/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactviewerdialog.h"
#include "contactviewer.h"
#include "contactdefaultactions.h"

#include <item.h>
using namespace Akonadi;

#include <KConfig>
#include <KLocalizedString>

#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <QPushButton>

class Q_DECL_HIDDEN ContactViewerDialog::Private
{
public:
    Private(ContactViewerDialog *parent)
        : q(parent)
    {
    }

    void readConfig()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("ContactViewer"));
        const QSize size = group.readEntry("Size", QSize(500, 600));
        if (size.isValid()) {
            q->resize(size);
        }
    }

    void writeConfig()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("ContactViewer"));
        group.writeEntry("Size", q->size());
        group.sync();
    }

    ContactViewerDialog *const q;
    ContactViewer *mViewer = nullptr;
};

ContactViewerDialog::ContactViewerDialog(QWidget *parent)
    : QDialog(parent)
    , d(new Private(this))
{
    setWindowTitle(i18nc("@title:window", "Show Contact"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    QWidget *mainWidget = new QWidget(this);
    mainLayout->addWidget(mainWidget);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ContactViewerDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ContactViewerDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout(mainWidget);

    d->mViewer = new ContactViewer(this);
    layout->addWidget(d->mViewer);

    ContactDefaultActions *actions = new ContactDefaultActions(this);
    actions->connectToView(d->mViewer);

    mainLayout->addWidget(buttonBox);

    d->readConfig();
}

ContactViewerDialog::~ContactViewerDialog()
{
    d->writeConfig();
    delete d;
}

Akonadi::Item ContactViewerDialog::contact() const
{
    return d->mViewer->contact();
}

ContactViewer *ContactViewerDialog::viewer() const
{
    return d->mViewer;
}

void ContactViewerDialog::setContact(const Akonadi::Item &contact)
{
    d->mViewer->setContact(contact);
}
