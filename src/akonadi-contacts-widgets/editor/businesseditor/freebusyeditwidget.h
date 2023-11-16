/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>

namespace KContacts
{
class Addressee;
}

class KUrlRequester;
namespace Akonadi
{
class FreeBusyEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FreeBusyEditWidget(QWidget *parent = nullptr);
    ~FreeBusyEditWidget() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);

private:
    KUrlRequester *mURL = nullptr;
};
}
