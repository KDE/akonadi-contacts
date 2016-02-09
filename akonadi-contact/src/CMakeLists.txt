remove_definitions(-DQT_NO_CAST_FROM_BYTEARRAY)


set(Prison_MIN_VERSION "1.2.1")
find_package(KF5Prison ${Prison_MIN_VERSION})
set_package_properties(Prison PROPERTIES DESCRIPTION "Prison" URL "http://projects.kde.org/prison" TYPE OPTIONAL PURPOSE "Needed to show mobile barcodes of your contacts")
if (KF5Prison_FOUND)
    add_definitions(-DHAVE_PRISON)
endif()

set( AKONADI_PHONE_DIAL_DEFAULT "UseSkype" )
set( AKONADI_SEND_SMS_DEFAULT  "UseSkypeSms" )

add_subdirectory(kcm)
add_subdirectory(editor/im)
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

set(akonadicontact_customfieldseditor_SRCS
   editor/customfieldeditor/customfieldswidget.cpp
   editor/customfieldeditor/customfieldeditorwidget.cpp
   )


set(akonadicontact_editor_widgets_SRCS
    editor/widgets/kwidgetlister.cpp
    )

set(akonadicontact_editor_generalinfo_phone_SRCS
    editor/generalinfoeditor/phone/phonewidgetlister.cpp
    editor/generalinfoeditor/phone/phonewidget.cpp
    editor/generalinfoeditor/phone/phonelistwidget.cpp
    editor/generalinfoeditor/phone/phonecomboboxtype.cpp
    )

set(akonadicontact_editor_generalinfo_web_SRCS
    editor/generalinfoeditor/web/webwidgetlister.cpp
    editor/generalinfoeditor/web/weblistwidget.cpp
    editor/generalinfoeditor/web/webwidget.cpp
    )
set(akonadicontact_editor_generalinfo_mail_SRCS
    editor/generalinfoeditor/mail/maillistwidget.cpp
    editor/generalinfoeditor/mail/mailwidget.cpp
    editor/generalinfoeditor/mail/mailwidgetlister.cpp
    )

set(akonadicontact_editor_generalinfo_messaging_SRCS
    editor/generalinfoeditor/messaging/messaginglistwidget.cpp
    editor/generalinfoeditor/messaging/messagingwidget.cpp
    editor/generalinfoeditor/messaging/messagingwidgetlister.cpp
    )


set(akonadicontact_editor_generalinfo_SRCS
    editor/generalinfoeditor/generalinfowidget.cpp
    editor/generalinfoeditor/namewidget.cpp
    editor/generalinfoeditor/nicknamewidget.cpp
    ${akonadicontact_editor_generalinfo_messaging_SRCS}
    ${akonadicontact_editor_generalinfo_phone_SRCS}
    ${akonadicontact_editor_generalinfo_web_SRCS}
    ${akonadicontact_editor_generalinfo_mail_SRCS}
    )

set(akonadicontact_addresslocation_editor_SRCS
    editor/addresseditor/addresslocationwidget.cpp
    editor/addresseditor/addresseslocationviewer.cpp
    editor/addresseditor/addresseslocationgrantleeformater.cpp
    editor/addresseditor/addressgrantleeobject.cpp
    editor/addresseditor/iconnamecache.cpp
    editor/addresseditor/addresseslocationwidget.cpp
    editor/addresseditor/selectaddresstypecombobox.cpp
    editor/addresseditor/addresstypedialog.cpp
    )

set(akonadicontact_editor_SRCS
    editor/categorieseditwidget.cpp
    editor/contacteditorwidget.cpp
    editor/customfieldeditordialog.cpp
    editor/customfieldsdelegate.cpp
    editor/customfieldseditwidget.cpp
    editor/customfieldsmodel.cpp
    editor/dateeditwidget.cpp
    editor/displaynameeditwidget.cpp
    editor/emaileditwidget.cpp
    editor/freebusyeditwidget.cpp
    editor/im/imdelegate.cpp
    editor/im/imeditordialog.cpp
    editor/im/imaddress.cpp
    editor/im/immodel.cpp
    editor/im/improtocols.cpp
    editor/im/imitemdialog.cpp
    editor/imagewidget.cpp
    editor/imeditwidget.cpp
    editor/kdatepickerpopup.cpp
    editor/nameeditdialog.cpp
    editor/nameeditwidget.cpp
    editor/phoneeditwidget.cpp
    editor/secrecyeditwidget.cpp
    )

