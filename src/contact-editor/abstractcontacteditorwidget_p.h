/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>

namespace KContacts
{
class Addressee;
}

namespace ContactEditor
{
class ContactMetaDataBase;

class AbstractContactEditorWidget : public QWidget
{
public:
    /**
     * Creates a new abstract contact editor widget.
     *
     * @param parent The parent widget.
     */
    explicit AbstractContactEditorWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
    }

    /**
     * Destroys the abstract contact editor widget.
     */
    ~AbstractContactEditorWidget()
    {
    }

    /**
     * @param contact loads the given contact into the editor widget
     */
    virtual void loadContact(const KContacts::Addressee &contact, const ContactEditor::ContactMetaDataBase &metaData) = 0;

    /**
     * @param contact store the given contact into the editor widget
     */
    virtual void storeContact(KContacts::Addressee &contact, ContactEditor::ContactMetaDataBase &metaData) const = 0;

    /**
     * @param readOnly set read-only mode
     */
    virtual void setReadOnly(bool readOnly) = 0;

    virtual Q_REQUIRED_RESULT bool hasNoSavedData() const
    {
        return false;
    }
};
}

