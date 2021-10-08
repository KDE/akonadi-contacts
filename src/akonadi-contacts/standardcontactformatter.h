/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include "abstractcontactformatter.h"

#include <memory>

namespace Akonadi
{
/**
 * @short A class that formats a contact as HTML code.
 *
 * Examples:
 *
 * @code
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
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.5
 */
class AKONADI_CONTACT_EXPORT StandardContactFormatter : public AbstractContactFormatter
{
public:
    /**
     * Creates a new standard contact formatter.
     */
    StandardContactFormatter();

    /**
     * Destroys the standard contact formatter.
     */
    ~StandardContactFormatter() override;

    /**
     * Returns the contact formatted as HTML.
     */
    Q_REQUIRED_RESULT QString toHtml(HtmlForm form = SelfcontainedForm) const override;

    /*
     * @since 4.9.1
     */
    void setDisplayQRCode(bool show);
    /*
     * @since 4.9.1
     */
    bool displayQRCode() const;

private:
    //@cond PRIVATE
    class Private;
    std::unique_ptr<Private> const d;
    //@endcond
};
}

