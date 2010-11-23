/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 Bjoern Ricks <bjoern.ricks@intevation.de>

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

#ifndef QWINCEDIALER_H
#define QWINCEDIALER_H

#include "qdialer.h"

#include <QtCore/QString>

class QWinCEDialer: public QDialer
{
  public:
    QWinCEDialer( const QString &applicationName );
    ~QWinCEDialer();

    bool dialNumber( const QString &number );
    bool sendSms( const QString &number, const QString &text );

};

#endif
