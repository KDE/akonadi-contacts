/*
    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressselectionwidgettest.h"

#include <KComboBox>
#include <QApplication>
#include <QTextBrowser>

#include <QGridLayout>
#include <QPushButton>
#include <QTreeView>

MainWidget::MainWidget()
    : QWidget(nullptr)
{
    auto layout = new QGridLayout(this);

    mAddressesWidget = new Akonadi::EmailAddressSelectionWidget;
    layout->addWidget(mAddressesWidget, 0, 0);

    mInfo = new QTextBrowser;
    layout->addWidget(mInfo, 0, 1);

    auto box = new KComboBox;
    box->addItem(QStringLiteral("Single Selection"));
    box->addItem(QStringLiteral("Multi Selection"));
    connect(box, QOverload<int>::of(&KComboBox::activated), this, &MainWidget::selectionModeChanged);
    layout->addWidget(box, 1, 0);

    auto button = new QPushButton(QStringLiteral("Show Selection"));
    connect(button, &QPushButton::clicked, this, &MainWidget::showSelection);
    layout->addWidget(button, 1, 1);
}

void MainWidget::selectionModeChanged(int index)
{
    mAddressesWidget->view()->setSelectionMode(index == 0 ? QTreeView::SingleSelection : QTreeView::MultiSelection);
}

void MainWidget::showSelection()
{
    mInfo->append(QStringLiteral("===========================\n"));
    mInfo->append(QStringLiteral("Current selection:\n"));

    const auto selectedAddress = mAddressesWidget->selectedAddresses();
    for (const Akonadi::EmailAddressSelection &selection : selectedAddress) {
        mInfo->append(QStringLiteral("%1: %2\n").arg(selection.name(), selection.email()));
    }
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWidget wdg;
    wdg.show();

    return app.exec();
}
