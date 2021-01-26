/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactgroupviewerdialog.h"

#include "contactgroupviewer.h"

#include <KLocalizedString>
#include <item.h>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Akonadi;

class Q_DECL_HIDDEN ContactGroupViewerDialog::Private
{
public:
    ContactGroupViewer *mViewer = nullptr;
};

ContactGroupViewerDialog::ContactGroupViewerDialog(QWidget *parent)
    : QDialog(parent)
    , d(new Private)
{
    setWindowTitle(i18nc("@title:window", "Show Contact Group"));
    auto *mainLayout = new QVBoxLayout(this);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ContactGroupViewerDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ContactGroupViewerDialog::reject);

    mainLayout->addWidget(d->mViewer);
    mainLayout->addWidget(buttonBox);

    resize(QSize(500, 600));
}

ContactGroupViewerDialog::~ContactGroupViewerDialog()
{
    delete d;
}

Akonadi::Item ContactGroupViewerDialog::contactGroup() const
{
    return d->mViewer->contactGroup();
}

ContactGroupViewer *ContactGroupViewerDialog::viewer() const
{
    return d->mViewer;
}

void ContactGroupViewerDialog::setContactGroup(const Akonadi::Item &group)
{
    d->mViewer->setContactGroup(group);
}
