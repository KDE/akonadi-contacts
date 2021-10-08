/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "abstractcontacteditorwidget_p.h"
#include "contacteditor_export.h"

#include <memory>

namespace KContacts
{
class Addressee;
}

/**
 * @short A widget for editing a contact.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class CONTACTEDITOR_EXPORT ContactEditorWidget : public ContactEditor::AbstractContactEditorWidget
{
    Q_OBJECT
public:
    enum DisplayMode {
        FullMode, ///< Show all pages
        VCardMode ///< Show just pages with elements stored in vcard.
    };

    /**
     * Creates a new contact editor widget.
     *
     * @param parent The parent widget.
     */
    explicit ContactEditorWidget(QWidget *parent = nullptr);

    ContactEditorWidget(DisplayMode displayMode, QWidget *parent);

    /**
     * Destroys the contact editor widget.
     */
    ~ContactEditorWidget() override;

    /**
     * Initializes the fields of the contact editor
     * with the values from a @p contact.
     */
    void loadContact(const KContacts::Addressee &contact, const ContactEditor::ContactMetaDataBase &metaData) override;

    /**
     * Stores back the fields of the contact editor
     * into the given @p contact.
     */
    void storeContact(KContacts::Addressee &contact, ContactEditor::ContactMetaDataBase &metaData) const override;

    /**
     * Sets whether the contact in the editor allows
     * the user to edit the contact or not.
     */
    void setReadOnly(bool readOnly) override;

    Q_REQUIRED_RESULT bool hasNoSavedData() const override;

private:
    class Private;
    std::unique_ptr<Private> const d;
};

