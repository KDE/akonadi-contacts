# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim${KF_MAJOR_VERSION}AkonadiContact")
set(AKONADICONTACT_KF5_COMPAT FALSE)
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim${KF_MAJOR_VERSION}AkonadiContact_QCH
        FILE KPim${KF_MAJOR_VERSION}AkonadiContactQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim${KF_MAJOR_VERSION}AkonadiContactQchTargets.cmake\")")
endif()

add_library(KPim${KF_MAJOR_VERSION}AkonadiContact)
add_library(KPim${KF_MAJOR_VERSION}::AkonadiContact ALIAS KPim${KF_MAJOR_VERSION}AkonadiContact)


ecm_setup_version(PROJECT VARIABLE_PREFIX AKONADICONTACT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}AkonadiContactConfigVersion.cmake"
    SOVERSION 5
    )
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimAkonadiContactConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}AkonadiContactConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}AkonadiContactConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}AkonadiContactConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KPim${KF_MAJOR_VERSION}AkonadiContactTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KPim${KF_MAJOR_VERSION}AkonadiContactTargets.cmake NAMESPACE KPim${KF_MAJOR_VERSION}::)

########### next target ###############

target_sources(KPim${KF_MAJOR_VERSION}AkonadiContact PRIVATE
    attributes/contactmetadataattribute.cpp
    attributes/attributeregistrar.cpp
)

target_sources(KPim${KF_MAJOR_VERSION}AkonadiContact PRIVATE
    job/contactgroupexpandjob.cpp
    job/contactgroupsearchjob.cpp
    job/contactsearchjob.cpp
    job/addcontactjob.cpp
    job/addemailaddressjob.cpp
    job/addemaildisplayjob.cpp
    job/openemailaddressjob.cpp
)

target_sources(KPim${KF_MAJOR_VERSION}AkonadiContact PRIVATE
    recipientspicker/recipientseditormanager.cpp
    recipientspicker/recipientspickerwidget.cpp
    )

target_sources(KPim${KF_MAJOR_VERSION}AkonadiContact PRIVATE
    grantlee/contactgrantleewrapper.cpp
    grantlee/grantleecontactformatter.cpp
    grantlee/grantleecontactgroupformatter.cpp
    grantlee/grantleeprint.cpp
    grantlee/grantleecontactviewer.cpp
    )


target_sources(KPim${KF_MAJOR_VERSION}AkonadiContact PRIVATE
    abstractcontactformatter.cpp
    abstractcontactgroupformatter.cpp
    collectionfiltermodel.cpp
    contactcompletionmodel.cpp
    contactdefaultactions.cpp
    contacteditor.cpp
    contacteditordialog.cpp
    contactgroupeditor.cpp
    contactgroupeditordelegate.cpp
    contactgroupeditordialog.cpp
    contactgroupmodel.cpp
    contactgroupviewer.cpp
    contactmetadataakonadi.cpp
    contactparts.cpp
    contactsfilterproxymodel.cpp
    contactstreemodel.cpp
    contactviewer.cpp
    contactviewerdialog.cpp
    emailaddressselection.cpp
    emailaddressselectiondialog.cpp
    abstractemailaddressselectiondialog.cpp
    emailaddressselectionproxymodel.cpp
    emailaddressselectionwidget.cpp
    emailaddressrequester.cpp
    emailaddressselectionmodel.cpp
    textbrowser.cpp
    leafextensionproxymodel.cpp
    standardcontactactionmanager.cpp
    standardcontactformatter.cpp
    standardcontactgroupformatter.cpp
    waitingoverlay.cpp
    selectaddressbookdialog.cpp
    emailaddressselectionproxymodel_p.h
    job/contactgroupsearchjob.h
    job/openemailaddressjob.h
    job/contactsearchjob.h
    job/addemailaddressjob.h
    job/addemaildisplayjob.h
    job/addcontactjob.h
    job/contactgroupexpandjob.h
    contactdefaultactions.h
    contactviewer.h
    contacteditor.h
    contactgroupmodel_p.h
    abstractemailaddressselectiondialog.h
    emailaddressselectiondialog.h
    abstractcontactgroupformatter.h
    contactstreemodel.h
    emailaddressselectionmodel.h
    grantlee/grantleecontactgroupformatter.h
    grantlee/grantleeprint.h
    grantlee/grantleecontactviewer.h
    grantlee/contactgrantleewrapper.h
    grantlee/grantleecontactformatter.h
    standardcontactactionmanager.h
    emailaddressselection.h
    contactgroupeditordelegate_p.h
    textbrowser_p.h
    recipientspicker/recipientseditormanager.h
    recipientspicker/recipientspickerwidget.h
    akonadicontact_private_export.h
    contacteditordialog.h
    emailaddressselection_p.h
    contactgroupviewer.h
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
    selectaddressbookdialog.h
    contactparts.h
    contactmetadataakonadi_p.h
    emailaddressrequester.h
    contactgroupeditor.h
    attributes/contactmetadataattribute_p.h
    contactviewerdialog.h
    )


