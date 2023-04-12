/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QPointer>
#include <QWidget>

class KJob;

/**
 * @internal
 * Overlay widget to block widgets while a job is running.
 */
class WaitingOverlay : public QWidget
{
    Q_OBJECT
public:
    /**
     * Create an overlay widget on @p baseWidget for @p job.
     * @param baseWidget must not be null.
     * @param parent must not be equal to baseWidget
     */
    explicit WaitingOverlay(KJob *job, QWidget *baseWidget, QWidget *parent = nullptr);
    ~WaitingOverlay() override;

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    void reposition();

private:
    QPointer<QWidget> mBaseWidget;
    bool mPreviousState;
};
