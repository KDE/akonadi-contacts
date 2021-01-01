/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef BUSINESSEDITORWIDGET_H
#define BUSINESSEDITORWIDGET_H

#include <QWidget>
class KLineEdit;
class ImageWidget;
class FreeBusyEditWidget;
namespace KContacts {
class Addressee;
}
namespace ContactEditor {
class BusinessEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BusinessEditorWidget(QWidget *parent = nullptr);
    ~BusinessEditorWidget();
    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact);
    void setReadOnly(bool readOnly);

Q_SIGNALS:
    void organizationChanged(const QString &text);

private:
    KLineEdit *mOrganizationWidget = nullptr;
    KLineEdit *mProfessionWidget = nullptr;
    KLineEdit *mTitleWidget = nullptr;
    KLineEdit *mDepartmentWidget = nullptr;
    KLineEdit *mOfficeWidget = nullptr;
    KLineEdit *mManagerWidget = nullptr;
    KLineEdit *mAssistantWidget = nullptr;
    FreeBusyEditWidget *mFreeBusyWidget = nullptr;
    ImageWidget *mLogoWidget = nullptr;
};
}
#endif // BUSINESSEDITORWIDGET_H
