/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2017 Laurent Montel <laurent.montel@kdab.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef CUSTOMFIELDEDITORWIDGET_H
#define CUSTOMFIELDEDITORWIDGET_H

#include <QWidget>
#include "customfields_p.h"
class QLineEdit;
class QPushButton;
class QCheckBox;
class QComboBox;
namespace ContactEditor {
class CustomFieldEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomFieldEditorWidget(QWidget *parent = nullptr);
    ~CustomFieldEditorWidget();
    void setReadOnly(bool readOnly);

Q_SIGNALS:
    void addNewField(const CustomField &field);

private:
    void slotAddField();
    void slotFielNameChanged(const QString &text);
    void fillTypes();
    QLineEdit *mFieldName = nullptr;
    QPushButton *mAddField = nullptr;
    QCheckBox *mUseAllContacts = nullptr;
    QComboBox *mFieldType = nullptr;
};
}
#endif // CUSTOMFIELDEDITORWIDGET_H