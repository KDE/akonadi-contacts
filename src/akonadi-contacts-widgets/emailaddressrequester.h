/*
    SPDX-FileCopyrightText: 2001 Marc Mutz <mutz@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

#include <QWidget>

#include <memory>

class KLineEdit;

namespace Akonadi
{
class EmailAddressRequesterPrivate;

/**
 * @short A widget to input one or more email addresses.
 *
 * @author Marc Mutz <mutz@kde.org>
 */
class AKONADI_CONTACT_WIDGETS_EXPORT EmailAddressRequester : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged USER true)

public:
    /**
     * Creates a new email address requester.
     *
     * @param parent The parent widget.
     */
    explicit EmailAddressRequester(QWidget *parent = nullptr);

    /**
     * Destroys the email address requester.
     */
    ~EmailAddressRequester() override;

    /**
     * Clears the text of the email address requester.
     */
    void clear();

    /**
     * Sets the @p text of the email address requester.
     */
    void setText(const QString &text);

    /**
     * Returns the text of the email address requester.
     */
    [[nodiscard]] QString text() const;

    /**
     * Returns the line edit that is used by the email address requester.
     */
    KLineEdit *lineEdit() const;

Q_SIGNALS:
    /**
     * This signal is emitted whenever the text of the email address requester
     * has been changed.
     */
    void textChanged();

private:
    //@cond PRIVATE
    std::unique_ptr<EmailAddressRequesterPrivate> const d;
    //@endcond
};
}
