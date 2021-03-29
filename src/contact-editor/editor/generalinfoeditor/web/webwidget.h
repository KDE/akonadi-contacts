/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include <kcontacts/resourcelocatorurl.h>
class QToolButton;
namespace ContactEditor
{
class WebSelectTypeCombobox;
class PreferredLineEditWidget;
class WebWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WebWidget(QWidget *parent = nullptr);
    ~WebWidget();
    void updateAddRemoveButton(bool addButtonEnabled);

    void clearWidget();
    void setPreferred(bool b);

    KContacts::ResourceLocatorUrl url();
    void loadWebSite(const KContacts::ResourceLocatorUrl &url);

    void setReadOnly(bool readOnly);

Q_SIGNALS:
    void addWidget(ContactEditor::WebWidget *);
    void removeWidget(ContactEditor::WebWidget *);
    void preferredChanged(ContactEditor::WebWidget *);

private:
    void slotRemoveWeb();
    void slotAddWeb();
    void slotPreferredChanged();
    KContacts::ResourceLocatorUrl mUrl;
    QStringList mWebSiteType;
    QString mOldType;
    PreferredLineEditWidget *mWebSiteEdit = nullptr;
    QToolButton *mAddButton = nullptr;
    QToolButton *mRemoveButton = nullptr;
    ContactEditor::WebSelectTypeCombobox *mWebType = nullptr;
};
}
