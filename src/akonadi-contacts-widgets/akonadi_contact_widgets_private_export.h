/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef AKONADI_CONTACT_WIDGETS_TESTS_EXPORT
#define AKONADI_CONTACT_WIDGETS_TESTS_EXPORT AKONADI_CONTACT_WIDGETS_EXPORT
#endif
#else /* not compiling tests */
#define AKONADI_CONTACT_WIDGETS_TESTS_EXPORT
#endif
