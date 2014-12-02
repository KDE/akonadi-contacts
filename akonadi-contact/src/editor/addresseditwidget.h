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

#ifndef ADDRESSEDITWIDGET_H
#define ADDRESSEDITWIDGET_H

#include <QWidget>

#include <kcontacts/address.h>
#include <kcontacts/addressee.h>
#include <kcombobox.h>
#include <QDialog>

class QCheckBox;
class QLabel;

class QLineEdit;
class KTextEdit;

/**
 * @short A widget that shows a list of addresses for selection.
 */
class AddressSelectionWidget : public KComboBox
{
    Q_OBJECT

public:
    /**
     * Creates a new address selection widget.
     *
     * @param parent The parent widget.
     */
    explicit AddressSelectionWidget(QWidget *parent = Q_NULLPTR);

    /**
     * Destroys the address selection widget.
     */
    virtual ~AddressSelectionWidget();

    /**
     * Sets the list of @p addresses that can be chosen from.
     * @param addresses list of addresses that can be chosen from
     */
    void setAddresses(const KContacts::Address::List &addresses);

    /**
     * Sets the current @p address.
     * @param address new current address
     */
    void setCurrentAddress(const KContacts::Address &address);

    /**
     * Returns the current selected address.
     */
    KContacts::Address currentAddress() const;

Q_SIGNALS:
    /**
     * This signal is emitted whenever the selection of the
     * address has changed.
     *
     * @param address The new selected address.
     */
    void selectionChanged(const KContacts::Address &address);

private Q_SLOTS:
    void selected(int);

private:
    void updateView();

    KContacts::Address::List mAddresses;
};

/**
 * @short A widget for selecting the type of an address.
 */
class AddressTypeCombo : public KComboBox
{
    Q_OBJECT

public:
    /**
     * Creates a new address type combo.
     *
     * @param parent The parent widget.
     */
    explicit AddressTypeCombo(QWidget *parent = Q_NULLPTR);

    /**
     * Destroys the address type combo.
     */
    ~AddressTypeCombo();

    /**
     * Sets the type that shall be selected in the combobox.
     * @param type KABC address type to set.
     */
    void setType(KContacts::Address::Type type);

    /**
     * Returns the type that is currently selected.
     */
    KContacts::Address::Type type() const;

private Q_SLOTS:
    void selected(int);
    void otherSelected();

private:
    void update();

    KContacts::Address::Type mType;
    int mLastSelected;
    QList<int> mTypeList;
};

/**
 * @short An editor widget for addresses.
 */
class AddressEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddressEditWidget(QWidget *parent = Q_NULLPTR);
    ~AddressEditWidget();

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);

public Q_SLOTS:
    void updateName(const QString &name);

private Q_SLOTS:
    void updateAddressView();
    void createAddress();
    void editAddress();
    void deleteAddress();

private:
    void updateButtons();
    void fixPreferredAddress(const KContacts::Address &preferredAddress);

    AddressSelectionWidget *mAddressSelectionWidget;

    QLabel *mAddressView;
    QPushButton *mCreateButton;
    QPushButton *mEditButton;
    QPushButton *mDeleteButton;

    KContacts::Address::List mAddressList;
    QString mName;
    bool mReadOnly;
};

/**
  Dialog for editing address details.
 */
class AddressEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddressEditDialog(QWidget *parent = Q_NULLPTR);
    ~AddressEditDialog();

    void setAddress(const KContacts::Address &address);
    KContacts::Address address() const;

private Q_SLOTS:
    void editLabel();

private:
    void fillCountryCombo();

    AddressTypeCombo *mTypeCombo;
    KTextEdit *mStreetTextEdit;
    KComboBox *mCountryCombo;
    QLineEdit *mRegionEdit;
    QLineEdit *mLocalityEdit;
    QLineEdit *mPostalCodeEdit;
    QLineEdit *mPOBoxEdit;
    QCheckBox *mPreferredCheckBox;

    KContacts::Address mAddress;
    QString mLabel;
};

#endif
