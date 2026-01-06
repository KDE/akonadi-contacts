/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

#include <Akonadi/ItemMonitor>

#include <QWidget>

#include <memory>

namespace Akonadi
{
class AbstractContactGroupFormatter;
class ContactGroupViewerPrivate;

/*!
 * \brief A viewer component for contact groups in Akonadi.
 *
 * This widgets provides a way to show a contact group from the
 * Akonadi storage.
 *
 * Example:
 *
 * \code
 *
 * using namespace Akonadi;
 *
 * const Item group = ...
 *
 * ContactGroupViewer *viewer = new ContactGroupViewer( this );
 * viewer->setContactGroup( group );
 *
 * \endcode
 *
 * \author Tobias Koenig <tokoe@kde.org>
 * \since 4.4
 */
class AKONADI_CONTACT_WIDGETS_EXPORT ContactGroupViewer : public QWidget, public Akonadi::ItemMonitor
{
    Q_OBJECT

public:
    /*!
     * Creates a new contact group viewer.
     *
     * \a parent The parent widget.
     */
    explicit ContactGroupViewer(QWidget *parent = nullptr);

    /*!
     * Destroys the contact group viewer.
     */
    ~ContactGroupViewer() override;

    /*!
     * Returns the contact group that is currently displayed.
     */
    [[nodiscard]] Akonadi::Item contactGroup() const;

    /*!
     * Sets the contact group \a formatter that should be used for formatting the
     * contact group. If formatter is \\ 0, the standard formatter will be used.
     * \a formatter the formatter to use
     * \note The contact viewer won't take ownership of the formatter.
     * \since 4.6
     */
    void setContactGroupFormatter(Akonadi::AbstractContactGroupFormatter *formatter);

    /*!
     * \since 5.20.41
     */
    void updateView();

public Q_SLOTS:
    /*!
     * Sets the contact \a group that shall be displayed in the viewer.
     */
    void setContactGroup(const Akonadi::Item &group);

Q_SIGNALS:
    /*!
     * This signal is emitted whenever the user has clicked on
     * a URL in the viewer (e.g. a mailto: link).
     *
     * \a url The url that has been clicked.
     */
    void urlClicked(const QUrl &url);

private:
    /*!
     * This method is called whenever the displayed contact \a group has been changed.
     */
    AKONADI_CONTACT_WIDGETS_NO_EXPORT void itemChanged(const Akonadi::Item &group) override;

    /*!
     * This method is called whenever the displayed contact group has been
     * removed from Akonadi.
     */
    AKONADI_CONTACT_WIDGETS_NO_EXPORT void itemRemoved() override;

private:
    std::unique_ptr<ContactGroupViewerPrivate> const d;
};
}
