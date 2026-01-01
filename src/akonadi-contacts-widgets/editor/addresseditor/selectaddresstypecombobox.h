/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <KContacts/Address>
#include <QComboBox>

namespace Akonadi
{
/**
 * @short A widget for selecting the type of an address.
 */
class SelectAddressTypeComboBox : public QComboBox
{
    Q_OBJECT

public:
    /**
     * Creates a new address type combo.
     *
     * @param parent The parent widget.
     */
    explicit SelectAddressTypeComboBox(QWidget *parent = nullptr);

    /**
     * Destroys the address type combo.
     */
    ~SelectAddressTypeComboBox() override;

    /**
     * Sets the type that shall be selected in the combobox.
     * @param type KABC address type to set.
     */
    void setType(KContacts::Address::Type type);

    /**
     * Returns the type that is currently selected.
     */
    [[nodiscard]] KContacts::Address::Type type() const;

private Q_SLOTS:
    void selected(int);
    void otherSelected();

private:
    void update();

    KContacts::Address::Type mType = KContacts::Address::Home;
    int mLastSelected = 0;
    QList<int> mTypeList;
};

}
