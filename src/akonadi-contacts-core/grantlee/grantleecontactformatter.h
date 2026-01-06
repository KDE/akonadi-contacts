/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "abstractcontactformatter.h"
#include "akonadi-contact-core_export.h"

#include <memory>

namespace GrantleeTheme
{
class Theme;
}

namespace KAddressBookGrantlee
{
class GrantleeContactFormatterPrivate;

/*!
 * \brief A class that formats a contact as HTML code.
 *
 * \author Tobias Koenig <tokoe@kde.org>
 */
class AKONADI_CONTACT_CORE_EXPORT GrantleeContactFormatter : public Akonadi::AbstractContactFormatter
{
public:
    /*!
     * Creates a new grantlee contact formatter.
     */
    explicit GrantleeContactFormatter();

    /*!
     * Destroys the grantlee contact formatter.
     */
    ~GrantleeContactFormatter() override;

    void setAbsoluteThemePath(const QString &path);

    void setGrantleeTheme(const GrantleeTheme::Theme &theme);

    void setForceDisableQRCode(bool b);
    [[nodiscard]] bool forceDisableQRCode() const;

    /*!
     * Returns the contact formatted as HTML
     */
    [[nodiscard]] QString toHtml(HtmlForm form = SelfcontainedForm) const override;

    void setShowQRCode(bool b);

    /*! Translation domain for the Grantlee localizer. */
    void setApplicationDomain(const QByteArray &domain);

private:
    std::unique_ptr<GrantleeContactFormatterPrivate> const d;
};
}
