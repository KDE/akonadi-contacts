set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5ContactEditor")

ecm_setup_version(PROJECT VARIABLE_PREFIX AKONADICONTACT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/contact-editor_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5ContactEditorConfigVersion.cmake"
    SOVERSION 5
    )
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5ContactEditorConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5ContactEditorConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5ContactEditorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5ContactEditorConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5ContactEditorTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5ContactEditorTargets.cmake NAMESPACE KF5::)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5ContactEditorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5ContactEditorConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

configure_file(config-contact-editor.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-contact-editor.h)



set(contacteditor_abstractaddresslocation_SRCS
    editor/addresseditor/abstractaddresslocationwidget.cpp)

set(contacteditor_customfieldseditor_SRCS
    editor/customfieldeditor/customfieldswidget.cpp
    editor/customfieldeditor/customfieldeditorwidget.cpp
    editor/customfieldeditor/customfieldslistwidget.cpp
    editor/customfieldeditor/customfieldslistdelegate.cpp
    editor/customfieldeditor/customfieldsmodel.cpp
    )

set(contacteditor_editor_utils_SRCS
    editor/utils/utils.cpp
    )

set(contacteditor_editor_widgets_SRCS
    editor/widgets/kwidgetlister.cpp
    editor/widgets/contacteditorcombobox.cpp
    )

set(contacteditor_editor_generalinfo_phone_SRCS
    editor/generalinfoeditor/phone/phonewidgetlister.cpp
    editor/generalinfoeditor/phone/phonewidget.cpp
    editor/generalinfoeditor/phone/phonelistwidget.cpp
    editor/generalinfoeditor/phone/phonecomboboxtype.cpp
    editor/generalinfoeditor/phone/phonetypedialog.cpp
    )

set(contacteditor_editor_generalinfo_web_SRCS
    editor/generalinfoeditor/web/webwidgetlister.cpp
    editor/generalinfoeditor/web/weblistwidget.cpp
    editor/generalinfoeditor/web/webwidget.cpp
    editor/generalinfoeditor/web/webselecttypecombobox.cpp
    )
set(contacteditor_editor_generalinfo_mail_SRCS
    editor/generalinfoeditor/mail/maillistwidget.cpp
    editor/generalinfoeditor/mail/mailwidget.cpp
    editor/generalinfoeditor/mail/mailwidgetlister.cpp
    editor/generalinfoeditor/mail/mailtypecombobox.cpp
    )

set(contacteditor_editor_generalinfo_messaging_SRCS
    editor/generalinfoeditor/messaging/messaginglistwidget.cpp
    editor/generalinfoeditor/messaging/messagingwidget.cpp
    editor/generalinfoeditor/messaging/messagingwidgetlister.cpp
    )


set(contacteditor_editor_generalinfo_SRCS
    editor/generalinfoeditor/generalinfowidget.cpp
    editor/generalinfoeditor/namewidget.cpp
    editor/generalinfoeditor/nicknamewidget.cpp
    editor/generalinfoeditor/categorieseditwidget.cpp
    editor/generalinfoeditor/nameeditdialog.cpp
    editor/generalinfoeditor/displaynameeditwidget.cpp
    editor/generalinfoeditor/messageformattingwidget.cpp
    editor/generalinfoeditor/blogfeedwidget.cpp
    ${contacteditor_editor_generalinfo_messaging_SRCS}
    ${contacteditor_editor_generalinfo_phone_SRCS}
    ${contacteditor_editor_generalinfo_web_SRCS}
    ${contacteditor_editor_generalinfo_mail_SRCS}
    ${contacteditor_abstractaddresslocation_SRCS}
    )

set(contacteditor_addresslocation_editor_SRCS
    editor/addresseditor/addresseslocationwidget.cpp
    )

set(contacteditor_personal_editor_SRCS
    editor/personaleditor/personaleditorwidget.cpp
    editor/personaleditor/dateeditwidget.cpp
    editor/personaleditor/kdatepickerpopup.cpp
    )

set(contacteditor_business_editor_SRCS
    editor/businesseditor/businesseditorwidget.cpp
    editor/businesseditor/freebusyeditwidget.cpp
    )

set(contacteditor_editor_SRCS
    ${contacteditor_personal_editor_SRCS}
    ${contacteditor_editor_utils_SRCS}
    ${contacteditor_business_editor_SRCS}
    editor/contacteditorwidget.cpp
    editor/widgets/imagewidget.cpp
    editor/widgets/preferredlineeditwidget.cpp
    editor/widgets/categorieseditabstractwidget.cpp
    customfields.cpp
    customfieldmanager.cpp
    contactmetadatabase.cpp
)

