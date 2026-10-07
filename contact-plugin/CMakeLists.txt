# SPDX-FileCopyrightText: 2026 Carl Schwan <carlschwan@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(akonadiaddressbookplugin MODULE)
target_sources(akonadiaddressbookplugin PRIVATE
    akonadiaddressbookplugin.cpp
    akonadiaddressbookplugin.h
    singlecollectionaddressbook.cpp
    singlecollectionaddressbook.h
)
ecm_qt_declare_logging_category(akonadiaddressbookplugin
    HEADER akonadiaddressbookplugin_debug.h
    IDENTIFIER AKONADIADDRESSBOOKPLUGIN_LOG
    CATEGORY_NAME org.kde.kcontacts.akonadiplugin
    DESCRIPTION "KContacts (Akonadi plugin)"
    EXPORT AKONADICONTACTS
)
target_include_directories(akonadiaddressbookplugin PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(akonadiaddressbookplugin PRIVATE KF6::Contacts KPim6::AkonadiCore)
install(TARGETS akonadiaddressbookplugin DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/org.kde.kcontacts.addressbooks/)
