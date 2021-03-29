/*
    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "emailaddressselectionwidget.h"

#include <QWidget>

class QTextBrowser;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();

private Q_SLOTS:
    void selectionModeChanged(int);
    void showSelection();

private:
    Akonadi::EmailAddressSelectionWidget *mAddressesWidget = nullptr;
    QTextBrowser *mInfo = nullptr;
};

