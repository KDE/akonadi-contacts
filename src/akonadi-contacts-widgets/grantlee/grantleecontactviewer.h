/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"
#include "contactviewer.h"

namespace KAddressBookGrantlee
{
class GrantleeContactFormatter;

/*! Grantlee-based contact viewer. */
class AKONADI_CONTACT_WIDGETS_EXPORT GrantleeContactViewer : public Akonadi::ContactViewer
{
    Q_OBJECT
public:
    explicit GrantleeContactViewer(QWidget *parent = nullptr);
    ~GrantleeContactViewer() override;

    void setForceDisableQRCode(bool b);

private:
    [[nodiscard]] AKONADI_CONTACT_WIDGETS_NO_EXPORT QString kaddressBookAbsoluteThemePath() const;
    KAddressBookGrantlee::GrantleeContactFormatter *const mFormatter;
};
}
