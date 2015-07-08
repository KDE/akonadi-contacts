/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

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

#ifndef IMADDRESS_H
#define IMADDRESS_H

#include <QVector>
#include <QString>

class IMAddress
{
public:
    typedef QVector<IMAddress> List;

    IMAddress();
    IMAddress(const QString &protocol, const QString &name, bool preferred);

    void setProtocol(const QString &protocol);
    QString protocol() const;

    void setName(const QString &name);
    QString name() const;

    void setPreferred(bool preferred);
    bool preferred() const;

private:
    QString mProtocol;
    QString mName;
    bool mPreferred;
};

#endif // IMADDRESS_H
