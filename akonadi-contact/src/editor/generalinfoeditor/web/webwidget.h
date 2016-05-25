/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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

#ifndef WEBWIDGET_H
#define WEBWIDGET_H

#include <QWidget>

#include <kcontacts/resourcelocatorurl.h>
class QToolButton;
namespace Akonadi
{
class AkonadiContactSelectTypeCombobox;
class PreferredLineEditWidget;
class WebWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WebWidget(QWidget *parent = Q_NULLPTR);
    ~WebWidget();
    void updateAddRemoveButton(bool addButtonEnabled);

    void clearWidget();
    void setPreferred(bool b);

    KContacts::ResourceLocatorUrl url();
    void loadWebSite(const KContacts::ResourceLocatorUrl &url);

Q_SIGNALS:
    void addWidget(WebWidget *);
    void removeWidget(WebWidget *);
    void preferredChanged(WebWidget *);

private Q_SLOTS:
    void slotRemoveWeb();
    void slotAddWeb();
    void slotPreferredChanged();
private:
    KContacts::ResourceLocatorUrl mUrl;
    QStringList mWebSiteType;
    QString mOldType;
    PreferredLineEditWidget *mWebSiteEdit;
    QToolButton *mAddButton;
    QToolButton *mRemoveButton;
    Akonadi::AkonadiContactSelectTypeCombobox *mWebType;
};
}
#endif // WEBWIDGET_H
