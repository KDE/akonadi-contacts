/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "contacteditor_export.h"
#include "contactviewer.h"

namespace KAddressBookGrantlee
{
class GrantleeContactFormatter;

/** Grantlee-based contact viewer. */
class CONTACTEDITOR_EXPORT GrantleeContactViewer : public Akonadi::ContactViewer
{
    Q_OBJECT
public:
    explicit GrantleeContactViewer(QWidget *parent = nullptr);
    ~GrantleeContactViewer() override;

    void setForceDisableQRCode(bool b);

private:
    Q_REQUIRED_RESULT CONTACTEDITOR_NO_EXPORT QString kaddressBookAbsoluteThemePath() const;
    KAddressBookGrantlee::GrantleeContactFormatter *const mFormatter;
};
}
