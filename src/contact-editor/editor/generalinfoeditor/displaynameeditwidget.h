/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include <kcontacts/addressee.h>

class KComboBox;

/**
 * @short A widget for editing the display name of a contact.
 *
 * The widget will either use a predefined schema for formatting
 * the name or a custom one.
 */
class DisplayNameEditWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Describes what the display name should look like.
     */
    enum DisplayType {
        SimpleName, ///< A name of the form: givenName familyName
        FullName, ///< A name of the form: prefix givenName additionalName familyName suffix
        ReverseNameWithComma, ///< A name of the form: familyName, givenName
        ReverseName, ///< A name of the form: familyName givenName
        Organization, ///< The organization name
        CustomName ///< Let the user input a display name
    };

    explicit DisplayNameEditWidget(QWidget *parent = nullptr);
    ~DisplayNameEditWidget() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);

    void setDisplayType(DisplayType type);
    Q_REQUIRED_RESULT DisplayType displayType() const;

public Q_SLOTS:
    void changeName(const KContacts::Addressee &contact);
    void changeOrganization(const QString &organization);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    void displayTypeChanged(int);
    void setComboBoxEditable(bool);
    void updateView();

    KComboBox *mView = nullptr;
    KContacts::Addressee mContact;
    QWidget *mViewport = nullptr;
    DisplayType mDisplayType = DisplayType::SimpleName;
    int mAdditionalPopupWidth;
};

