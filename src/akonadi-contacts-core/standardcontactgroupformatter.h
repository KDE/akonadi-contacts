/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"

#include "abstractcontactgroupformatter.h"

#include <memory>

namespace Akonadi
{
class StandardContactGroupFormatterPrivate;

/*!
 * \brief A class that formats a contact group as HTML code.
 *
 * Examples:
 *
 * \code
 *
 * using namespace Akonadi;
 *
 * const KContacts::ContactGroup group = ...
 *
 * StandardContactGroupFormatter formatter;
 * formatter.setContactGroup( group );
 *
 * QTextBrowser *view = new QTextBrowser;
 * view->setHtml( formatter.toHtml() );
 *
 * \endcode
 *
 * \author Tobias Koenig <tokoe@kde.org>
 * \since 4.6
 */
class AKONADI_CONTACT_CORE_EXPORT StandardContactGroupFormatter : public AbstractContactGroupFormatter
{
public:
    /*!
     * Creates a new standard contact group formatter.
     */
    StandardContactGroupFormatter();

    /*!
     * Destroys the standard contact group formatter.
     */
    ~StandardContactGroupFormatter() override;

    /*!
     * Returns the contact group formatted as HTML.
     */
    [[nodiscard]] QString toHtml(HtmlForm form = SelfcontainedForm) const override;

private:
    std::unique_ptr<StandardContactGroupFormatterPrivate> const d;
};
}
