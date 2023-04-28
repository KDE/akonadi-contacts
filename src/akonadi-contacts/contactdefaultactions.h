/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <QObject>

#include <memory>

class QUrl;

namespace Akonadi
{
class ContactDefaultActionsPrivate;

/**
 * @short A convenience class that handles different contact related actions.
 *
 * This class handles contact related actions like opening an email address,
 * showing the address of a contact on a map etc.
 *
 * Example:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * const Item contact = ...
 *
 * ContactViewer *viewer = new ContactViewer( this );
 * viewer->setContact( contact );
 *
 * ContactDefaultActions *actions = new ContactDefaultActions( this );
 * actions->connectToView( viewer );
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactDefaultActions : public QObject
{
    Q_OBJECT

public:
    /**
     * Creates a new contact default actions object.
     *
     * @param parent The parent object.
     */
    explicit ContactDefaultActions(QObject *parent = nullptr);

    /**
     * Destroys the contact default actions object.
     */
    ~ContactDefaultActions() override;

    /**
     * Tries to connect the well known signals of the @p view
     * to the well known slots of this object.
     */
    void connectToView(QObject *view);

public Q_SLOTS:
    /**
     * Shows the given @p url in the users preferred webbrowser.
     */
    void showUrl(const QUrl &url);

private:
    //@cond PRIVATE
    std::unique_ptr<ContactDefaultActionsPrivate> const d;
    //@endcond PRIVATE
};
}
