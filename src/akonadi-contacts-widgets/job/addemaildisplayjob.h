/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "contacteditor_export.h"
#include <Akonadi/Item>
#include <KJob>

#include <memory>

namespace AkonadiContactWidgets
{
class Item;
class AddEmailDisplayJobPrivate;

/**
 * @brief The AddEmailDisplayJob class
 * @author Laurent Montel <montel@kde.org>
 */
class CONTACTEDITOR_EXPORT AddEmailDisplayJob : public KJob
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
    //@cond PRIVATE
    friend class AddEmailDisplayJobPrivate;
    std::unique_ptr<AddEmailDisplayJobPrivate> const d;
    //@endcond
};
}