set(contacteditor_LIB_SRC
    ${contacteditor_addresslocation_editor_SRCS}
    ${contacteditor_editor_widgets_SRCS}
    ${contacteditor_editor_generalinfo_SRCS}
    ${contacteditor_customfieldseditor_SRCS}
    ${contacteditor_attributes_SRCS}
    ${contacteditor_job_SRCS}
    )

ecm_qt_declare_logging_category(contacteditor_LIB_SRC HEADER contacteditor_debug.h IDENTIFIER CONTACTEDITOR_LOG CATEGORY_NAME org.kde.pim.contacteditor)

set(contacteditor_LIB_SRC
    ${contacteditor_LIB_SRC}
    ${contacteditor_editor_SRCS}
    )



add_library(KF5ContactEditor ${contacteditor_LIB_SRC})
if (BUILD_TESTING)
    target_compile_definitions(KF5ContactEditor PRIVATE BUILD_TESTING)
endif()
generate_export_header(KF5ContactEditor BASE_NAME contacteditor)

add_library(KF5::ContactEditor ALIAS KF5ContactEditor)

target_include_directories(KF5ContactEditor INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/ContactEditor;${KDE_INSTALL_INCLUDEDIR_KF5}>")
target_include_directories(KF5ContactEditor INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/contacteditor>")
target_include_directories(KF5ContactEditor PUBLIC "$<BUILD_INTERFACE:${Akonadi-Contact_SOURCE_DIR}/src/contact-editor;${Akonadi-Contact_BINARY_DIR}/src/contact-editor>")

target_link_libraries(KF5ContactEditor
    PUBLIC
    KF5::Contacts
    Qt5::Widgets
    PRIVATE
    KF5::Completion
    KF5::ConfigCore
    KF5::ConfigWidgets
    KF5::IconThemes
    KF5::KIOWidgets
    KF5::Mime
    KF5::Codecs
    KF5::I18n
    KF5::Service
    KF5::TextWidgets
    KF5::WidgetsAddons
    )

set_target_properties(KF5ContactEditor PROPERTIES
    VERSION ${AKONADICONTACT_VERSION_STRING}
    SOVERSION ${AKONADICONTACT_SOVERSION}
    EXPORT_NAME ContactEditor
    )

install(TARGETS
    KF5ContactEditor
    EXPORT KF5ContactEditorTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS}
    )

ecm_generate_pri_file(BASE_NAME ContactEditor
    LIB_NAME KF5ContactEditor
    DEPS "Contacts" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/ContactEditor
    )

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

ecm_generate_headers(ContactEditor_CamelCase_HEADERS
    HEADER_NAMES
    ContactEditorPagePlugin
    REQUIRED_HEADERS ContactEditor_HEADERS
    PREFIX ContactEditor
    )

ecm_generate_headers(ContactEditorWidget_CamelCase_HEADERS
    HEADER_NAMES
    CategoriesEditAbstractWidget
    REQUIRED_HEADERS ContactEditorWidget_HEADERS
    PREFIX ContactEditor
    RELATIVE editor/widgets/
    )

ecm_generate_headers(ContactEditorAddressLocationWidget_CamelCase_HEADERS
    HEADER_NAMES
    AbstractAddressLocationWidget
    REQUIRED_HEADERS ContactEditorAddressLocationWidget_HEADERS
    PREFIX ContactEditor
    RELATIVE editor/addresseditor/
    )

install( FILES
    ${ContactEditor_CamelCase_HEADERS}
    ${ContactEditorWidget_CamelCase_HEADERS}
    ${ContactEditorAddressLocationWidget_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/ContactEditor COMPONENT Devel
    )

install( FILES
    ${ContactEditor_HEADERS}
    ${ContactEditorWidget_HEADERS}
    ${ContactEditorAddressLocationWidget_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/contacteditor_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/contacteditor COMPONENT Devel
    )



if (BUILD_TESTING)
    add_subdirectory(editor/generalinfoeditor/autotests/)
    add_subdirectory(editor/generalinfoeditor/tests)
    add_subdirectory(editor/customfieldeditor/autotests/)
    add_subdirectory(editor/customfieldeditor/tests)
    add_subdirectory(editor/widgets/autotests/)
endif()

install(FILES editor/pics/world.jpg DESTINATION ${KDE_INSTALL_DATADIR_KF5}/akonadi/contact/pics)
install(FILES editor/data/zone.tab DESTINATION ${KDE_INSTALL_DATADIR_KF5}/akonadi/contact/data)

