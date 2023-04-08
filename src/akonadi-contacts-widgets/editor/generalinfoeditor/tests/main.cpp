/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "../generalinfowidget.h"
#include <QApplication>
using namespace ContactEditor;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ContactEditor::GeneralInfoWidget w;
    w.show();
    return app.exec();
}
