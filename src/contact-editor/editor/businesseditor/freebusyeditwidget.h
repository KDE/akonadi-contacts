/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef FREEBUSYEDITWIDGET_H
#define FREEBUSYEDITWIDGET_H

#include <QWidget>

namespace KContacts {
class Addressee;
}

class KUrlRequester;

class FreeBusyEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FreeBusyEditWidget(QWidget *parent = nullptr);
    ~FreeBusyEditWidget();

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);

private:
    KUrlRequester *mURL = nullptr;
    bool mReadOnly = false;
};

#endif
