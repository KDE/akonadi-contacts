# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6AkonadiContact")
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim6AkonadiContact_QCH
        FILE KPim6AkonadiContactQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim6AkonadiContactQchTargets.cmake\")")
endif()

add_library(KPim6AkonadiContact)
add_library(KPim6::AkonadiContact ALIAS KPim6AkonadiContact)


ecm_setup_version(PROJECT VARIABLE_PREFIX AKONADICONTACT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactConfigVersion.cmake"
    SOVERSION 6
    )
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimAkonadiContactConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KPim6AkonadiContactTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KPim6AkonadiContactTargets.cmake NAMESPACE KPim6::)

########### next target ###############

target_sources(KPim6AkonadiContact PRIVATE
    attributes/contactmetadataattribute.cpp
    attributes/attributeregistrar.cpp
)

target_sources(KPim6AkonadiContact PRIVATE
    job/contactgroupexpandjob.cpp
    job/contactgroupsearchjob.cpp
    job/contactsearchjob.cpp
)

target_sources(KPim6AkonadiContact PRIVATE
    recipientspicker/recipientseditormanager.cpp
    recipientspicker/recipientspickerwidget.cpp
    )

target_sources(KPim6AkonadiContact PRIVATE
    grantlee/contactgrantleewrapper.cpp
    grantlee/grantleecontactformatter.cpp
    grantlee/grantleecontactgroupformatter.cpp
    grantlee/grantleeprint.cpp
    )


target_sources(KPim6AkonadiContact PRIVATE
    abstractcontactformatter.cpp
    abstractcontactgroupformatter.cpp
    collectionfiltermodel.cpp
    contactcompletionmodel.cpp
    contactdefaultactions.cpp
    contactgroupeditor.cpp
    contactgroupeditordelegate.cpp
    contactgroupeditordialog.cpp
    contactgroupmodel.cpp
    contactparts.cpp
    contactsfilterproxymodel.cpp
    contactstreemodel.cpp

    emailaddressselection.cpp
    emailaddressselectiondialog.cpp
    abstractemailaddressselectiondialog.cpp
    emailaddressselectionproxymodel.cpp
    emailaddressselectionwidget.cpp
    emailaddressrequester.cpp
    emailaddressselectionmodel.cpp
    leafextensionproxymodel.cpp
    standardcontactformatter.cpp
    standardcontactgroupformatter.cpp
    waitingoverlay.cpp
    emailaddressselectionproxymodel_p.h
    job/contactgroupsearchjob.h
    job/contactsearchjob.h
    job/contactgroupexpandjob.h
    contactdefaultactions.h
    contactgroupmodel_p.h
    abstractemailaddressselectiondialog.h
    emailaddressselectiondialog.h
    abstractcontactgroupformatter.h
    contactstreemodel.h
    emailaddressselectionmodel.h
    grantlee/grantleecontactgroupformatter.h
    grantlee/grantleeprint.h
    grantlee/contactgrantleewrapper.h
    grantlee/grantleecontactformatter.h
    emailaddressselection.h
    contactgroupeditordelegate_p.h
    recipientspicker/recipientseditormanager.h
    recipientspicker/recipientspickerwidget.h
    akonadicontact_private_export.h
    emailaddressselection_p.h
    collectionfiltermodel_p.h
    abstractcontactformatter.h
    contactsfilterproxymodel.h
    standardcontactgroupformatter.h
    standardcontactformatter.h
    contactgroupeditordialog.h
    contactgroupeditor_p.h
    contactcompletionmodel_p.h
    waitingoverlay_p.h
    leafextensionproxymodel_p.h
    emailaddressselectionwidget.h
    contactparts.h
    emailaddressrequester.h
    contactgroupeditor.h
    attributes/contactmetadataattribute_p.h
    )


ecm_qt_declare_logging_category(KPim6AkonadiContact HEADER akonadi_contact_debug.h IDENTIFIER AKONADICONTACT_LOG CATEGORY_NAME org.kde.pim.akonadicontact
        DESCRIPTION "akonadicontact (pim lib)"
        OLD_CATEGORY_NAMES log_akonadi_contact
        EXPORT AKONADICONTACTS
    )

ki18n_wrap_ui(KPim6AkonadiContact contactgroupeditor.ui)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_source_files_properties(
        grantlee/contactgrantleewrapper.cpp
        grantlee/grantleecontactformatter.cpp
        grantlee/grantleecontactgroupformatter.cpp
        grantlee/grantleeprint.cpp
        PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON)
    set_target_properties(KPim6AkonadiContact PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KPim6AkonadiContact BASE_NAME akonadi-contact)


