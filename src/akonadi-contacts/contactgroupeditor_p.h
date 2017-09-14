/*
    This file is part of Akonadi Contact.

    Copyright (c) 2007-2010 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef AKONADI_CONTACTGROUPEDITOR_P_H
#define AKONADI_CONTACTGROUPEDITOR_P_H

#include "contactgroupeditor.h"

#include "ui_contactgroupeditor.h"

#include <collection.h>
#include <item.h>

class KJob;

namespace Akonadi {
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
    bool storeContactGroup(KContacts::ContactGroup &group);
    void setupMonitor();

    ContactGroupEditor *mParent = nullptr;
    ContactGroupEditor::Mode mMode;
    Item mItem;
    Monitor *mMonitor = nullptr;
    Collection mDefaultCollection;
    Ui::ContactGroupEditor mGui;
    bool mReadOnly;
    ContactGroupModel *mGroupModel = nullptr;
};
}

#endif