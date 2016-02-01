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

#include <KComboBox>
#include <KLineEdit>
#include <KLocalizedString>

#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>

AddressLocationWidget::AddressLocationWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *topLayout = new QGridLayout;
    setLayout(topLayout);



    QLabel *label = new QLabel(KContacts::Address::postOfficeBoxLabel(), this);
    label->setObjectName(QStringLiteral("postofficeboxlabel"));

    mPOBoxEdit = new KLineEdit(this);
    mPOBoxEdit->setObjectName(QStringLiteral("postofficeboxlineedit"));
    mPOBoxEdit->setTrapReturnKey(true);


    label = new QLabel(KContacts::Address::localityLabel(), this);
    label->setObjectName(QStringLiteral("localitylabel"));
    mLocalityEdit = new KLineEdit(this);
    mLocalityEdit->setObjectName(QStringLiteral("localitylineedit"));
    mLocalityEdit->setTrapReturnKey(true);

    label = new QLabel(KContacts::Address::regionLabel(), this);
    label->setObjectName(QStringLiteral("regionlabel"));
    mRegionEdit = new KLineEdit(this);
    mRegionEdit->setObjectName(QStringLiteral("regionlineedit"));
    mRegionEdit->setTrapReturnKey(true);

    label = new QLabel(KContacts::Address::postalCodeLabel(), this);
    label->setObjectName(QStringLiteral("postalcodelabel"));
    mPostalCodeEdit = new KLineEdit(this);
    mPostalCodeEdit->setObjectName(QStringLiteral("postalcodelineedit"));
    mPostalCodeEdit->setTrapReturnKey(true);

    label = new QLabel(KContacts::Address::countryLabel(), this);
    label->setObjectName(QStringLiteral("countrylabel"));
    mCountryCombo = new KComboBox(this);
    mCountryCombo->setObjectName(QStringLiteral("countrycombobox"));
    mCountryCombo->setEditable(true);
    mCountryCombo->setDuplicatesEnabled(false);

    mPreferredCheckBox = new QCheckBox(i18nc("street/postal", "This is the preferred address"), this);
    mPreferredCheckBox->setObjectName(QStringLiteral("preferredcheckbox"));

}

AddressLocationWidget::~AddressLocationWidget()
{

}

void AddressLocationWidget::setAddress(const KContacts::Address &address)
{
    //TODO
}

KContacts::Address AddressLocationWidget::address() const
{
    return KContacts::Address();
}
