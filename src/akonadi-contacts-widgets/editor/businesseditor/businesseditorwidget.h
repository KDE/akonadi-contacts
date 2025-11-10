/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class KLineEdit;
namespace KContacts
{
class Addressee;
}
namespace Akonadi
{
class FreeBusyEditWidget;
class ImageWidget;
class BusinessEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BusinessEditorWidget(QWidget *parent = nullptr);
    ~BusinessEditorWidget() override;
    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact);
    void setReadOnly(bool readOnly);

Q_SIGNALS:
    void organizationChanged(const QString &text);

private:
    KLineEdit *const mOrganizationWidget;
    KLineEdit *const mProfessionWidget;
    KLineEdit *const mTitleWidget;
    KLineEdit *const mDepartmentWidget;
    KLineEdit *const mOfficeWidget;
    KLineEdit *const mManagerWidget;
    KLineEdit *const mAssistantWidget;
    Akonadi::FreeBusyEditWidget *const mFreeBusyWidget;
    ImageWidget *const mLogoWidget;
};
}
