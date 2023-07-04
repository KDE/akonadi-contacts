/*
    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressselectiondialog.h"

#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Akonadi::EmailAddressSelectionDialog dlg;
    if (dlg.exec()) {
        const auto selectedAddress = dlg.selectedAddresses();

        for (const Akonadi::EmailAddressSelection &selection : selectedAddress) {
            qDebug("%s: %s", qPrintable(selection.name()), qPrintable(selection.email()));
        }
    }
    return 0;
}
