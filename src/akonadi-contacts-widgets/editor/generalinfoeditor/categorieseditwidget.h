/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <KContacts/Addressee>
#include <KJob>
#include <QVariant>
#include <QWidget>
namespace Akonadi
{
class TagWidget;
}

/**
 * @short A widget for editing the categories of a contact.
 */
class CategoriesEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CategoriesEditWidget(QWidget *parent = nullptr);
    ~CategoriesEditWidget() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);

private:
    void onMissingTagCreated(KJob *);
    Akonadi::TagWidget *const mTagWidget;
};