target_include_directories(KPim6AkonadiContact INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContact>")
target_include_directories(KPim6AkonadiContact PUBLIC "$<BUILD_INTERFACE:${Akonadi-Contact_SOURCE_DIR}/src;${Akonadi-Contact_BINARY_DIR}/src>")

target_link_libraries(KPim6AkonadiContact
    PUBLIC
    KPim6::AkonadiCore
    KF6::Contacts
    KPim6::AkonadiWidgets
    Qt::Widgets
    KPim6::GrantleeTheme
    PRIVATE
    KF6::ConfigCore
    KF6::IconThemes
    KF6::Completion
    KF6::KIOCore
    KF6::JobWidgets
    KF6::KIOGui
    KPim6::Mime
    KF6::I18n
    KF6::TextWidgets
    KF6::XmlGui
    KF6::Prison
    KF6::Codecs
    ${MAIN_LIB}
    )
if(TARGET KF6::I18nLocaleData)
    target_link_libraries(KPim6AkonadiContact PRIVATE KF6::I18nLocaleData)
endif()

set_target_properties(KPim6AkonadiContact PROPERTIES
    VERSION ${AKONADICONTACT_VERSION}
    SOVERSION ${AKONADICONTACT_SOVERSION}
    EXPORT_NAME AkonadiContact
    )

install(TARGETS
    KPim6AkonadiContact
    EXPORT KPim6AkonadiContactTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    )

ecm_generate_pri_file(BASE_NAME AkonadiContact
    LIB_NAME KPim6AkonadiContact
    DEPS "AkonadiCore KContacts" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR}/KPim6/Akonadi/Contact
    )

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

ecm_generate_headers(AkonadiContactJob_CamelCase_HEADERS
    HEADER_NAMES
    ContactGroupExpandJob
    ContactGroupSearchJob
    ContactSearchJob
    REQUIRED_HEADERS AkonadiContactJob_HEADERS
    PREFIX Akonadi
    RELATIVE job
    )

ecm_generate_headers(AkonadiContactRecipients_CamelCase_HEADERS
    HEADER_NAMES
    RecipientsEditorManager
    RecipientsPickerWidget
    REQUIRED_HEADERS AkonadiContactRecipients_HEADERS
    PREFIX Akonadi
    RELATIVE recipientspicker
    )


ecm_generate_headers(AkonadiContact_CamelCase_HEADERS
    HEADER_NAMES
    AbstractContactFormatter
    AbstractContactGroupFormatter
    ContactDefaultActions
    ContactGroupEditor
    ContactGroupEditorDialog
    ContactsFilterProxyModel
    ContactsTreeModel
    ContactParts

    EmailAddressSelection
    EmailAddressSelectionDialog
    EmailAddressSelectionWidget
    EmailAddressSelectionModel
    EmailAddressRequester
    AbstractEmailAddressSelectionDialog
    StandardContactFormatter
    StandardContactGroupFormatter

    REQUIRED_HEADERS AkonadiContact_HEADERS
    PREFIX Akonadi
    )

ecm_generate_headers(AkonadiContactGrantlee_CamelCase_HEADERS
    HEADER_NAMES
    ContactGrantleeWrapper
    GrantleeContactFormatter
    GrantleeContactGroupFormatter
    GrantleePrint

    REQUIRED_HEADERS AkonadiContactGrantlee_HEADERS
    RELATIVE grantlee
    PREFIX Akonadi
)

install( FILES
    ${AkonadiContact_CamelCase_HEADERS}
    ${AkonadiContactJob_CamelCase_HEADERS}
    ${AkonadiContactRecipients_CamelCase_HEADERS}
    ${AkonadiContactGrantlee_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContact/Akonadi COMPONENT Devel
    )

install( FILES
    ${AkonadiContact_HEADERS}
    ${AkonadiContactJob_HEADERS}
    ${AkonadiContactRecipients_HEADERS}
    ${AkonadiContactGrantlee_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContact/akonadi COMPONENT Devel
    )


if (BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

if (BUILD_QCH)
    ecm_add_qch(
        KPim6AkonadiContact_QCH
        NAME KPim6AkonadiContact
        BASE_NAME KPim6AkonadiContact
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${AkonadiContact_HEADERS}
        ${AkonadiContactJob_HEADERS}
        ${AkonadiContactRecipients_HEADERS}
        ${AkonadiContactGrantlee_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            KSIEVEUI_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContact COMPONENT Devel
)
