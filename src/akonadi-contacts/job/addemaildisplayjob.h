/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ADDEMAILDISPLAYJOB_H
#define ADDEMAILDISPLAYJOB_H

#include "akonadi-contact_export.h"
#include <AkonadiCore/Item>
#include <KJob>

namespace Akonadi
{
class Item;
/**
 * @brief The AddEmailDisplayJob class
 * @author Laurent Montel <montel@kde.org>
 */
class AKONADI_CONTACT_EXPORT AddEmailDisplayJob : public KJob
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
    class Private;
    Private *const d;
    //@endcond
};
}

#endif
