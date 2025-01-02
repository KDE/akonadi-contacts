/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "abstractemailaddressselectiondialog.h"

using namespace Akonadi;
AbstractEmailAddressSelectionDialog::AbstractEmailAddressSelectionDialog(QWidget *parent)
    : QDialog(parent)
{
}

AbstractEmailAddressSelectionDialog::~AbstractEmailAddressSelectionDialog() = default;

#include "moc_abstractemailaddressselectiondialog.cpp"
