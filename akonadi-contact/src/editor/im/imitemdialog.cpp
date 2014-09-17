/*
IM address item editor widget for KDE PIM

Copyright 2012 Jonathan Marten <jjm@keelhaul.me.uk>

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

#include "imitemdialog.h"

#include "immodel.h"
#include "improtocols.h"

#include <QFormLayout>

#include <QDialogButtonBox>
#include <QPushButton>
#include <kcombobox.h>
#include <klineedit.h>
#include <klocalizedstring.h>

IMItemDialog::IMItemDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QWidget *widget = new QWidget(this);
    mainLayout->addWidget(widget);

    QFormLayout *layout = new QFormLayout(widget);

    mProtocolCombo = new KComboBox;
    mProtocolCombo->addItem(i18nc("@item:inlistbox select from a list of IM protocols",
                                  "Select..."));
    layout->addRow(i18nc("@label:listbox", "Protocol:"), mProtocolCombo);

    const QStringList protocols = IMProtocols::self()->protocols();
    foreach (const QString &protocol, protocols) {
        mProtocolCombo->addItem(QIcon::fromTheme(IMProtocols::self()->icon(protocol + QLatin1String(".png"))),
                                IMProtocols::self()->name(protocol),
                                protocol);
    }

    mNameEdit = new QLineEdit;
    layout->addRow(i18nc("@label:textbox IM address", "Address:"), mNameEdit);

    connect(mProtocolCombo, static_cast<void (KComboBox::*)(int)>(&KComboBox::currentIndexChanged), this, &IMItemDialog::slotUpdateButtons);
    connect(mNameEdit, &QLineEdit::textChanged, this, &IMItemDialog::slotUpdateButtons);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mOkButton = buttonBox->button(QDialogButtonBox::Ok);

    mOkButton->setDefault(true);
    mOkButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &IMItemDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &IMItemDialog::reject);
    mainLayout->addWidget(buttonBox);

    slotUpdateButtons();
}

void IMItemDialog::setAddress(const IMAddress &address)
{
    mProtocolCombo->setCurrentIndex(
        IMProtocols::self()->protocols().indexOf(address.protocol()) + 1);

    mNameEdit->setText(address.name());
    slotUpdateButtons();
}

IMAddress IMItemDialog::address() const
{
    return IMAddress(mProtocolCombo->itemData(mProtocolCombo->currentIndex()).toString(),
                     mNameEdit->text(), false);
}

void IMItemDialog::slotUpdateButtons()
{
    mOkButton->setEnabled(mProtocolCombo->currentIndex() > 0 && !mNameEdit->text().isEmpty());
}
