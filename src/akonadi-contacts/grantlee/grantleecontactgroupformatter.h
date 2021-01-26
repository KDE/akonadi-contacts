/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef GRANTLEECONTACTGROUPFORMATTER_H
#define GRANTLEECONTACTGROUPFORMATTER_H

#include "abstractcontactgroupformatter.h"
#include "akonadi-contact_export.h"

namespace GrantleeTheme
{
class Theme;
}

namespace KAddressBookGrantlee
{
/**
 * @short A class that formats a contact group as HTML code.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class AKONADI_CONTACT_EXPORT GrantleeContactGroupFormatter : public Akonadi::AbstractContactGroupFormatter
{
public:
    /**
     * Creates a new grantlee contact group formatter.
     */
    explicit GrantleeContactGroupFormatter();

    void setGrantleeTheme(const GrantleeTheme::Theme &theme);
    void setAbsoluteThemePath(const QString &path);

    /**
     * Destroys the grantlee contact group formatter.
     */
    ~GrantleeContactGroupFormatter() override;

    /**
     * Returns the contact group formatted as HTML
     */
    Q_REQUIRED_RESULT QString toHtml(HtmlForm form = SelfcontainedForm) const override;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

#endif
