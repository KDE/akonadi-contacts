/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <Akonadi/ItemMonitor>

#include <QWidget>

#include <memory>

namespace KContacts
{
class Address;
class Addressee;
class PhoneNumber;
}

namespace Akonadi
{
class AbstractContactFormatter;
class ContactViewerPrivate;

/**
 * @short A viewer component for contacts in Akonadi.
 *
 * This widgets provides a way to show a contact from the
 * Akonadi storage or a raw contact object.
 *
 * Examples:
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
 * @endcode

 * @code
 *
 * using namespace Akonadi;
 *
 * const KContacts::Addressee contact = ...
 *
 * ContactViewer *viewer = new ContactViewer( this );
 * viewer->setContact( contact );
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactViewer : public QWidget, public Akonadi::ItemMonitor
{
    Q_OBJECT

public:
    /**
     * Creates a new contact viewer.
     *
     * @param parent The parent widget.
     */
    explicit ContactViewer(QWidget *parent = nullptr);

    /**
     * Destroys the contact viewer.
     */
    ~ContactViewer() override;

    /**
     * Returns the contact that is currently displayed.
     *
     * @note The returned contact is only valid if it was
     *       set with setContact() before.
     */
    Q_REQUIRED_RESULT Akonadi::Item contact() const;

    /**
     * Returns the raw contact that is currently displayed.
     *
     * @since 4.5
     */
    Q_REQUIRED_RESULT KContacts::Addressee rawContact() const;

    /**
     * Sets the contact @p formatter that should be used for formatting the
     * contact. If formatter is @c 0, the standard formatter will be used.
     * @param formatter the contact formatter to set
     * @note The contact viewer won't take ownership of the formatter.
     *
     * @since 4.6
     */
    void setContactFormatter(AbstractContactFormatter *formatter);
    /**
     * @since 5.1
     */
    void updateView();

    /**
     * @since 5.2
     */
    void setShowQRCode(bool b);
    Q_REQUIRED_RESULT bool showQRCode() const;
public Q_SLOTS:
    /**
     * Sets the @p contact that shall be displayed in the viewer.
     */
    void setContact(const Akonadi::Item &contact);

    /**
     * Sets the raw @p contact object that shall be displayed in the viewer.
     * @param contact the contact object to set
     * @since 4.5
     */
    void setRawContact(const KContacts::Addressee &contact);

Q_SIGNALS:
    /**
     * This signal is emitted whenever the user has clicked on
     * a url (e.g. homepage or blog url) in the viewer.
     *
     * @param url The url that has been clicked.
     */
    void urlClicked(const QUrl &url);

    /**
     * This signal is emitted whenever the user has clicked on
     * an email address in the viewer.
     *
     * @param name The name of the contact.
     * @param email The plain email address of the contact.
     */
    void emailClicked(const QString &name, const QString &email);

    /**
     * This signal is emitted whenever the user has clicked on a
     * phone number (that includes fax numbers as well) in the viewer.
     *
     * @param number The corresponding phone number.
     */
    void phoneNumberClicked(const KContacts::PhoneNumber &number);

    /**
     * This signal is emitted whenever the user has clicked on a SMS link of a
     * phone number in the viewer.
     *
     * @param number The corresponding phone number.
     */
    void smsClicked(const KContacts::PhoneNumber &number);

    /**
     * This signal is emitted whenever the user has clicked on an
     * address in the viewer.
     *
     * @param address The corresponding address.
     */
    void addressClicked(const KContacts::Address &address);

private:
    /**
     * This method is called whenever the displayed contact has been changed.
     */
    void itemChanged(const Item &contact) override;

    /**
     * This method is called whenever the displayed contact has been
     * removed from Akonadi.
     */
    void itemRemoved() override;

private:
    //@cond PRIVATE
    std::unique_ptr<ContactViewerPrivate> const d;

    Q_PRIVATE_SLOT(d, void slotUrlClicked(const QUrl &))
    Q_PRIVATE_SLOT(d, void slotParentCollectionFetched(KJob *))
    //@endcond
};
}

