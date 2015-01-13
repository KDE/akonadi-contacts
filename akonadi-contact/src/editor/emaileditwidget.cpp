/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "emaileditwidget.h"

#include "autoqpointer_p.h"

#include <QtCore/QEvent>
#include <QtCore/QString>
#include <QGridLayout>
#include <QPushButton>
#include <QToolButton>

#include <kcontacts/addressee.h>
#include <kacceleratormanager.h>
#include <qinputdialog.h>
#include <klineedit.h>
#include <QListWidget>
#include <klocalizedstring.h>
#include <kmessagebox.h>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <KEmailAddress>

class EmailAddressExtracter : public QObject
{
public:
    EmailAddressExtracter(QLineEdit *lineEdit)
        : QObject(lineEdit)
        , mLineEdit(lineEdit)
    {
        lineEdit->installEventFilter(this);
    }

    virtual bool eventFilter(QObject *watched, QEvent *event)
    {
        if (watched == mLineEdit && event->type() == QEvent::FocusOut) {
            const QString fullEmailAddress = mLineEdit->text();
            const QString extractedEmailAddress = KEmailAddress::extractEmailAddress(fullEmailAddress);
            mLineEdit->setText(extractedEmailAddress);
        }

        return QObject::eventFilter(watched, event);
    }

private:
    QLineEdit *mLineEdit;
};

class EmailItem : public QListWidgetItem
{
public:
    EmailItem(const QString &text, QListWidget *parent, bool preferred)
        : QListWidgetItem(text, parent)
        , mPreferred(preferred)
    {
        format();
    }

    void setPreferred(bool preferred)
    {
        mPreferred = preferred;
        format();
    }
    bool preferred() const
    {
        return mPreferred;
    }

private:
    void format()
    {
        QFont f = font();
        f.setBold(mPreferred);
        setFont(f);
    }

private:
    bool mPreferred;
};

EmailEditWidget::EmailEditWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);

    mEmailEdit = new QLineEdit;
    new EmailAddressExtracter(mEmailEdit);
    connect(mEmailEdit, &QLineEdit::textChanged, this, &EmailEditWidget::textChanged);
    layout->addWidget(mEmailEdit);

    mEditButton = new QToolButton;
    mEditButton->setText(QStringLiteral("..."));
    connect(mEditButton, &QPushButton::clicked, this, &EmailEditWidget::edit);
    layout->addWidget(mEditButton);
    setFocusProxy(mEditButton);
    setFocusPolicy(Qt::StrongFocus);
}

EmailEditWidget::~EmailEditWidget()
{
}

void EmailEditWidget::setReadOnly(bool readOnly)
{
    mEmailEdit->setReadOnly(readOnly);
    mEditButton->setEnabled(!readOnly);
}

void EmailEditWidget::loadContact(const KContacts::Addressee &contact)
{
    mEmailList = contact.emails();

    if (!mEmailList.isEmpty()) {
        mEmailEdit->setText(mEmailList.first());
    } else {
        mEmailEdit->setText(QString());
    }
}

void EmailEditWidget::storeContact(KContacts::Addressee &contact) const
{
    QStringList emails(mEmailList);

    // the preferred address is always the first one, remove it...
    if (!emails.isEmpty()) {
        emails.removeFirst();
    }

    // ... and prepend the one from the line edit
    if (!mEmailEdit->text().isEmpty()) {
        emails.prepend(mEmailEdit->text().toLower());
    }

    contact.setEmails(emails);
}

void EmailEditWidget::edit()
{
    AutoQPointer<EmailEditDialog> dlg = new EmailEditDialog(this);
    dlg->setEmailList(mEmailList);
    if (dlg->exec()) {
        if (dlg->changed()) {
            mEmailList = dlg->emails();
            if (!mEmailList.isEmpty()) {
                mEmailEdit->setText(mEmailList.first());
            } else {
                mEmailEdit->setText(QString());
            }
        }
    }
}

void EmailEditWidget::textChanged(const QString &text)
{
    if (!mEmailList.isEmpty()) {
        mEmailList.removeFirst();
    }

    mEmailList.prepend(text);
}

EmailEditDialog::EmailEditDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Edit Email Addresses"));

    QWidget *page = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->addWidget(page);

    QGridLayout *topLayout = new QGridLayout(page);
    mainLayout->addLayout(topLayout);
    //PORT QT5 topLayout->setSpacing(spacingHint());
    topLayout->setMargin(0);

    mEmailListBox = new QListWidget(page);
    mEmailListBox->setObjectName(QLatin1String("emailListBox"));
    mainLayout->addWidget(mEmailListBox);
    mEmailListBox->setSelectionMode(QAbstractItemView::SingleSelection);

    // Make sure there is room for the scrollbar
    mEmailListBox->setMinimumHeight(mEmailListBox->sizeHint().height() + 30);
    connect(mEmailListBox, &QListWidget::currentItemChanged, this, &EmailEditDialog::selectionChanged);
    connect(mEmailListBox, &QListWidget::itemDoubleClicked, this, &EmailEditDialog::edit);
    topLayout->addWidget(mEmailListBox, 0, 0, 5, 2);

    mAddButton = new QPushButton(i18n("Add..."), page);
    mainLayout->addWidget(mAddButton);
    connect(mAddButton, &QPushButton::clicked, this, &EmailEditDialog::add);
    topLayout->addWidget(mAddButton, 0, 2);

    mEditButton = new QPushButton(i18n("Edit..."), page);
    mainLayout->addWidget(mEditButton);
    mEditButton->setEnabled(false);
    connect(mEditButton, &QPushButton::clicked, this, &EmailEditDialog::edit);
    topLayout->addWidget(mEditButton, 1, 2);

    mRemoveButton = new QPushButton(i18n("Remove"), page);
    mainLayout->addWidget(mRemoveButton);
    mRemoveButton->setEnabled(false);
    connect(mRemoveButton, &QPushButton::clicked, this, &EmailEditDialog::remove);
    topLayout->addWidget(mRemoveButton, 2, 2);

    mStandardButton = new QPushButton(i18n("Set as Standard"), page);
    mainLayout->addWidget(mStandardButton);
    mStandardButton->setEnabled(false);
    connect(mStandardButton, &QPushButton::clicked, this, &EmailEditDialog::standard);
    topLayout->addWidget(mStandardButton, 3, 2);

    topLayout->setRowStretch(4, 1);

    // set default state
    KAcceleratorManager::manage(this);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    buttonBox->button(QDialogButtonBox::Cancel)->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EmailEditDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EmailEditDialog::reject);
    mainLayout->addWidget(buttonBox);

    readConfig();
}

