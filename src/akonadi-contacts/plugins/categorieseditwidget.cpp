/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorieseditwidget.h"

#include <item.h>
#include <tag.h>
#include <tagwidget.h>
#include <QHBoxLayout>
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(CategoriesEditWidget, "categorieseditwidgetplugin.json")

CategoriesEditWidget::CategoriesEditWidget(QWidget *parent, const QList<QVariant> &)
    : ContactEditor::CategoriesEditAbstractWidget(parent)
{
    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    mTagWidget = new Akonadi::TagWidget(this);
    layout->addWidget(mTagWidget);
}

CategoriesEditWidget::~CategoriesEditWidget()
{
}

void CategoriesEditWidget::setReadOnly(bool readOnly)
{
    mTagWidget->setReadOnly(readOnly);
}

void CategoriesEditWidget::loadContact(const KContacts::Addressee &contact)
{
    Akonadi::Tag::List tags;

    const QStringList categories = contact.categories();
    tags.reserve(categories.count());
    for (const QString &category : categories) {
        tags.append(Akonadi::Tag::fromUrl(QUrl(category)));
    }

    mTagWidget->setSelection(tags);
}

void CategoriesEditWidget::storeContact(KContacts::Addressee &contact) const
{
    QStringList categories;

    const Akonadi::Tag::List tags = mTagWidget->selection();
    categories.reserve(tags.count());
    for (const Akonadi::Tag &tag : tags) {
        categories.append(tag.url().url());
    }

    contact.setCategories(categories);
}

#include "categorieseditwidget.moc"
