/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"
#include <Akonadi/Item>
#include <KJob>

#include <memory>

namespace Akonadi
{
class Item;
class AddEmailDisplayJobPrivate;

/*!
 * \class Akonadi::AddEmailDisplayJob
 * \brief The AddEmailDisplayJob class
 * \inmodule AkonadiContactWidgets
 * \inheaderfile Akonadi/AddEmailDisplayJob
 * \author Laurent Montel <montel@kde.org>
 */
class AKONADI_CONTACT_WIDGETS_EXPORT AddEmailDisplayJob : public KJob
{
    Q_OBJECT

public:
    explicit AddEmailDisplayJob(const QString &email, QWidget *parentWidget, QObject *parent = nullptr);

    ~AddEmailDisplayJob() override;
    void setShowAsHTML(bool html);
    void setRemoteContent(bool b);
    void setContact(const Akonadi::Item &contact);
    void setMessageId(Akonadi::Item::Id id);

    void start() override;

Q_SIGNALS:
    void contactUpdated(const Akonadi::Item &contact, Akonadi::Item::Id id, bool showAsHTML, bool remoteContent);

private:
    friend class AddEmailDisplayJobPrivate;
    std::unique_ptr<AddEmailDisplayJobPrivate> const d;
};
}
