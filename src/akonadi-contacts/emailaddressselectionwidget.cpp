/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressselectionwidget.h"

#include "emailaddressselection_p.h"
#include "emailaddressselectionmodel.h"
#include "emailaddressselectionproxymodel_p.h"

#include <changerecorder.h>
#include <contactsfilterproxymodel.h>
#include <contactstreemodel.h>
#include <controlgui.h>
#include <entitydisplayattribute.h>
#include <entitytreeview.h>
#include <itemfetchscope.h>
#include <session.h>
#include <kcontacts/addressee.h>
#include <kcontacts/contactgroup.h>
#include <KLocalizedString>

#include <QTimer>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QKeyEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
using namespace Akonadi;

/**
 * @internal
 */
class SearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    SearchLineEdit(QWidget *receiver, QWidget *parent = nullptr)
        : QLineEdit(parent)
        , mReceiver(receiver)
    {
        setClearButtonEnabled(true);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Down) {
            QMetaObject::invokeMethod(mReceiver, "setFocus");
        }

        QLineEdit::keyPressEvent(event);
    }

private:
    QWidget *const mReceiver;
};

/**
 * @internal
 */
class Q_DECL_HIDDEN EmailAddressSelectionWidget::Private
{
public:
    Private(bool showOnlyContactWithEmail, EmailAddressSelectionWidget *qq, QAbstractItemModel *model)
        : q(qq)
        , mModel(model)
        , mShowOnlyContactWithEmail(showOnlyContactWithEmail)
    {
        init();
    }

    void init();

    EmailAddressSelectionWidget *q = nullptr;
    QAbstractItemModel *mModel = nullptr;
    QLabel *mDescriptionLabel = nullptr;
    SearchLineEdit *mSearchLine = nullptr;
    Akonadi::EntityTreeView *mView = nullptr;
    EmailAddressSelectionProxyModel *mSelectionModel = nullptr;
    bool mShowOnlyContactWithEmail = false;
};

void EmailAddressSelectionWidget::Private::init()
{
    // setup internal model if needed
    if (!mModel) {
        auto *model = new Akonadi::EmailAddressSelectionModel(q);
        mModel = model->model();
    }

    // setup ui
    auto *layout = new QVBoxLayout(q);
    layout->setContentsMargins(0, 0, 0, 0);

    mDescriptionLabel = new QLabel;
    mDescriptionLabel->hide();
    layout->addWidget(mDescriptionLabel);

    auto *searchLayout = new QHBoxLayout;
    searchLayout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(searchLayout);

    mView = new Akonadi::EntityTreeView;
    mView->setEditTriggers(Akonadi::EntityTreeView::NoEditTriggers);

    QLabel *label = new QLabel(i18nc("@label Search in a list of contacts", "Search:"));
    mSearchLine = new SearchLineEdit(mView);
    label->setBuddy(mSearchLine);
    searchLayout->addWidget(label);
    searchLayout->addWidget(mSearchLine);

#ifndef QT_NO_DRAGANDDROP
    mView->setDragDropMode(QAbstractItemView::NoDragDrop);
#endif
    layout->addWidget(mView);

    auto *filter = new Akonadi::ContactsFilterProxyModel(q);
    if (mShowOnlyContactWithEmail) {
        filter->setFilterFlags(ContactsFilterProxyModel::HasEmail);
    }
    filter->setMatchFilterContactFlag(ContactsFilterProxyModel::MatchFilterContactFlag::OnlyNameAndEmailsAddresses);
    filter->setExcludeVirtualCollections(true);
    filter->setSourceModel(mModel);

    mSelectionModel = new EmailAddressSelectionProxyModel(q);
    mSelectionModel->setSourceModel(filter);

    mView->setModel(mSelectionModel);
    mView->header()->hide();

    q->connect(mSearchLine, &QLineEdit::textChanged,
               filter, &ContactsFilterProxyModel::setFilterString);

    q->connect(mView, QOverload<const Akonadi::Item &>::of(&Akonadi::EntityTreeView::doubleClicked),
               q, [this]() { Q_EMIT q->doubleClicked(); });
    ControlGui::widgetNeedsAkonadi(q);

    mSearchLine->setFocus();

    if (auto *etm = qobject_cast<Akonadi::EntityTreeModel *>(mModel)) {
        QObject::connect(etm, &Akonadi::EntityTreeModel::collectionTreeFetched, mView, &QTreeView::expandAll);
    } else {
        QTimer::singleShot(1000, mView, &QTreeView::expandAll);
    }
}

EmailAddressSelectionWidget::EmailAddressSelectionWidget(QWidget *parent)
    : QWidget(parent)
    , d(new Private(true, this, nullptr))
{
}

EmailAddressSelectionWidget::EmailAddressSelectionWidget(QAbstractItemModel *model, QWidget *parent)
    : QWidget(parent)
    , d(new Private(true, this, model))
{
}

EmailAddressSelectionWidget::EmailAddressSelectionWidget(bool showOnlyContactWithEmail, QAbstractItemModel *model, QWidget *parent)
    : QWidget(parent)
    , d(new Private(showOnlyContactWithEmail, this, model))
{
}

EmailAddressSelectionWidget::~EmailAddressSelectionWidget()
{
    delete d;
}

EmailAddressSelection::List EmailAddressSelectionWidget::selectedAddresses() const
{
    EmailAddressSelection::List selections;

    if (!d->mView->selectionModel()) {
        return selections;
    }

    const QModelIndexList selectedRows = d->mView->selectionModel()->selectedRows(0);
    for (const QModelIndex &index : selectedRows) {
        EmailAddressSelection selection;
        selection.d->mName = index.data(EmailAddressSelectionProxyModel::NameRole).toString();
        selection.d->mEmailAddress = index.data(EmailAddressSelectionProxyModel::EmailAddressRole).toString();
        selection.d->mItem = index.data(ContactsTreeModel::ItemRole).value<Akonadi::Item>();

        if (d->mShowOnlyContactWithEmail) {
            if (!selection.d->mEmailAddress.isEmpty()) {
                selections << selection;
            }
        } else {
            selections << selection;
        }
    }

    return selections;
}

QLineEdit *EmailAddressSelectionWidget::searchLineEdit() const
{
    return d->mSearchLine;
}

QTreeView *EmailAddressSelectionWidget::view() const
{
    return d->mView;
}

#include "emailaddressselectionwidget.moc"
