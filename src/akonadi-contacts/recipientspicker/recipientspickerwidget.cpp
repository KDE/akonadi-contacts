/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "recipientspickerwidget.h"
#include "contactstreemodel.h"
#include "emailaddressselectionmodel.h"
#include "emailaddressselectionwidget.h"
#include "recipientseditormanager.h"
#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QTreeView>

using namespace Akonadi;
RecipientsPickerWidget::RecipientsPickerWidget(bool onlyShowEmailWithAddress, QAbstractItemModel *model, QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins({});

    mView =
        new Akonadi::EmailAddressSelectionWidget(onlyShowEmailWithAddress, model ? model : Akonadi::RecipientsEditorManager::self()->model()->model(), this);
    layout->addWidget(mView);
    mView->view()->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mView->view()->setAlternatingRowColors(true);
    mView->view()->setSortingEnabled(true);
    mView->view()->sortByColumn(0, Qt::AscendingOrder);
}

RecipientsPickerWidget::~RecipientsPickerWidget()
{
}

QTreeView *RecipientsPickerWidget::view() const
{
    return mView->view();
}

Akonadi::EmailAddressSelectionWidget *RecipientsPickerWidget::emailAddressSelectionWidget() const
{
    return mView;
}
