/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "contacteditor_private_export.h"
#include <KContacts/PhoneNumber>
#include <QDialog>
class QButtonGroup;

namespace ContactEditor
{
/**
 * A dialog for editing phone number types.
 */
class CONTACTEDITOR_TESTS_EXPORT PhoneTypeDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * Creates a new phone type dialog.
     *
     * @param type The initial type of the phone number.
     * @param parent The parent widget.
     */
    explicit PhoneTypeDialog(KContacts::PhoneNumber::Type type, QWidget *parent = nullptr);

    /**
     * Returns the selected type.
     */
    KContacts::PhoneNumber::Type type() const;

private:
    const KContacts::PhoneNumber::Type mType;
    KContacts::PhoneNumber::TypeList mTypeList;

    QButtonGroup *mGroup = nullptr;
};
}
