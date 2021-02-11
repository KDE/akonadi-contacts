/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRANTLEECONTACTVIEWER_H
#define GRANTLEECONTACTVIEWER_H

#include "akonadi-contact_export.h"
#include "contactviewer.h"

namespace KAddressBookGrantlee
{
class GrantleeContactFormatter;

/** Grantlee-based contact viewer. */
class AKONADI_CONTACT_EXPORT GrantleeContactViewer : public Akonadi::ContactViewer
{
    Q_OBJECT
public:
    explicit GrantleeContactViewer(QWidget *parent = nullptr);
    ~GrantleeContactViewer() override;

    void setForceDisableQRCode(bool b);

private:
    Q_REQUIRED_RESULT QString kaddressBookAbsoluteThemePath();
    KAddressBookGrantlee::GrantleeContactFormatter *const mFormatter;
};
}

#endif // GRANTLEECONTACTVIEWER_H
