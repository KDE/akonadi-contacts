/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "displaynameeditwidget.h"
#include <QDialog>

#include <KContacts/Addressee>

class KLineEdit;
class KComboBox;
namespace Akonadi
{
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
}
