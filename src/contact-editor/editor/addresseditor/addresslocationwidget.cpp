/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
#include <QStackedWidget>

using namespace ContactEditor;

struct LocaleAwareLessThan : std::binary_function<QString, QString, bool> {
    bool operator()(const QString &s1, const QString &s2) const
    {
        return QString::localeAwareCompare(s1, s2) < 0;
    }
};

AddressLocationWidget::AddressLocationWidget(QWidget *parent)
    : QWidget(parent)
    , mCurrentMode(CreateAddress)
{
    auto *topLayout = new QVBoxLayout(this);

    auto *gridLayout = new QGridLayout;
    topLayout->addLayout(gridLayout);

    mTypeCombo = new SelectAddressTypeComboBox(this);
    mTypeCombo->setObjectName(QStringLiteral("typeaddress"));
    connect(mTypeCombo, QOverload<const QString &>::of(&SelectAddressTypeComboBox::activated), this, &AddressLocationWidget::slotChanged);
    gridLayout->addWidget(mTypeCombo, 0, 0, 1, 2);

    QLabel *label = new QLabel(KContacts::Address::streetLabel(), this);
    label->setObjectName(QStringLiteral("streetlabel"));
    gridLayout->addWidget(label, 1, 0);

    mStreetEdit = new KLineEdit(this);
    mStreetEdit->setPlaceholderText(i18n("Add Street"));
    mStreetEdit->setObjectName(QStringLiteral("streetlineedit"));
    mStreetEdit->setTrapReturnKey(true);
    connect(mStreetEdit, &KLineEdit::editingFinished, this, &AddressLocationWidget::slotChanged);
    gridLayout->addWidget(mStreetEdit, 2, 0);

    label = new QLabel(KContacts::Address::postOfficeBoxLabel(), this);
    label->setObjectName(QStringLiteral("postofficeboxlabel"));
    gridLayout->addWidget(label, 1, 1);

    mPOBoxEdit = new KLineEdit(this);
    mPOBoxEdit->setPlaceholderText(i18n("Add Post Office Box"));
    mPOBoxEdit->setObjectName(QStringLiteral("postofficeboxlineedit"));
    mPOBoxEdit->setTrapReturnKey(true);
    connect(mPOBoxEdit, &KLineEdit::editingFinished, this, &AddressLocationWidget::slotChanged);
    gridLayout->addWidget(mPOBoxEdit, 2, 1);

    label = new QLabel(KContacts::Address::postalCodeLabel(), this);
    label->setObjectName(QStringLiteral("postalcodelabel"));
    gridLayout->addWidget(label, 3, 0);
    mPostalCodeEdit = new KLineEdit(this);
    mPostalCodeEdit->setPlaceholderText(i18n("Add Postal Code"));
    mPostalCodeEdit->setObjectName(QStringLiteral("postalcodelineedit"));
    mPostalCodeEdit->setTrapReturnKey(true);
    connect(mPostalCodeEdit, &KLineEdit::editingFinished, this, &AddressLocationWidget::slotChanged);
    gridLayout->addWidget(mPostalCodeEdit, 4, 0);

    label = new QLabel(KContacts::Address::localityLabel(), this);
    label->setObjectName(QStringLiteral("localitylabel"));
    gridLayout->addWidget(label, 3, 1);
    mLocalityEdit = new KLineEdit(this);
    mLocalityEdit->setPlaceholderText(i18n("Add Locality"));
    mLocalityEdit->setObjectName(QStringLiteral("localitylineedit"));
    mLocalityEdit->setTrapReturnKey(true);
    connect(mLocalityEdit, &KLineEdit::editingFinished, this, &AddressLocationWidget::slotChanged);
    gridLayout->addWidget(mLocalityEdit, 4, 1);

    label = new QLabel(KContacts::Address::regionLabel(), this);
    label->setObjectName(QStringLiteral("regionlabel"));
    gridLayout->addWidget(label, 5, 0);
    mRegionEdit = new KLineEdit(this);
    mRegionEdit->setPlaceholderText(i18n("Add Region"));
    mRegionEdit->setObjectName(QStringLiteral("regionlineedit"));
    mRegionEdit->setTrapReturnKey(true);
    connect(mRegionEdit, &KLineEdit::editingFinished, this, &AddressLocationWidget::slotChanged);
    gridLayout->addWidget(mRegionEdit, 6, 0);

    label = new QLabel(KContacts::Address::countryLabel(), this);
    label->setObjectName(QStringLiteral("countrylabel"));
    gridLayout->addWidget(label, 5, 1);
    mCountryCombo = new KComboBox(this);
    auto *edit = new KLineEdit(this);
    edit->setTrapReturnKey(true);
    mCountryCombo->setLineEdit(edit);
    mCountryCombo->setObjectName(QStringLiteral("countrycombobox"));
    mCountryCombo->setEditable(true);
    mCountryCombo->lineEdit()->setPlaceholderText(i18n("Add a Country"));
    mCountryCombo->setDuplicatesEnabled(false);
    connect(mCountryCombo, QOverload<const QString &>::of(&KComboBox::activated), this, &AddressLocationWidget::slotChanged);
    gridLayout->addWidget(mCountryCombo, 6, 1);

    mPreferredCheckBox = new QCheckBox(i18nc("street/postal", "This is the preferred address"), this);
    mPreferredCheckBox->setObjectName(QStringLiteral("preferredcheckbox"));
    gridLayout->addWidget(mPreferredCheckBox, 7, 0, 1, 2);

    mButtonStack = new QStackedWidget(this);
    mButtonStack->setObjectName(QStringLiteral("buttonstacked"));
    topLayout->addWidget(mButtonStack);

    QWidget *addButtonWidget = new QWidget(this);
    auto *addButtonWidgetLayout = new QHBoxLayout(addButtonWidget);
    addButtonWidgetLayout->setContentsMargins(0, 0, 0, 0);
    mAddAddress = new QPushButton(i18n("Add Address"), this);
    mAddAddress->setObjectName(QStringLiteral("addbuttonaddress"));
    connect(mAddAddress, &QPushButton::clicked, this, &AddressLocationWidget::slotAddAddress);
    addButtonWidgetLayout->addWidget(mAddAddress);
    addButtonWidgetLayout->addStretch(1);
    mButtonStack->addWidget(addButtonWidget);

    QWidget *modifyButtonWidget = new QWidget(this);
    auto *modifyButtonWidgetLayout = new QHBoxLayout(modifyButtonWidget);
    modifyButtonWidgetLayout->setContentsMargins(0, 0, 0, 0);
    mButtonStack->addWidget(modifyButtonWidget);

    mModifyAddress = new QPushButton(i18n("Update Address"), this);
    mModifyAddress->setObjectName(QStringLiteral("modifybuttonaddress"));
    modifyButtonWidgetLayout->addWidget(mModifyAddress);
    connect(mModifyAddress, &QPushButton::clicked, this, &AddressLocationWidget::slotUpdateAddress);

    mCancelAddress = new QPushButton(i18n("Cancel"), this);
    mCancelAddress->setObjectName(QStringLiteral("cancelbuttonaddress"));
    connect(mCancelAddress, &QPushButton::clicked, this, &AddressLocationWidget::slotCancelModifyAddress);
    modifyButtonWidgetLayout->addWidget(mCancelAddress);
    modifyButtonWidgetLayout->addStretch(1);
    const int buttonWidth = qMax(mCancelAddress->width(), mModifyAddress->width());
    mModifyAddress->setMinimumWidth(buttonWidth);
    mCancelAddress->setMinimumWidth(buttonWidth);

    topLayout->addStretch(1);
    fillCountryCombo();
    switchMode();
}

