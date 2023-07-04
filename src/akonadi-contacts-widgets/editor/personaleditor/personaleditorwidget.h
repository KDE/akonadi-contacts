/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class DateEditWidget;
class KLineEdit;
namespace KContacts
{
class Addressee;
}

namespace Akonadi
{
class PersonalEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PersonalEditorWidget(QWidget *parent = nullptr);
    ~PersonalEditorWidget() override;
    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact);
    void setReadOnly(bool readOnly);

private:
    DateEditWidget *mBirthdateWidget = nullptr;
    DateEditWidget *mAnniversaryWidget = nullptr;
    KLineEdit *mPartnerWidget = nullptr;
};
}
