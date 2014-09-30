/*
IM address editor widget for KDE PIM

Copyright 2004,2010 Will Stephenson <wstephenson@kde.org>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) version 3, or any
later version accepted by the membership of KDE e.V. (or its
successor approved by the membership of KDE e.V.), which shall
act as a proxy defined in Section 6 of version 3 of the license.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "imeditordialog.h"

#include "imdelegate.h"
#include "imitemdialog.h"

#include <QGridLayout>
#include <QPointer>
#include <QPushButton>
#include <QTreeView>

#include <klocalizedstring.h>
#include <kmessagebox.h>
#include <KSharedConfig>
#include <KConfigGroup>

IMEditorDialog::IMEditorDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Edit Instant Messaging Addresses"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QWidget *widget = new QWidget(this);
    mainLayout->addWidget(widget);

    QGridLayout *layout = new QGridLayout(widget);
    layout->setMargin(0);

    mAddButton = new QPushButton(i18nc("@action:button", "Add..."));
    mEditButton = new QPushButton(i18nc("@action:button", "Edit..."));
    mRemoveButton = new QPushButton(i18nc("@action:button", "Remove"));
    mStandardButton = new QPushButton(i18nc("@action:button", "Set as Standard"));

    mView = new QTreeView;
    mView->setRootIsDecorated(false);

    layout->addWidget(mView, 0, 0, 5, 1);
    layout->addWidget(mAddButton, 0, 1);
    layout->addWidget(mEditButton, 1, 1);
    layout->addWidget(mRemoveButton, 2, 1);
    layout->addWidget(mStandardButton, 3, 1);
    layout->setRowStretch(4, 1);

    connect(mAddButton, &QPushButton::clicked, this, &IMEditorDialog::slotAdd);
    connect(mEditButton, &QPushButton::clicked, this, &IMEditorDialog::slotEdit);
    connect(mRemoveButton, &QPushButton::clicked, this, &IMEditorDialog::slotRemove);
    connect(mStandardButton, &QPushButton::clicked, this, &IMEditorDialog::slotSetStandard);

    mModel = new IMModel(this);

    mView->setModel(mModel);
    mView->setItemDelegate(new IMDelegate(this));

    connect(mView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(slotUpdateButtons()));
    connect(mView, &QTreeView::doubleClicked, this, &IMEditorDialog::slotEdit);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &IMEditorDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &IMEditorDialog::reject);
    mainLayout->addWidget(buttonBox);

    slotUpdateButtons();
    readConfig();
}

IMEditorDialog::~IMEditorDialog()
{
    writeConfig();
}

void IMEditorDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "IMEditorDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(400, 200));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void IMEditorDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "IMEditorDialog");
    group.writeEntry("Size", size());
}

void IMEditorDialog::setAddresses(const IMAddress::List &addresses)
{
    mModel->setAddresses(addresses);
}

IMAddress::List IMEditorDialog::addresses() const
{
    return mModel->addresses();
}

void IMEditorDialog::slotAdd()
{
    QPointer<IMItemDialog> d(new IMItemDialog(this));
    d->setWindowTitle(i18nc("@title:window", "Add IM Address"));
    if (d->exec() == QDialog::Accepted && d != 0) {
        IMAddress newAddress = d->address();
        int addedRow = mModel->rowCount();
        mModel->insertRow(addedRow);

        mModel->setData(mModel->index(addedRow, 0), newAddress.protocol(), IMModel::ProtocolRole);
        mModel->setData(mModel->index(addedRow, 1), newAddress.name(), Qt::EditRole);
    }
    delete d;
}

void IMEditorDialog::slotEdit()
{
    const int currentRow = mView->currentIndex().row();
    if (currentRow < 0) {
        return;
    }

    QPointer<IMItemDialog> d(new IMItemDialog(this));
    d->setWindowTitle(i18nc("@title:window", "Edit IM Address"));
    d->setAddress(mModel->addresses().at(currentRow));

    if (d->exec() == QDialog::Accepted && d != 0) {
        IMAddress editedAddress = d->address();
        mModel->setData(mModel->index(currentRow, 0), editedAddress.protocol(),
                        IMModel::ProtocolRole);
        mModel->setData(mModel->index(currentRow, 1), editedAddress.name(),
                        Qt::EditRole);
    }
    delete d;
}

void IMEditorDialog::slotRemove()
{
    const int currentRow = mView->currentIndex().row();
    if (currentRow < 0) {
        return;
    }

    if (KMessageBox::warningContinueCancel(
            this,
            xi18nc("@info Instant messaging",
                   "Do you really want to delete the selected <resource>%1</resource> address?",
                   mModel->data(mModel->index(currentRow, 0), Qt::DisplayRole).toString()),
            i18nc("@title:window", "Confirm Delete Resource"),
            KStandardGuiItem::del()) != KMessageBox::Continue) {
        return;
    }

    mModel->removeRow(currentRow);
}

void IMEditorDialog::slotSetStandard()
{
    const int currentRow = mView->currentIndex().row();
    if (currentRow < 0) {
        return;
    }

    // set current index as preferred and all other as non-preferred
    for (int i = 0; i < mModel->rowCount(); ++i) {
        const QModelIndex index = mModel->index(i, 0);
        mModel->setData(index, (index.row() == currentRow), IMModel::IsPreferredRole);
    }
}

void IMEditorDialog::slotUpdateButtons()
{
    const QModelIndex currentIndex = mView->currentIndex();

    mRemoveButton->setEnabled(currentIndex.isValid());
    mEditButton->setEnabled(currentIndex.isValid());

    mStandardButton->setEnabled(currentIndex.isValid() &&
                                !mModel->data(currentIndex, IMModel::IsPreferredRole).toBool());
}