ecm_qt_declare_logging_category(KPim${KF_MAJOR_VERSION}AkonadiContact HEADER akonadi_contact_debug.h IDENTIFIER AKONADICONTACT_LOG CATEGORY_NAME org.kde.pim.akonadicontact
        DESCRIPTION "akonadicontact (pim lib)"
        OLD_CATEGORY_NAMES log_akonadi_contact
        EXPORT AKONADICONTACTS
    )

ki18n_wrap_ui(KPim${KF_MAJOR_VERSION}AkonadiContact contactgroupeditor.ui)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_source_files_properties(
        grantlee/contactgrantleewrapper.cpp
        grantlee/grantleecontactformatter.cpp
        grantlee/grantleecontactgroupformatter.cpp
        grantlee/grantleeprint.cpp
        grantlee/grantleecontactviewer.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON)
    set_target_properties(KPim${KF_MAJOR_VERSION}AkonadiContact PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KPim${KF_MAJOR_VERSION}AkonadiContact BASE_NAME akonadi-contact)


target_include_directories(KPim${KF_MAJOR_VERSION}AkonadiContact INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/AkonadiContact>")
target_include_directories(KPim${KF_MAJOR_VERSION}AkonadiContact PUBLIC "$<BUILD_INTERFACE:${Akonadi-Contact_SOURCE_DIR}/src;${Akonadi-Contact_BINARY_DIR}/src>")

target_link_libraries(KPim${KF_MAJOR_VERSION}AkonadiContact
    PUBLIC
    KPim${KF_MAJOR_VERSION}::AkonadiCore
    KF${KF_MAJOR_VERSION}::Contacts
    KPim${KF_MAJOR_VERSION}::AkonadiWidgets
    Qt::Widgets
    KPim${KF_MAJOR_VERSION}::GrantleeTheme
    PRIVATE
    KF${KF_MAJOR_VERSION}::ConfigCore
    KF${KF_MAJOR_VERSION}::IconThemes
    KF${KF_MAJOR_VERSION}::Completion
    KF${KF_MAJOR_VERSION}::KIOCore
    KF${KF_MAJOR_VERSION}::JobWidgets
    KF${KF_MAJOR_VERSION}::KIOGui
    KPim${KF_MAJOR_VERSION}::Mime
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::TextWidgets
    KF${KF_MAJOR_VERSION}::XmlGui
    KPim${KF_MAJOR_VERSION}::ContactEditor
    KF${KF_MAJOR_VERSION}::Prison
    KF${KF_MAJOR_VERSION}::Codecs
    ${MAIN_LIB}
    )
if(TARGET KF${KF_MAJOR_VERSION}::I18nLocaleData)
    target_link_libraries(KPim${KF_MAJOR_VERSION}AkonadiContact PRIVATE KF${KF_MAJOR_VERSION}::I18nLocaleData)
endif()

set_target_properties(KPim${KF_MAJOR_VERSION}AkonadiContact PROPERTIES
    VERSION ${AKONADICONTACT_VERSION}
    SOVERSION ${AKONADICONTACT_SOVERSION}
    EXPORT_NAME AkonadiContact
    )

install(TARGETS
    KPim${KF_MAJOR_VERSION}AkonadiContact
    EXPORT KPim${KF_MAJOR_VERSION}AkonadiContactTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    )

ecm_generate_pri_file(BASE_NAME AkonadiContact
    LIB_NAME KPim${KF_MAJOR_VERSION}AkonadiContact
    DEPS "AkonadiCore KContacts" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/Akonadi/Contact
    )

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

ecm_generate_headers(AkonadiContactJob_CamelCase_HEADERS
    HEADER_NAMES
    ContactGroupExpandJob
    ContactGroupSearchJob
    ContactSearchJob
    AddEmailAddressJob
    AddEmailDisplayJob
    OpenEmailAddressJob
    AddContactJob
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
    ContactEditor
    ContactEditorDialog
    ContactGroupEditor
    ContactGroupEditorDialog
    ContactGroupViewer
    ContactsFilterProxyModel
    ContactsTreeModel
    ContactParts
    ContactViewer
    ContactViewerDialog
    EmailAddressSelection
    EmailAddressSelectionDialog
    EmailAddressSelectionWidget
    EmailAddressSelectionModel
    EmailAddressRequester
    AbstractEmailAddressSelectionDialog
    StandardContactActionManager
    StandardContactFormatter
    StandardContactGroupFormatter
    SelectAddressBookDialog

    REQUIRED_HEADERS AkonadiContact_HEADERS
    PREFIX Akonadi
    )

ecm_generate_headers(AkonadiContactGrantlee_CamelCase_HEADERS
    HEADER_NAMES
    ContactGrantleeWrapper
    GrantleeContactFormatter
    GrantleeContactGroupFormatter
    GrantleePrint
    GrantleeContactViewer

    REQUIRED_HEADERS AkonadiContactGrantlee_HEADERS
    RELATIVE grantlee
    PREFIX Akonadi
)

install( FILES
    ${AkonadiContact_CamelCase_HEADERS}
    ${AkonadiContactJob_CamelCase_HEADERS}
    ${AkonadiContactRecipients_CamelCase_HEADERS}
    ${AkonadiContactGrantlee_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/AkonadiContact/Akonadi COMPONENT Devel
    )

install( FILES
    ${AkonadiContact_HEADERS}
    ${AkonadiContactJob_HEADERS}
    ${AkonadiContactRecipients_HEADERS}
    ${AkonadiContactGrantlee_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/AkonadiContact/akonadi COMPONENT Devel
    )


if (BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

if (BUILD_QCH)
    ecm_add_qch(
        KPim${KF_MAJOR_VERSION}AkonadiContact_QCH
        NAME KPim${KF_MAJOR_VERSION}AkonadiContact
        BASE_NAME KPim${KF_MAJOR_VERSION}AkonadiContact
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
            Qt${QT_MAJOR_VERSION}Core_QCH
            Qt${QT_MAJOR_VERSION}Gui_QCH
            Qt${QT_MAJOR_VERSION}Widgets_QCH
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
  DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/AkonadiContact COMPONENT Devel
)

##
# TODO: Backwards compatiblity. Remove in next major version
##
set(CMAKECONFIG_INSTALL_DIR_KF5 "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5AkonadiContact")
set(AKONADICONTACT_KF5_COMPAT TRUE)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimAkonadiContactConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR_KF5}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfig.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
    COMPONENT Devel
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}AkonadiContactConfigVersion.cmake"
    RENAME "KF5AkonadiContactConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
    COMPONENT Devel
)
install(EXPORT KPim${KF_MAJOR_VERSION}AkonadiContactTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
    FILE KPim${KF_MAJOR_VERSION}AkonadiContactTargets.cmake
    NAMESPACE KF5::
)

if (BUILD_QCH)
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}AkonadiContactQchTargets.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
        COMPONENT Devel
    )
endif()

