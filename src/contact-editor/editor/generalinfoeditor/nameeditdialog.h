/*
    This file is part of Contact Editor.

    Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

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

#ifndef NAMEEDITDIALOG_H
#define NAMEEDITDIALOG_H

#include "displaynameeditwidget.h"
#include <QDialog>

#include <KContacts/Addressee>

class KLineEdit;
class KComboBox;
class DisplayNameEditWidget;
class NameEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NameEditDialog(QWidget *parent = nullptr);

    void setFamilyName(const QString &name);
    Q_REQUIRED_RESULT QString familyName() const;

    void setGivenName(const QString &name);
    Q_REQUIRED_RESULT QString givenName() const;

    void setPrefix(const QString &prefix);
    Q_REQUIRED_RESULT QString prefix() const;

    void setSuffix(const QString &suffix);
    Q_REQUIRED_RESULT QString suffix() const;

    void setAdditionalName(const QString &name);
    Q_REQUIRED_RESULT QString additionalName() const;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

    void setDisplayType(DisplayNameEditWidget::DisplayType type);
    Q_REQUIRED_RESULT DisplayNameEditWidget::DisplayType displayType() const;
private:
    KComboBox *mSuffixCombo = nullptr;
    KComboBox *mPrefixCombo = nullptr;
    KLineEdit *mFamilyNameEdit = nullptr;
    KLineEdit *mGivenNameEdit = nullptr;
    KLineEdit *mAdditionalNameEdit = nullptr;
    DisplayNameEditWidget *mDisplayNameEdit = nullptr;
};

#endif
