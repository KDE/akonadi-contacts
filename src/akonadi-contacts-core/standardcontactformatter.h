/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"

#include "abstractcontactformatter.h"

#include <memory>

namespace Akonadi
{
class StandardContactFormatterPrivate;

/*!
 * \class Akonadi::StandardContactFormatter
 * \brief A class that formats a contact as HTML code.
 * \inmodule AkonadiContactCore
 * \inheaderfile Akonadi/StandardContactFormatter
 *
 * Examples:
 *
 * \code
 *
 * using namespace Akonadi;
 *
 * const KContacts::Addressee contact = ...
 *
 * StandardContactFormatter formatter;
 * formatter.setContact( contact );
 *
 * QTextBrowser *view = new QTextBrowser;
 * view->setHtml( formatter.toHtml() );
 *
 * \endcode
 *
 * \author Tobias Koenig <tokoe@kde.org>
 * \since 4.5
 */
class AKONADI_CONTACT_CORE_EXPORT StandardContactFormatter : public AbstractContactFormatter
{
public:
    /*!
     * Creates a new standard contact formatter.
     */
    StandardContactFormatter();

    /*!
     * Destroys the standard contact formatter.
     */
    ~StandardContactFormatter() override;

    /*!
     * Returns the contact formatted as HTML.
     */
    [[nodiscard]] QString toHtml(HtmlForm form = SelfcontainedForm) const override;

    /*
     * \since 4.9.1
     */
    void setDisplayQRCode(bool show);
    /*
     * \since 4.9.1
     */
    [[nodiscard]] bool displayQRCode() const;

private:
    std::unique_ptr<StandardContactFormatterPrivate> const d;
};
}
