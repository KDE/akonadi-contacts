/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2007-2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "contactgroupeditor.h"

#include "ui_contactgroupeditor.h"

#include <collection.h>
#include <item.h>

class KJob;

namespace Akonadi
{
class ContactGroupModel;
class Monitor;

class Q_DECL_HIDDEN ContactGroupEditor::Private
{
public:
    Private(ContactGroupEditor *parent);
    ~Private();

    void itemFetchDone(KJob *job);
    void parentCollectionFetchDone(KJob *job);
    void storeDone(KJob *job);
    void itemChanged(const Akonadi::Item &item, const QSet<QByteArray> &notUsed);
    void memberChanged();
    void setReadOnly(bool);

    void adaptHeaderSizes();

    void loadContactGroup(const KContacts::ContactGroup &group);
    Q_REQUIRED_RESULT bool storeContactGroup(KContacts::ContactGroup &group);
    void setupMonitor();

    ContactGroupEditor::Mode mMode = ContactGroupEditor::Mode::CreateMode;
    Item mItem;
    Collection mDefaultCollection;
    Ui::ContactGroupEditor mGui;
    ContactGroupEditor *mParent = nullptr;
    ContactGroupModel *mGroupModel = nullptr;
    Monitor *mMonitor = nullptr;
    bool mReadOnly = false;
};
}

