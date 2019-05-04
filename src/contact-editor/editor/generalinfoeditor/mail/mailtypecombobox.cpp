/*
    This file is part of Contact Editor.

    Copyright (C) 2016-2019 Laurent Montel <montel@kde.org>

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

#include "mailtypecombobox.h"

#include <KContacts/Email>
#include <KLocalizedString>

using namespace ContactEditor;

MailTypeCombobox::MailTypeCombobox(QWidget *parent)
    : ContactEditor::ContactEditorComboBox(parent)
{
    addItem(i18n("Select..."), QVariant());
    addItem(i18n("Home"), (int)KContacts::Email::Home);
    addItem(i18n("Work"), (int)KContacts::Email::Work);
    addItem(i18n("Other"), (int)KContacts::Email::Other);
}

MailTypeCombobox::~MailTypeCombobox() = default;
