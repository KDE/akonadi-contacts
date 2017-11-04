/*
    This file is part of Contact Editor.

    Copyright (C) 2017 Laurent Montel <montel@kde.org>

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

#ifndef ABSTRACTADDRESSLOCATIONWIDGET_H
#define ABSTRACTADDRESSLOCATIONWIDGET_H

#include <QWidget>

#include <KContacts/Addressee>
#include "contacteditor_export.h"

namespace ContactEditor {
class CONTACTEDITOR_EXPORT AbstractAddressLocationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractAddressLocationWidget(QWidget *parent = nullptr);
    ~AbstractAddressLocationWidget();

    virtual void loadContact(const KContacts::Addressee &contact);
    virtual void storeContact(KContacts::Addressee &contact) const;

    virtual void setReadOnly(bool readOnly);
};
}
#endif // ABSTRACTADDRESSLOCATIONWIDGET_H
