/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 Laurent Montel <montel@kde.org>

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
#ifndef BUSINESSEDITORWIDGET_H
#define BUSINESSEDITORWIDGET_H

#include <QWidget>
class KLineEdit;
class ImageWidget;
class FreeBusyEditWidget;
namespace KContacts
{
class Addressee;
}
namespace Akonadi
{
class BusinessEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BusinessEditorWidget(QWidget *parent = Q_NULLPTR);
    ~BusinessEditorWidget();
    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact);
    void setReadOnly(bool readOnly);

Q_SIGNALS:
    void organizationChanged(const QString &text);

private:
    KLineEdit *mOrganizationWidget;
    KLineEdit *mProfessionWidget;
    KLineEdit *mTitleWidget;
    KLineEdit *mDepartmentWidget;
    KLineEdit *mOfficeWidget;
    KLineEdit *mManagerWidget;
    KLineEdit *mAssistantWidget;
    FreeBusyEditWidget *mFreeBusyWidget;
    ImageWidget *mLogoWidget;
};
}
#endif // BUSINESSEDITORWIDGET_H