set(akonadicontact_LIB_SRC
    ${akonadicontact_addresslocation_editor_SRCS}
    ${akonadicontact_editor_widgets_SRCS}
    ${akonadicontact_editor_generalinfo_SRCS}
    ${akonadicontact_customfieldseditor_SRCS}
    abstractcontactformatter.cpp
    abstractcontactgroupformatter.cpp
    attributeregistrar.cpp
    collectionfiltermodel.cpp
    contactcompletionmodel.cpp
    contactdefaultactions.cpp
    contacteditor.cpp
    contacteditordialog.cpp
    contactgroupeditor.cpp
    contactgroupeditordelegate.cpp
    contactgroupeditordialog.cpp
    contactgrouplineedit.cpp
    contactgroupexpandjob.cpp
    contactgroupmodel.cpp
    contactgroupsearchjob.cpp
    contactgroupviewer.cpp
    contactgroupviewerdialog.cpp
    contactmetadata.cpp
    contactmetadataattribute.cpp
    contactparts.cpp
    contactsearchjob.cpp
    contactsfilterproxymodel.cpp
    contactstreemodel.cpp
    contactviewer.cpp
    contactviewerdialog.cpp
    customfields.cpp
    customfieldmanager.cpp
    emailaddressselection.cpp
    emailaddressselectiondialog.cpp
    emailaddressselectionproxymodel.cpp
    emailaddressselectionwidget.cpp
    emailaddressrequester.cpp
    textbrowser.cpp
    leafextensionproxymodel.cpp
    recentcontactscollections.cpp
    recentcontactscollectionrequestjob.cpp
    standardcontactactionmanager.cpp
    standardcontactformatter.cpp
    standardcontactgroupformatter.cpp
    waitingoverlay.cpp
    selectaddressbookdialog.cpp
    ${akonadicontact_actions_SRCS}
    )

ecm_qt_declare_logging_category(akonadicontact_LIB_SRC HEADER akonadi_contact_debug.h IDENTIFIER AKONADICONTACT_LOG CATEGORY_NAME log_akonadi_contact)

if(NOT KDE_PLATFORM_PROFILE STREQUAL "Mobile")
    set(akonadicontact_LIB_SRC
        ${akonadicontact_LIB_SRC}
        ${akonadicontact_editor_SRCS}
        )
else()
    add_definitions(-DDISABLE_EDITOR_WIDGETS)
endif()

ki18n_wrap_ui(akonadicontact_LIB_SRC contactgroupeditor.ui)
kconfig_add_kcfg_files(akonadicontact_LIB_SRC recentcontactscollectionssettings.kcfgc )


add_library(KF5AkonadiContact ${akonadicontact_LIB_SRC})

generate_export_header(KF5AkonadiContact BASE_NAME akonadi-contact)

add_library(KF5::AkonadiContact ALIAS KF5AkonadiContact)


target_include_directories(KF5AkonadiContact INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/Akonadi/Contact>")
target_include_directories(KF5AkonadiContact PUBLIC "$<BUILD_INTERFACE:${Akonadi-Contact_SOURCE_DIR}/src;${Akonadi-Contact_BINARY_DIR}/src>")

# TODO: Remove when kdepimlibs is split (and fix the broken includes in eg. akonadi-calendar)
target_include_directories(KF5AkonadiContact INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/akonadi/contact>")

target_link_libraries(KF5AkonadiContact
    PUBLIC
    KF5::AkonadiCore
    KF5::Contacts
    Qt5::Widgets
    PRIVATE
    KF5::AkonadiWidgets
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
    Qt5::WebKitWidgets
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
install(FILES recentcontactscollections.kcfg DESTINATION ${KDE_INSTALL_KCFGDIR} )

ecm_generate_pri_file(BASE_NAME AkonadiContact
    LIB_NAME KF5AkonadiContact
    DEPS "AkonadiCore Abc" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/Akonadi/Contact
    )

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

ecm_generate_headers(AkonadiContact_CamelCase_HEADERS
    HEADER_NAMES
    AbstractContactFormatter
    AbstractContactGroupFormatter
    ContactDefaultActions
    ContactEditor
    ContactEditorDialog
    ContactGroupEditor
    ContactGroupEditorDialog
    ContactGroupExpandJob
    ContactGroupSearchJob
    ContactGroupViewer
    ContactGroupViewerDialog
    ContactSearchJob
    ContactsFilterProxyModel
    ContactsTreeModel
    ContactEditorPagePlugin
    ContactParts
    ContactViewer
    ContactViewerDialog
    EmailAddressSelection
    EmailAddressSelectionDialog
    EmailAddressSelectionWidget
    EmailAddressRequester
    RecentContactsCollectionRequestJob
    StandardContactActionManager
    StandardContactFormatter
    StandardContactGroupFormatter
    SelectAddressBookDialog

    REQUIRED_HEADERS AkonadiContact_HEADERS
    PREFIX Akonadi/Contact
    )

install( FILES
    ${AkonadiContact_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/Akonadi/Contact COMPONENT Devel
    )

install( FILES
    ${AkonadiContact_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_export.h
    editor/im/improtocols.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/akonadi/contact COMPONENT Devel
    )

if (BUILD_TESTING)
    add_subdirectory(editor/autotests)
    add_subdirectory(editor/addresseditor/autotests/)
    add_subdirectory(editor/addresseditor/tests)
    add_subdirectory(editor/generalinfoeditor/autotests/)
    add_subdirectory(editor/generalinfoeditor/tests)
endif()


add_subdirectory(editor/addresseditor/html)

