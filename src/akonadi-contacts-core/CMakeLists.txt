# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

ecm_setup_version(PROJECT VARIABLE_PREFIX AKONADICONTACTCORE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_core_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactCoreConfigVersion.cmake"
    SOVERSION 6
)

add_library(KPim6AkonadiContactCore)
add_library(KPim6::AkonadiContactCore ALIAS KPim6AkonadiContactCore)
########### next target ###############

target_sources(
    KPim6AkonadiContactCore
    PRIVATE
        attributes/contactmetadataattribute.cpp
        attributes/attributeregistrar.cpp
)

target_sources(
    KPim6AkonadiContactCore
    PRIVATE
        job/contactgroupexpandjob.cpp
        job/contactgroupsearchjob.cpp
        job/contactsearchjob.cpp
)

target_sources(
    KPim6AkonadiContactCore
    PRIVATE
        grantlee/contactgrantleewrapper.cpp
        grantlee/grantleecontactformatter.cpp
        grantlee/grantleecontactgroupformatter.cpp
        grantlee/grantleeprint.cpp
)

target_sources(
    KPim6AkonadiContactCore
    PRIVATE
        abstractcontactformatter.cpp
        abstractcontactgroupformatter.cpp
        collectionfiltermodel.cpp
        contactcompletionmodel.cpp
        contactgroupmodel.cpp
        contactparts.cpp
        contactsfilterproxymodel.cpp
        contactstreemodel.cpp
        emailaddressselection.cpp
        emailaddressselectionproxymodel.cpp
        emailaddressselectionmodel.cpp
        leafextensionproxymodel.cpp
        standardcontactformatter.cpp
        standardcontactgroupformatter.cpp
        emailaddressselectionproxymodel_p.h
        job/contactgroupsearchjob.h
        job/contactsearchjob.h
        job/contactgroupexpandjob.h
        contactgroupmodel_p.h
        abstractcontactgroupformatter.h
        contactstreemodel.h
        emailaddressselectionmodel.h
        grantlee/grantleecontactgroupformatter.h
        grantlee/grantleeprint.h
        grantlee/contactgrantleewrapper.h
        grantlee/grantleecontactformatter.h
        emailaddressselection.h
        emailaddressselection_p.h
        collectionfiltermodel_p.h
        abstractcontactformatter.h
        contactsfilterproxymodel.h
        standardcontactgroupformatter.h
        standardcontactformatter.h
        contactcompletionmodel_p.h
        leafextensionproxymodel_p.h
        contactparts.h
        attributes/contactmetadataattribute_p.h
        akonadi_contact_core_private_export.h
)

ecm_qt_declare_logging_category(KPim6AkonadiContactCore HEADER akonadi_contact_debug.h IDENTIFIER AKONADICONTACT_LOG CATEGORY_NAME org.kde.pim.akonadicontact
        DESCRIPTION "akonadicontact (pim lib)"
        OLD_CATEGORY_NAMES log_akonadi_contact
        EXPORT AKONADICONTACTS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_source_files_properties(
        grantlee/contactgrantleewrapper.cpp
        grantlee/grantleecontactformatter.cpp
        grantlee/grantleecontactgroupformatter.cpp
        grantlee/grantleeprint.cpp
        PROPERTIES
            SKIP_UNITY_BUILD_INCLUSION
                ON
    )
    set_target_properties(
        KPim6AkonadiContactCore
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(KPim6AkonadiContactCore BASE_NAME akonadi-contact-core)

target_include_directories(
    KPim6AkonadiContactCore
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContactCore>"
)
target_include_directories(
    KPim6AkonadiContactCore
    PUBLIC
        "$<BUILD_INTERFACE:${Akonadi-Contact_SOURCE_DIR}/src;${Akonadi-Contact_BINARY_DIR}/src>"
)

target_link_libraries(
    KPim6AkonadiContactCore
    PUBLIC
        KPim6::AkonadiCore
        KF6::Contacts
        KPim6::GrantleeTheme
    PRIVATE
        KF6::ConfigCore
        KF6::IconThemes
        KF6::GuiAddons
        KF6::I18n
        KPim6::Mime
        KF6::TextUtils
)
set_target_properties(
    KPim6AkonadiContactCore
    PROPERTIES
        VERSION
            ${AKONADICONTACTCORE_VERSION}
        SOVERSION
            ${AKONADICONTACTCORE_SOVERSION}
        EXPORT_NAME
            AkonadiContactCore
)

install(TARGETS KPim6AkonadiContactCore EXPORT KPim6AkonadiContactCoreTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(AkonadiContactCoreJob_CamelCase_HEADERS
    HEADER_NAMES
    ContactGroupExpandJob
    ContactGroupSearchJob
    ContactSearchJob
    REQUIRED_HEADERS AkonadiContactCoreJob_HEADERS
    PREFIX Akonadi
    RELATIVE job
)

ecm_generate_headers(AkonadiContactCore_CamelCase_HEADERS
    HEADER_NAMES
    AbstractContactFormatter
    AbstractContactGroupFormatter
    ContactsFilterProxyModel
    ContactsTreeModel
    ContactParts

    EmailAddressSelection
    EmailAddressSelectionModel
    StandardContactFormatter
    StandardContactGroupFormatter

    REQUIRED_HEADERS AkonadiContactCore_HEADERS
    PREFIX Akonadi
)

ecm_generate_headers(AkonadiContactCoreGrantlee_CamelCase_HEADERS
    HEADER_NAMES
    ContactGrantleeWrapper
    GrantleeContactFormatter
    GrantleeContactGroupFormatter
    GrantleePrint

    REQUIRED_HEADERS AkonadiContactCoreGrantlee_HEADERS
    RELATIVE grantlee
    PREFIX Akonadi
)

install(
    FILES
        ${AkonadiContactCore_CamelCase_HEADERS}
        ${AkonadiContactCoreJob_CamelCase_HEADERS}
        ${AkonadiContactCoreGrantlee_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContactCore/Akonadi
    COMPONENT Devel
)

install(
    FILES
        ${AkonadiContactCore_HEADERS}
        ${AkonadiContactCoreJob_HEADERS}
        ${AkonadiContactCoreGrantlee_HEADERS}
        ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact-core_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContactCore/akonadi
    COMPONENT Devel
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6AkonadiContactCore")
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimAkonadiContactCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactCoreConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactCoreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactCoreConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KPim6AkonadiContactCoreTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPim6AkonadiContactCoreTargets.cmake
    NAMESPACE KPim6::
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_core_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContactCore
    COMPONENT Devel
)
