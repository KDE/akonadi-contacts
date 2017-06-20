add_definitions(-DTRANSLATION_DOMAIN=\"akonadicontact5\")
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5AkonadiContact")

ecm_setup_version(PROJECT VARIABLE_PREFIX AKONADICONTACT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfigVersion.cmake"
    SOVERSION 5
    )
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5AkonadiContactConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5AkonadiContactTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5AkonadiContactTargets.cmake NAMESPACE KF5::)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )


set( AKONADI_PHONE_DIAL_DEFAULT "UseSkype" )
set( AKONADI_SEND_SMS_DEFAULT  "UseSkypeSms" )

########### next target ###############

set(akonadicontact_actions_SRCS
    actions/dialphonenumberaction.cpp
    actions/showaddressaction.cpp
    actions/qdialer.cpp
    actions/qskypedialer.cpp
    actions/sendsmsaction.cpp
    actions/smsdialog.cpp
    actions/qsflphonedialer.cpp
    actions/qekigadialer.cpp
    )

configure_file(config-akonadi-contact.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-akonadi-contact.h)

configure_file( actions/contactactionssettings.kcfg.cmake ${CMAKE_CURRENT_BINARY_DIR}/contactactionssettings.kcfg @ONLY)
kconfig_add_kcfg_files(akonadicontact_actions_SRCS actions/contactactionssettings.kcfgc)


set(akonadicontact_attributes_SRCS
    attributes/contactmetadataattribute.cpp
    attributes/attributeregistrar.cpp
)

set(akonadicontact_job_SRCS
    job/contactgroupexpandjob.cpp
    job/contactgroupsearchjob.cpp
    job/contactsearchjob.cpp
)

set(akonadicontact_LIB_SRC
    ${akonadicontact_customfieldseditor_SRCS}
    ${akonadicontact_attributes_SRCS}
    ${akonadicontact_job_SRCS}
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
    contactgroupviewerdialog.cpp
    contactmetadataakonadi.cpp
    contactparts.cpp
    contactsfilterproxymodel.cpp
    contactstreemodel.cpp
    contactviewer.cpp
    contactviewerdialog.cpp
    emailaddressselection.cpp
    emailaddressselectiondialog.cpp
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
    ${akonadicontact_actions_SRCS}
    )

ecm_qt_declare_logging_category(akonadicontact_LIB_SRC HEADER akonadi_contact_debug.h IDENTIFIER AKONADICONTACT_LOG CATEGORY_NAME org.kde.pim.akonadicontact)

set(akonadicontact_LIB_SRC
    ${akonadicontact_LIB_SRC}
    )

ki18n_wrap_ui(akonadicontact_LIB_SRC contactgroupeditor.ui)


add_library(KF5AkonadiContact ${akonadicontact_LIB_SRC})

generate_export_header(KF5AkonadiContact BASE_NAME akonadi-contact)

add_library(KF5::AkonadiContact ALIAS KF5AkonadiContact)

target_include_directories(KF5AkonadiContact INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/Akonadi/Contact;${KDE_INSTALL_INCLUDEDIR_KF5}>")
target_include_directories(KF5AkonadiContact INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/akonadi/contact>")
target_include_directories(KF5AkonadiContact PUBLIC "$<BUILD_INTERFACE:${Akonadi-Contact_SOURCE_DIR}/src;${Akonadi-Contact_BINARY_DIR}/src>")

target_link_libraries(KF5AkonadiContact
    PUBLIC
    KF5::AkonadiCore
    KF5::Contacts
    KF5::AkonadiWidgets
    Qt5::Widgets
    PRIVATE
    KF5::Completion
    KF5::ConfigCore
    KF5::ConfigWidgets
    KF5::IconThemes
    KF5::KIOWidgets
    KF5::Mime
    KF5::Codecs
    KF5::DBusAddons
    KF5::I18n
    KF5::Service
    KF5::TextWidgets
    KF5::WidgetsAddons
    KF5::XmlGui
    Grantlee5::Templates
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    KF5::ContactEditor
    )

if(KF5Prison_FOUND)
    target_link_libraries(KF5AkonadiContact PRIVATE KF5::Prison)
endif()


set_target_properties(KF5AkonadiContact PROPERTIES
    VERSION ${AKONADICONTACT_VERSION_STRING}
    SOVERSION ${AKONADICONTACT_SOVERSION}
    EXPORT_NAME AkonadiContact
    )

install(TARGETS
    KF5AkonadiContact
    EXPORT KF5AkonadiContactTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS}
    )

install(FILES editor/pics/world.jpg DESTINATION ${KDE_INSTALL_DATADIR_KF5}/akonadi/contact/pics)
install(FILES editor/data/zone.tab DESTINATION ${KDE_INSTALL_DATADIR_KF5}/akonadi/contact/data)

ecm_generate_pri_file(BASE_NAME AkonadiContact
    LIB_NAME KF5AkonadiContact
    DEPS "AkonadiCore Contacts" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/Akonadi/Contact
    )

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

ecm_generate_headers(AkonadiContactJob_CamelCase_HEADERS
    HEADER_NAMES
    ContactGroupExpandJob
    ContactGroupSearchJob
    ContactSearchJob
    REQUIRED_HEADERS AkonadiContactJob_HEADERS
    PREFIX Akonadi/Contact
    RELATIVE job
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
    ContactGroupViewerDialog
    ContactsFilterProxyModel
    ContactsTreeModel
    ContactEditorPagePlugin
    ContactParts
    ContactViewer
    ContactViewerDialog
    EmailAddressSelection
    EmailAddressSelectionDialog
    EmailAddressSelectionWidget
    EmailAddressSelectionModel
    EmailAddressRequester
    StandardContactActionManager
    StandardContactFormatter
    StandardContactGroupFormatter
    SelectAddressBookDialog

    REQUIRED_HEADERS AkonadiContact_HEADERS
    PREFIX Akonadi/Contact
    )

install( FILES
    ${AkonadiContact_CamelCase_HEADERS}
    ${AkonadiContactJob_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/Akonadi/Contact COMPONENT Devel
    )

install( FILES
    ${AkonadiContact_HEADERS}
    ${AkonadiContactJob_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_export.h
    editor/im/improtocols.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/akonadi/contact COMPONENT Devel
    )


if (BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

