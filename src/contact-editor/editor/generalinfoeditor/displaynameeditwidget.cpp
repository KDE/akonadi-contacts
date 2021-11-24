/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "displaynameeditwidget.h"

#include <QAbstractItemView>
#include <QEvent>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyledItemDelegate>

#include <KComboBox>
#include <KLocalizedString>

// Tries to guess the display type that is used for the passed contact
static DisplayNameEditWidget::DisplayType guessedDisplayType(const KContacts::Addressee &contact)
{
    if (contact.formattedName() == (contact.givenName() + QLatin1Char(' ') + contact.familyName())) {
        return DisplayNameEditWidget::SimpleName;
    } else if (contact.formattedName() == contact.assembledName()) {
        return DisplayNameEditWidget::FullName;
    } else if (contact.formattedName() == (contact.familyName() + QLatin1String(", ") + contact.givenName())) {
        return DisplayNameEditWidget::ReverseNameWithComma;
    } else if (contact.formattedName() == (contact.familyName() + QLatin1Char(' ') + contact.givenName())) {
        return DisplayNameEditWidget::ReverseName;
    } else if (contact.formattedName() == contact.organization()) {
        return DisplayNameEditWidget::Organization;
    } else {
        return DisplayNameEditWidget::CustomName;
    }
}

class DisplayNameDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DisplayNameDelegate(QAbstractItemView *view, QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {
        mDescriptions.append(i18n("Short Name"));
        mDescriptions.append(i18n("Full Name"));
        mDescriptions.append(i18n("Reverse Name with Comma"));
        mDescriptions.append(i18n("Reverse Name"));
        mDescriptions.append(i18n("Organization"));
        mDescriptions.append(i18nc("@item:inlistbox A custom name format", "Custom"));

        QFont font = view->font();
        font.setStyle(QFont::StyleItalic);
        QFontMetrics metrics(font);
        for (const QString &description : std::as_const(mDescriptions)) {
            mMaxDescriptionWidth = qMax(mMaxDescriptionWidth, metrics.boundingRect(description).width());
        }

        mMaxDescriptionWidth += 2;
    }

    int maximumDescriptionWidth() const
    {
        return mMaxDescriptionWidth;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::paint(painter, option, index);
        const QRect rect(option.rect.width() - mMaxDescriptionWidth, option.rect.y(), mMaxDescriptionWidth, option.rect.height());
        painter->save();
        QFont font(painter->font());
        font.setStyle(QFont::StyleItalic);
        painter->setFont(font);
        if (option.state & QStyle::State_Selected) {
            painter->setPen(option.palette.color(QPalette::Normal, QPalette::BrightText));
        } else {
            painter->setPen(option.palette.color(QPalette::Disabled, QPalette::Text));
        }
        painter->drawText(rect, Qt::AlignLeft, mDescriptions.at(index.row()));
        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setWidth(size.width() + mMaxDescriptionWidth);

        return size;
    }

private:
    QStringList mDescriptions;
    int mMaxDescriptionWidth = 0;
};

DisplayNameEditWidget::DisplayNameEditWidget(QWidget *parent)
    : QWidget(parent)
    , mDisplayType(FullName)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins({});

    mView = new KComboBox(this);
    mView->addItems(QStringList() << QString() << QString() << QString() << QString() << QString() << QString());

    layout->addWidget(mView);
    setFocusProxy(mView);
    setFocusPolicy(Qt::StrongFocus);
    connect(mView, qOverload<int>(&KComboBox::activated), this, &DisplayNameEditWidget::displayTypeChanged);

    auto delegate = new DisplayNameDelegate(mView->view(), this);
    mView->view()->setItemDelegate(delegate);

    mAdditionalPopupWidth = delegate->maximumDescriptionWidth();

    mViewport = mView->view()->viewport();
    mViewport->installEventFilter(this);
}

DisplayNameEditWidget::~DisplayNameEditWidget() = default;

void DisplayNameEditWidget::setReadOnly(bool readOnly)
{
    mView->setEnabled(!readOnly);
}

void DisplayNameEditWidget::setDisplayType(DisplayType type)
{
    if ((int)type == -1) {
        // guess the used display type
        mDisplayType = guessedDisplayType(mContact);
    } else {
        mDisplayType = type;
    }

    updateView();
}

DisplayNameEditWidget::DisplayType DisplayNameEditWidget::displayType() const
{
    return mDisplayType;
}

void DisplayNameEditWidget::loadContact(const KContacts::Addressee &contact)
{
    mContact = contact;

    mDisplayType = guessedDisplayType(mContact);

    updateView();
}

void DisplayNameEditWidget::storeContact(KContacts::Addressee &contact) const
{
    contact.setFormattedName(mView->currentText());
}

void DisplayNameEditWidget::changeName(const KContacts::Addressee &contact)
{
    const QString organization = mContact.organization();
    mContact = contact;
    mContact.setOrganization(organization);
    if (mDisplayType == CustomName) {
        mContact.setFormattedName(mView->currentText());
    }

    updateView();
}

void DisplayNameEditWidget::changeOrganization(const QString &organization)
{
    mContact.setOrganization(organization);

    updateView();
}

void DisplayNameEditWidget::displayTypeChanged(int type)
{
    mDisplayType = (DisplayType)type;

    updateView();
}

bool DisplayNameEditWidget::eventFilter(QObject *object, QEvent *event)
{
    if (object == mViewport) {
        if (event->type() == QEvent::Show) {
            // retrieve the widget that contains the popup view
            QWidget *parentWidget = mViewport->parentWidget()->parentWidget();

            int maxWidth = 0;
            QFontMetrics metrics(mView->font());
            const int viewCount(mView->count());
            for (int i = 0; i < viewCount; ++i) {
                maxWidth = qMax(maxWidth, metrics.boundingRect(mView->itemText(i)).width());
            }

            // resize it to show the complete content
            parentWidget->resize(maxWidth + mAdditionalPopupWidth + 20, parentWidget->height());
        }
        return false;
    }

    return QWidget::eventFilter(object, event);
}

void DisplayNameEditWidget::updateView()
{
    // SimpleName:
    mView->setItemText(0, mContact.givenName() + QLatin1Char(' ') + mContact.familyName());

    // FullName:
    mView->setItemText(1, mContact.assembledName());

    // ReverseNameWithComma:
    mView->setItemText(2, mContact.familyName() + QStringLiteral(", ") + mContact.givenName());

    // ReverseName:
    mView->setItemText(3, mContact.familyName() + QLatin1Char(' ') + mContact.givenName());

    // Organization:
    mView->setItemText(4, mContact.organization());

    // CustomName:
    mView->setItemText(5, mContact.formattedName());

    // delay the state change here, since we might have been called from mView via a signal
    QMetaObject::invokeMethod(
        this,
        [this]() {
            setComboBoxEditable(mDisplayType == CustomName);
        },
        Qt::QueuedConnection);

    mView->setCurrentIndex((int)mDisplayType);
}

void DisplayNameEditWidget::setComboBoxEditable(bool value)
{
    mView->setEditable(value);
}

#include "displaynameeditwidget.moc"
