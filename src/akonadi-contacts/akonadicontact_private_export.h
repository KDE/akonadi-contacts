/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef AKONADICONTACT_PRIVATE_EXPORT_H
#define AKONADICONTACT_PRIVATE_EXPORT_H

#include "akonadi-contact_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
# ifndef AKONADI_CONTACTS_TESTS_EXPORT
#  define AKONADI_CONTACTS_TESTS_EXPORT AKONADI_CONTACT_EXPORT
# endif
#else /* not compiling tests */
# define AKONADI_CONTACTS_TESTS_EXPORT
#endif

#endif