AddressLocationWidget::~AddressLocationWidget()
{
}

void AddressLocationWidget::slotChanged()
{
    mWasChanged = true;
}

bool AddressLocationWidget::wasChanged() const
{
    return mWasChanged;
}

void AddressLocationWidget::setReadOnly(bool readOnly)
{
    mPreferredCheckBox->setEnabled(!readOnly);
    mPOBoxEdit->setReadOnly(readOnly);
    mLocalityEdit->setReadOnly(readOnly);
    mRegionEdit->setReadOnly(readOnly);
    mPostalCodeEdit->setReadOnly(readOnly);
    mStreetEdit->setReadOnly(readOnly);
    mCountryCombo->setEnabled(!readOnly);
    mTypeCombo->setEnabled(!readOnly);

    mAddAddress->setEnabled(!readOnly);
    mModifyAddress->setEnabled(!readOnly);
    mCancelAddress->setEnabled(!readOnly);
}

void AddressLocationWidget::fillCountryCombo()
{
    QStringList countries;
    const QList<QLocale> localeList = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);
    countries.reserve(localeList.count());
    for (const QLocale &locale : localeList) {
        const QString localeStr = QLocale::countryToString(locale.country());
        if (countries.contains(localeStr)) {
            continue;
        }
        countries.append(localeStr);
    }

    std::sort(countries.begin(), countries.end(), LocaleAwareLessThan());

    mCountryCombo->addItems(countries);
    mCountryCombo->setAutoCompletion(true);
    mCountryCombo->completionObject()->setItems(countries);
    mCountryCombo->completionObject()->setIgnoreCase(true);

    const QString currentCountry = QLocale::countryToString(QLocale().country());
    mCountryCombo->setCurrentIndex(mCountryCombo->findText(currentCountry));
}

