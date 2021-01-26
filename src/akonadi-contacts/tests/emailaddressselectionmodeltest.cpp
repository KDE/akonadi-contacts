/*
    SPDX-FileCopyrightText: 2017 David Faure <faure@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressselectionmodel.h"
#include <Akonadi/Contact/ContactsTreeModel>
#include <QTreeView>

#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Akonadi::EmailAddressSelectionModel model;
    QTreeView view;
    view.setModel(model.model());
    view.show();

    return app.exec();
}
