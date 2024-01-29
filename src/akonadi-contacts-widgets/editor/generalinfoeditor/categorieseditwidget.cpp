/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorieseditwidget.h"

#include <Akonadi/Item>
#include <Akonadi/Tag>
#include <Akonadi/TagWidget>
#include <QHBoxLayout>
#include <akonadi/tagcreatejob.h>
using namespace Akonadi;
CategoriesEditWidget::CategoriesEditWidget(QWidget *parent)
    : QWidget(parent)
    , mTagWidget(new Akonadi::TagWidget(this))
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins({});
    layout->addWidget(mTagWidget);
}

CategoriesEditWidget::~CategoriesEditWidget() = default;

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
        if (category.startsWith(QLatin1StringView("akonadi:"))) {
            tags.append(Akonadi::Tag::fromUrl(QUrl(category)));
        } else {
            Akonadi::Tag missingTag = Akonadi::Tag(category);
            auto createJob = new Akonadi::TagCreateJob(missingTag, this);
            createJob->setMergeIfExisting(true);
            connect(createJob, &Akonadi::TagCreateJob::result, this, &CategoriesEditWidget::onMissingTagCreated);
        }
    }

    mTagWidget->setSelection(tags);
}

void CategoriesEditWidget::onMissingTagCreated(KJob *job)
{
    if (job->error()) {
        return;
    }
    auto createJob = static_cast<Akonadi::TagCreateJob *>(job);

    auto selectedTags{mTagWidget->selection()};
    selectedTags += createJob->tag();
    mTagWidget->setSelection(selectedTags);
}

void CategoriesEditWidget::storeContact(KContacts::Addressee &contact) const
{
    QStringList categories;

    const Akonadi::Tag::List tags = mTagWidget->selection();
    categories.reserve(tags.count());
    for (const Akonadi::Tag &tag : tags) {
        categories.append(tag.name());
    }

    contact.setCategories(categories);
}

#include "moc_categorieseditwidget.cpp"