void AddressLocationWidget::slotAddAddress()
{
    KContacts::Address addr = address();
    if (!addr.isEmpty()) {
        Q_EMIT addNewAddress(addr);
        reset();
    }
}

void AddressLocationWidget::setAddress(const KContacts::Address &address)
{
    mAddress = address;
    mTypeCombo->setType(mAddress.type());
    mStreetEdit->setText(mAddress.street());
    mRegionEdit->setText(address.region());
    mLocalityEdit->setText(address.locality());
    mPostalCodeEdit->setText(address.postalCode());
    mPOBoxEdit->setText(address.postOfficeBox());
    mPreferredCheckBox->setChecked(address.type() &KContacts::Address::Pref);
    if (address.isEmpty()) {
        mCountryCombo->setItemText(mCountryCombo->currentIndex(),
                                   QLocale::countryToString(QLocale().country()));
    } else {
        mCountryCombo->setItemText(mCountryCombo->currentIndex(), mAddress.country());
    }
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
    address.setStreet(mStreetEdit->text());
    if (mPreferredCheckBox->isChecked()) {
        address.setType(address.type() | KContacts::Address::Pref);
    } else {
        address.setType(address.type() & ~(KContacts::Address::Pref));
    }
    return address;
}

void AddressLocationWidget::switchMode()
{
    switch (mCurrentMode) {
    case CreateAddress:
        mButtonStack->setCurrentIndex(0);
        break;
    case ModifyAddress:
        mButtonStack->setCurrentIndex(1);
        break;
    }
}

void AddressLocationWidget::slotModifyAddress(const KContacts::Address &address, int currentIndex)
{
    setAddress(address);
    mCurrentMode = ModifyAddress;
    mCurrentAddress = currentIndex;
    switchMode();
}

void AddressLocationWidget::clear()
{
    mCurrentMode = CreateAddress;
    setAddress(KContacts::Address());
    switchMode();
}

void AddressLocationWidget::slotUpdateAddress()
{
    if (mCurrentMode == ModifyAddress) {
        Q_EMIT updateAddress(address(), mCurrentAddress);
        reset();
    }
}

void AddressLocationWidget::reset()
{
    Q_EMIT updateAddressCanceled();
    mCurrentAddress = -1;
    mWasChanged = false;
    clear();
}

void AddressLocationWidget::slotCancelModifyAddress()
{
    reset();
}
