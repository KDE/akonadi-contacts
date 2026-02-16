/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "abstractcontactgroupformatter.h"
#include "akonadi-contact-core_export.h"

#include <memory>

namespace GrantleeTheme
{
class Theme;
}

namespace KAddressBookGrantlee
{
class GrantleeContactGroupFormatterPrivate;

/*!
 * \class KAddressBookGrantlee::GrantleeContactGroupFormatter
 * \brief A class that formats a contact group as HTML code.
 * \inmodule AkonadiContactCore
 * \inheaderfile Akonadi/GrantleeContactGroupFormatter
 *
 * \author Tobias Koenig <tokoe@kde.org>
 */
class AKONADI_CONTACT_CORE_EXPORT GrantleeContactGroupFormatter : public Akonadi::AbstractContactGroupFormatter
{
public:
    /*!
     * Creates a new grantlee contact group formatter.
     */
    explicit GrantleeContactGroupFormatter();

    /*!
     * Sets the Grantlee \a theme to be used for formatting the contact group.
     *
     * \a theme The Grantlee theme to apply.
     */
    void setGrantleeTheme(const GrantleeTheme::Theme &theme);

    /*!
     * Sets the absolute path to the Grantlee theme.
     *
     * \a path The absolute path to the theme directory.
     */
    void setAbsoluteThemePath(const QString &path);

    /*!
     * Destroys the grantlee contact group formatter.
     */
    ~GrantleeContactGroupFormatter() override;

    /*!
     * Returns the contact group formatted as HTML
     */
    [[nodiscard]] QString toHtml(HtmlForm form = SelfcontainedForm) const override;

private:
    std::unique_ptr<GrantleeContactGroupFormatterPrivate> const d;
};
}
