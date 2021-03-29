/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "contacteditor_private_export.h"
#include <KContacts/Addressee>
#include <QWidget>
class QComboBox;
class QCheckBox;
namespace ContactEditor
{
class CONTACTEDITOR_TESTS_EXPORT MessageFormattingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageFormattingWidget(QWidget *parent = nullptr);
    ~MessageFormattingWidget();

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);

private:
    QComboBox *mMailPreferFormatting = nullptr;
    QCheckBox *mAllowRemoteContent = nullptr;
};
}
