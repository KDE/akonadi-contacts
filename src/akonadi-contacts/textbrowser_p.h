/*
    This file is part of Akonadi Contact.
    SPDX-FileCopyrightText: 2012-2022 Laurent Montel <montel@kde.org>

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QTextBrowser>

namespace Akonadi
{
/**
 * A convenience class to remove the 'Copy Link Location' action
 * from the context menu of QTextBrowser.
 */
class TextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    explicit TextBrowser(QWidget *parent = nullptr);

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif
private:
    void slotCopyData();
    QVariant mDataToCopy;
};
}
