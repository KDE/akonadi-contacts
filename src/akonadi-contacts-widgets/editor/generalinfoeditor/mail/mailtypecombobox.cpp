/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mailtypecombobox.h"

#include <KContacts/Email>
#include <KLocalizedString>

using namespace Akonadi;

MailTypeCombobox::MailTypeCombobox(QWidget *parent)
    : Akonadi::ContactEditorComboBox(parent)
{
    addItem(i18n("Select..."), QVariant());
    addItem(i18n("Home"), (int)KContacts::Email::Home);
    addItem(i18n("Work"), (int)KContacts::Email::Work);
    addItem(i18n("Other"), (int)KContacts::Email::Other);
}

MailTypeCombobox::~MailTypeCombobox() = default;

#include "moc_mailtypecombobox.cpp"
