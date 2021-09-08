/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <Akonadi/ItemMonitor>

#include <QWidget>

namespace Akonadi
{
class AbstractContactGroupFormatter;

/**
 * @short A viewer component for contact groups in Akonadi.
 *
 * This widgets provides a way to show a contact group from the
 * Akonadi storage.
 *
 * Example:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * const Item group = ...
 *
 * ContactGroupViewer *viewer = new ContactGroupViewer( this );
 * viewer->setContactGroup( group );
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactGroupViewer : public QWidget, public Akonadi::ItemMonitor
{
    Q_OBJECT

public:
    /**
     * Creates a new contact group viewer.
     *
     * @param parent The parent widget.
     */
    explicit ContactGroupViewer(QWidget *parent = nullptr);

    /**
     * Destroys the contact group viewer.
     */
    ~ContactGroupViewer() override;

    /**
     * Returns the contact group that is currently displayed.
     */
    Akonadi::Item contactGroup() const;

    /**
     * Sets the contact group @p formatter that should be used for formatting the
     * contact group. If formatter is @c 0, the standard formatter will be used.
     * @param formatter the formatter to use
     * @note The contact viewer won't take ownership of the formatter.
     * @since 4.6
     */
    void setContactGroupFormatter(AbstractContactGroupFormatter *formatter);

public Q_SLOTS:
    /**
     * Sets the contact @p group that shall be displayed in the viewer.
     */
    void setContactGroup(const Akonadi::Item &group);

Q_SIGNALS:
    /**
     * This signal is emitted whenever the user has clicked on
     * an email address in the viewer.
     *
     * @param name The name of the contact.
     * @param email The plain email address of the contact.
     */
    void emailClicked(const QString &name, const QString &email);

private:
    /**
     * This method is called whenever the displayed contact @p group has been changed.
     */
    void itemChanged(const Item &group) override;

    /**
     * This method is called whenever the displayed contact group has been
     * removed from Akonadi.
     */
    void itemRemoved() override;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

