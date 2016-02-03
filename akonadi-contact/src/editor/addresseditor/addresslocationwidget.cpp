/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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


#include "addresslocationwidget.h"
#include "selectaddresstypecombobox.h"

#include <KComboBox>
#include <KLineEdit>
#include <KLocalizedString>

#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>

AddressLocationWidget::AddressLocationWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *topLayout = new QGridLayout;
    setLayout(topLayout);

    mTypeCombo = new SelectAddressTypeComboBox(this);
    mTypeCombo->setObjectName(QStringLiteral("typeaddress"));
    topLayout->addWidget(mTypeCombo, 0, 0, 1, 2);

    QLabel *label = new QLabel(KContacts::Address::streetLabel(), this);
    label->setObjectName(QStringLiteral("streetlabel"));
    topLayout->addWidget(label, 1, 0);

    mStreetEdit = new KLineEdit(this);
    mStreetEdit->setPlaceholderText(i18n("Add Street"));
    mStreetEdit->setObjectName(QStringLiteral("streetlineedit"));
    mStreetEdit->setTrapReturnKey(true);
    topLayout->addWidget(mStreetEdit, 2, 0);



    label = new QLabel(KContacts::Address::postOfficeBoxLabel(), this);
    label->setObjectName(QStringLiteral("postofficeboxlabel"));
    topLayout->addWidget(label, 1, 1);

    mPOBoxEdit = new KLineEdit(this);
    mPOBoxEdit->setPlaceholderText(i18n("Add Post Office Box"));
    mPOBoxEdit->setObjectName(QStringLiteral("postofficeboxlineedit"));
    mPOBoxEdit->setTrapReturnKey(true);
    topLayout->addWidget(mPOBoxEdit, 2, 1);

    label = new QLabel(KContacts::Address::postalCodeLabel(), this);
    label->setObjectName(QStringLiteral("postalcodelabel"));
    topLayout->addWidget(label, 3, 0);
    mPostalCodeEdit = new KLineEdit(this);
    mPostalCodeEdit->setPlaceholderText(i18n("Add Postal Code"));
    mPostalCodeEdit->setObjectName(QStringLiteral("postalcodelineedit"));
    mPostalCodeEdit->setTrapReturnKey(true);
    topLayout->addWidget(mPostalCodeEdit, 4, 0);


    label = new QLabel(KContacts::Address::localityLabel(), this);
    label->setObjectName(QStringLiteral("localitylabel"));
    topLayout->addWidget(label, 3, 1);
    mLocalityEdit = new KLineEdit(this);
    mLocalityEdit->setPlaceholderText(i18n("Add Locality"));
    mLocalityEdit->setObjectName(QStringLiteral("localitylineedit"));
    mLocalityEdit->setTrapReturnKey(true);
    topLayout->addWidget(mLocalityEdit, 4, 1);

    label = new QLabel(KContacts::Address::regionLabel(), this);
    label->setObjectName(QStringLiteral("regionlabel"));
    topLayout->addWidget(label, 5, 0);
    mRegionEdit = new KLineEdit(this);
    mRegionEdit->setPlaceholderText(i18n("Add Region"));
    mRegionEdit->setObjectName(QStringLiteral("regionlineedit"));
    mRegionEdit->setTrapReturnKey(true);
    topLayout->addWidget(mRegionEdit, 6, 0);


    label = new QLabel(KContacts::Address::countryLabel(), this);
    label->setObjectName(QStringLiteral("countrylabel"));
    topLayout->addWidget(label, 5, 1);
    mCountryCombo = new KComboBox(this);
    mCountryCombo->setObjectName(QStringLiteral("countrycombobox"));
    mCountryCombo->setEditable(true);
    mCountryCombo->lineEdit()->setPlaceholderText(i18n("Add a Country"));
    mCountryCombo->setDuplicatesEnabled(false);
    topLayout->addWidget(mCountryCombo, 6, 1);

    mPreferredCheckBox = new QCheckBox(i18nc("street/postal", "This is the preferred address"), this);
    mPreferredCheckBox->setObjectName(QStringLiteral("preferredcheckbox"));
    topLayout->addWidget(mPreferredCheckBox, 7, 0, 1, 2);

    mAddAddress = new QPushButton(i18n("Add Address"), this);
    mAddAddress->setObjectName(QStringLiteral("addbuttonaddress"));
    topLayout->addWidget(mAddAddress, 8, 0);

}

AddressLocationWidget::~AddressLocationWidget()
{

}

void AddressLocationWidget::setAddress(const KContacts::Address &address)
{
    mAddress = address;
    mTypeCombo->setType(mAddress.type());
    //mStreetTextEdit->setPlainText(mAddress.street());
    mRegionEdit->setText(address.region());
    mLocalityEdit->setText(address.locality());
    mPostalCodeEdit->setText(address.postalCode());
    mPOBoxEdit->setText(address.postOfficeBox());
    mPreferredCheckBox->setChecked(address.type() &KContacts::Address::Pref);
#if 0
    if (address.isEmpty()) {
        mCountryCombo->setItemText(mCountryCombo->currentIndex(),
                                   QLocale::countryToString(QLocale().country()));
    } else {
        mCountryCombo->setItemText(mCountryCombo->currentIndex(), mAddress.country());
    }
#endif
    //TODO
}

KContacts::Address AddressLocationWidget::address() const
{
    KContacts::Address address(mAddress);

    address.setType(mTypeCombo->type());
    address.setLocality(mLocalityEdit->text());
    address.setRegion(mRegionEdit->text());
    address.setPostalCode(mPostalCodeEdit->text());
    address.setCountry(mCountryCombo->currentText());
    address.setPostOfficeBox(mPOBoxEdit->text());
    //address.setStreet(mStreetTextEdit->toPlainText());
    //address.setLabel(mLabel);
#if 0
    if (mPreferredCheckBox->isChecked()) {
        address.setType(address.type() | KContacts::Address::Pref);
    } else {
        address.setType(address.type() & ~(KContacts::Address::Pref));
    }
#endif
    return address;

    return KContacts::Address();
}

void AddressLocationWidget::slotModifyAddress(const KContacts::Address &address, int currentIndex)
{
    //TODO
}