EmailEditDialog::~EmailEditDialog()
{
    writeConfig();
}

void EmailEditDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "EmailEditDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(400, 200));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void EmailEditDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "EmailEditDialog");
    group.writeEntry("Size", size());
}

QStringList EmailEditDialog::emails() const
{
    QStringList emails;

    for (int i = 0; i < mEmailListBox->count(); ++i) {
        EmailItem *item = static_cast<EmailItem *>(mEmailListBox->item(i));
        if (item->preferred()) {
            emails.prepend(item->text());
        } else {
            emails.append(item->text());
        }
    }

    return emails;
}

void EmailEditDialog::add()
{
    bool ok = false;

    QString email = QInputDialog::getText(this, i18n("Add Email"), i18n("New Email:"), QLineEdit::Normal,
                                          QString(), &ok);

    if (!ok) {
        return;
    }

    email = KEmailAddress::extractEmailAddress(email.toLower());

    // check if item already available, ignore if so...
    for (int i = 0; i < mEmailListBox->count(); ++i) {
        if (mEmailListBox->item(i)->text() == email) {
            return;
        }
    }

    new EmailItem(email, mEmailListBox, (mEmailListBox->count() == 0));

    mChanged = true;
}

void EmailEditDialog::edit()
{
    bool ok = false;

    QListWidgetItem *item = mEmailListBox->currentItem();

    QString email = QInputDialog::getText(this, i18n("Edit Email"),
                                          i18nc("@label:textbox Inputfield for an email address", "Email:"), QLineEdit::Normal,
                                          item->text(), &ok);

    if (!ok) {
        return;
    }

    email = KEmailAddress::extractEmailAddress(email.toLower());

    // check if item already available, ignore if so...
    for (int i = 0; i < mEmailListBox->count(); ++i) {
        if (mEmailListBox->item(i)->text() == email) {
            return;
        }
    }

    EmailItem *eitem = static_cast<EmailItem *>(item);
    eitem->setText(email);

    mChanged = true;
}

void EmailEditDialog::remove()
{
    const QString address = mEmailListBox->currentItem()->text();

    const QString text = i18n("<qt>Are you sure that you want to remove the email address <b>%1</b>?</qt>", address);
    const QString caption = i18n("Confirm Remove");

    if (KMessageBox::warningContinueCancel(this, text, caption, KGuiItem(i18n("&Delete"), QStringLiteral("edit-delete"))) == KMessageBox::Continue) {
        EmailItem *item = static_cast<EmailItem *>(mEmailListBox->currentItem());

        const bool preferred = item->preferred();
        mEmailListBox->takeItem(mEmailListBox->currentRow());
        if (preferred) {
            item = dynamic_cast<EmailItem *>(mEmailListBox->item(0));
            if (item) {
                item->setPreferred(true);
            }
        }

        mChanged = true;
    }
}

bool EmailEditDialog::changed() const
{
    return mChanged;
}

void EmailEditDialog::setEmailList(const QStringList &list)
{
    QStringList items = list;
    if (items.removeAll(QLatin1String("")) > 0) {
        mChanged = true;
    } else {
        mChanged = false;
    }

    QStringList::ConstIterator it;
    bool preferred = true;
    QStringList::ConstIterator end(items.constEnd());
    QStringList emails;
    for (it = items.constBegin(); it != end; ++it) {
        if (!emails.contains(*it)) {
            new EmailItem(*it, mEmailListBox, preferred);
            emails << *it;
            preferred = false;
        }
    }

}

void EmailEditDialog::standard()
{
    for (int i = 0; i < mEmailListBox->count(); ++i) {
        EmailItem *item = static_cast<EmailItem *>(mEmailListBox->item(i));
        if (i == mEmailListBox->currentRow()) {
            item->setPreferred(true);
        } else {
            item->setPreferred(false);
        }
    }

    mChanged = true;
}

void EmailEditDialog::selectionChanged()
{
    const int index = mEmailListBox->currentRow();
    const bool value = (index >= 0);   // An item is selected

    mRemoveButton->setEnabled(value);
    mEditButton->setEnabled(value);
    mStandardButton->setEnabled(value);
}
