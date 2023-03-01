# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"akonadicontact5-serializer\")

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()

add_library(akonadi_serializer_addressee MODULE)
target_sources(akonadi_serializer_addressee PRIVATE
    akonadi_serializer_addressee.cpp
    akonadi_serializer_addressee.h
)


ecm_qt_declare_logging_category(akonadi_serializer_addressee HEADER serializer_debug.h IDENTIFIER AKONADI_SERIALIZER_CONTACT_LOG CATEGORY_NAME org.kde.pim.contact_serializer
        DESCRIPTION "serializer contact (plugin)"
        EXPORT AKONADICONTACTS
    )


target_link_libraries(akonadi_serializer_addressee
    KF${KF_MAJOR_VERSION}::Contacts
    KPim${KF_MAJOR_VERSION}::AkonadiCore
    KF${KF_MAJOR_VERSION}::I18n
)
install(TARGETS akonadi_serializer_addressee
    DESTINATION ${KDE_INSTALL_PLUGINDIR}
)
install(FILES akonadi_serializer_addressee.desktop
    DESTINATION ${KDE_INSTALL_DATADIR}/akonadi/plugins/serializer
)

##################################

add_library(akonadi_serializer_contactgroup MODULE)
target_sources(akonadi_serializer_contactgroup PRIVATE
    akonadi_serializer_contactgroup.cpp
    akonadi_serializer_contactgroup.h
)
target_link_libraries(akonadi_serializer_contactgroup
    KF${KF_MAJOR_VERSION}::Contacts
    KPim${KF_MAJOR_VERSION}::AkonadiCore
    KF${KF_MAJOR_VERSION}::I18n
    KPim${KF_MAJOR_VERSION}::AkonadiContact
)
install(TARGETS akonadi_serializer_contactgroup
    DESTINATION ${KDE_INSTALL_PLUGINDIR}
)
install(FILES akonadi_serializer_contactgroup.desktop
    DESTINATION ${KDE_INSTALL_DATADIR}/akonadi/plugins/serializer
)
