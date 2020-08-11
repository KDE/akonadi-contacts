/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CONTACTEDITOR_CONTACTEDITORPAGEPLUGIN_H
#define CONTACTEDITOR_CONTACTEDITORPAGEPLUGIN_H

#include <QWidget>

namespace KContacts {
class Addressee;
}

namespace ContactEditor {
/**
 * @short The base class for custom ContactEditor page plugins.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class ContactEditorPagePlugin : public QWidget
{
public:
    /**
     * Returns the i18n'd page title.
     */
    virtual QString title() const = 0;

    /**
     * This method is called to fill the editor widget with the data from @p contact.
     */
    virtual void loadContact(const KContacts::Addressee &contact) = 0;

    /**
     * This method is called to store the data from the editor widget into @p contact.
     */
    virtual void storeContact(KContacts::Addressee &contact) const = 0;

    /**
     * This method is called to set the editor widget @p readOnly.
     */
    virtual void setReadOnly(bool readOnly) = 0;
};
}

Q_DECLARE_INTERFACE(ContactEditor::ContactEditorPagePlugin, "org.freedesktop.Akonadi.ContactEditorPagePlugin/1.0")

#endif
