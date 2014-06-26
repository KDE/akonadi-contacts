remove_definitions(-DQT_NO_CAST_FROM_BYTEARRAY)

set(Prison_MIN_VERSION "1.2.0")
find_package(Prison ${Prison_MIN_VERSION})
set_package_properties(Prison PROPERTIES DESCRIPTION "Prison" URL "http://projects.kde.org/prison" TYPE OPTIONAL PURPOSE "Needed to show mobile barcodes of your contacts")
if (PRISON_FOUND)
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

configure_file( actions/contactactionssettings.kcfg.cmake ${CMAKE_CURRENT_BINARY_DIR}/contactactionssettings.kcfg @ONLY)
kconfig_add_kcfg_files(akonadicontact_actions_SRCS actions/contactactionssettings.kcfgc)

set(akonadicontact_editor_SRCS
  editor/addresseditwidget.cpp
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
  editor/geoeditwidget.cpp
  editor/im/imdelegate.cpp
  editor/im/imeditordialog.cpp
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
  editor/soundeditwidget.cpp
)

set(akonadicontact_LIB_SRC
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
  textbrowser.cpp
  leafextensionproxymodel.cpp
  recentcontactscollections.cpp
  recentcontactscollectionrequestjob.cpp
  standardcontactactionmanager.cpp
  standardcontactformatter.cpp
  standardcontactgroupformatter.cpp
  waitingoverlay.cpp
  ${akonadicontact_actions_SRCS}
)

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

target_include_directories(KF5AkonadiContact INTERFACE "$<INSTALL_INTERFACE:${KF5_INCLUDE_INSTALL_DIR}/Akonadi/Contact;${Boost_INCLUDE_DIR};${PHONON_INCLUDES}>")
target_include_directories(KF5AkonadiContact PUBLIC "$<BUILD_INTERFACE:${Akonadi-Contact_SOURCE_DIR}/src;${Akonadi-Contact_BINARY_DIR}/src;${Boost_INCLUDE_DIR};${PHONON_INCLUDES}>")
# TODO: Remove when kdepimlibs is split (and fix the broken includes in eg. akonadi-calendar)
target_include_directories(KF5AkonadiContact INTERFACE "$<INSTALL_INTERFACE:${KF5_INCLUDE_INSTALL_DIR}/akonadi/contact>")

target_link_libraries(KF5AkonadiContact
PUBLIC
    KF5::AkonadiCore
    KF5::Abc
PRIVATE
    KF5::AkonadiWidgets
    KF5::CalendarCore
    KF5::KIOCore
    KF5::Mime
    KF5::PimUtils
    KF5::KDELibs4Support
    Phonon::phonon4qt5
)

if(PRISON_FOUND)
   target_link_libraries(KF5AkonadiContact PRIVATE ${PRISON_LIBRARIES})
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

install(FILES editor/pics/world.jpg DESTINATION ${KF5_DATA_INSTALL_DIR}/akonadi/contact/pics)
install(FILES editor/data/zone.tab DESTINATION ${KF5_DATA_INSTALL_DIR}/akonadi/contact/data)
install(FILES recentcontactscollections.kcfg DESTINATION ${KCFG_INSTALL_DIR} )

ecm_generate_pri_file(BASE_NAME AkonadiContact
    LIB_NAME KF5AkonadiContact
    DEPS "AkonadiCore Abc" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KF5_INCLUDE_INSTALL_DIR}/Akonadi/Contact
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
  ContactViewer
  ContactViewerDialog
  EmailAddressSelection
  EmailAddressSelectionDialog
  EmailAddressSelectionWidget
  RecentContactsCollectionRequestJob
  StandardContactActionManager
  StandardContactFormatter
  StandardContactGroupFormatter

  REQUIRED_HEADERS AkonadiContact_HEADERS
  PREFIX Akonadi/Contact
)

install( FILES
  ${AkonadiContact_CamelCase_HEADERS}
  DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Akonadi/Contact COMPONENT Devel
)

install( FILES
  ${AkonadiContact_HEADERS}
  ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_export.h
  editor/im/improtocols.h
  DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/akonadi/contact COMPONENT Devel
)

