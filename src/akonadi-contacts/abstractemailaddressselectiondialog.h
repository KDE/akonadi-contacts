/*
   Copyright (C) 2019 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef ABSTRACTEMAILADDRESSSELECTIONDIALOG_H
#define ABSTRACTEMAILADDRESSSELECTIONDIALOG_H

#include "akonadi-contact_export.h"

#include "emailaddressselectionwidget.h"

#include <QDialog>
#include <KContacts/Addressee>
namespace Akonadi {
class AKONADI_CONTACT_EXPORT AbstractEmailAddressSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AbstractEmailAddressSelectionDialog(QWidget *parent = nullptr);
    virtual ~AbstractEmailAddressSelectionDialog();

    /**
     * Returns the list of selected email addresses.
     */
    Q_REQUIRED_RESULT virtual EmailAddressSelection::List selectedAddresses() const = 0;

    /**
     * Returns the email address selection view that is used.
     */
    Q_REQUIRED_RESULT virtual EmailAddressSelectionWidget *view() const = 0;
Q_SIGNALS:
    void insertAddresses(const KContacts::Addressee::List &list);
};
}

#endif // ABSTRACTEMAILADDRESSSELECTIONDIALOG_H
