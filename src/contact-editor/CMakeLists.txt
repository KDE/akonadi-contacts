# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5ContactEditor")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5ContactEditor_QCH
        FILE KF5ContactEditorQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5ContactEditorQchTargets.cmake\")")
endif()

add_library(KF5ContactEditor)
add_library(KF5::ContactEditor ALIAS KF5ContactEditor)

ecm_setup_version(PROJECT VARIABLE_PREFIX AKONADICONTACT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact-editor_version.h"
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

target_sources(KF5ContactEditor PRIVATE
    editor/customfieldeditor/customfieldswidget.cpp
    editor/customfieldeditor/customfieldeditorwidget.cpp
    editor/customfieldeditor/customfieldslistwidget.cpp
    editor/customfieldeditor/customfieldslistdelegate.cpp
    editor/customfieldeditor/customfieldsmodel.cpp
    editor/utils/utils.cpp
    editor/widgets/kwidgetlister.cpp
    editor/widgets/contacteditorcombobox.cpp
    editor/generalinfoeditor/phone/phonewidgetlister.cpp
    editor/generalinfoeditor/phone/phonewidget.cpp
    editor/generalinfoeditor/phone/phonelistwidget.cpp
    editor/generalinfoeditor/phone/phonecomboboxtype.cpp
    editor/generalinfoeditor/phone/phonetypedialog.cpp
    editor/generalinfoeditor/web/webwidgetlister.cpp
    editor/generalinfoeditor/web/weblistwidget.cpp
    editor/generalinfoeditor/web/webwidget.cpp
    editor/generalinfoeditor/web/webselecttypecombobox.cpp
    editor/generalinfoeditor/mail/maillistwidget.cpp
    editor/generalinfoeditor/mail/mailwidget.cpp
    editor/generalinfoeditor/mail/mailwidgetlister.cpp
    editor/generalinfoeditor/mail/mailtypecombobox.cpp
    editor/generalinfoeditor/messaging/messaginglistwidget.cpp
    editor/generalinfoeditor/messaging/messagingwidget.cpp
    editor/generalinfoeditor/messaging/messagingwidgetlister.cpp
    editor/generalinfoeditor/generalinfowidget.cpp
    editor/generalinfoeditor/namewidget.cpp
    editor/generalinfoeditor/nicknamewidget.cpp
    editor/generalinfoeditor/categorieseditwidget.cpp
    editor/generalinfoeditor/nameeditdialog.cpp
    editor/generalinfoeditor/displaynameeditwidget.cpp
    editor/generalinfoeditor/messageformattingwidget.cpp
    editor/generalinfoeditor/blogfeedwidget.cpp
    editor/addresseditor/addressdelegate.cpp
    editor/addresseditor/addressmodel.cpp
    editor/addresseditor/addresseslocationwidget.cpp
    editor/addresseditor/addresslocationwidget.cpp
    editor/addresseditor/addresstypedialog.cpp
    editor/addresseditor/selectaddresstypecombobox.cpp
    editor/personaleditor/personaleditorwidget.cpp
    editor/personaleditor/dateeditwidget.cpp
    editor/businesseditor/businesseditorwidget.cpp
    editor/businesseditor/freebusyeditwidget.cpp
    editor/contacteditorwidget.cpp
    editor/widgets/imagewidget.cpp
    editor/widgets/preferredlineeditwidget.cpp
    editor/widgets/categorieseditabstractwidget.cpp
    customfields.cpp
    customfieldmanager.cpp
    contactmetadatabase.cpp
    editor/addresseditor/addresslocationwidget.h
    editor/addresseditor/selectaddresstypecombobox.h
    editor/addresseditor/addresseslocationwidget.h
    editor/addresseditor/addressdelegate.h
    editor/addresseditor/addressmodel.h
    editor/addresseditor/addresstypedialog.h
    editor/utils/utils.h
    editor/generalinfoeditor/web/webwidgetlister.h
    editor/generalinfoeditor/web/weblistwidget.h
    editor/generalinfoeditor/web/webwidget.h
    editor/generalinfoeditor/web/webselecttypecombobox.h
    editor/generalinfoeditor/messageformattingwidget.h
    editor/generalinfoeditor/phone/phonelistwidget.h
    editor/generalinfoeditor/phone/phonetypedialog.h
    editor/generalinfoeditor/phone/phonewidget.h
    editor/generalinfoeditor/phone/phonewidgetlister.h
    editor/generalinfoeditor/phone/phonecomboboxtype.h
    editor/generalinfoeditor/messaging/messaginglistwidget.h
    editor/generalinfoeditor/messaging/messagingwidgetlister.h
    editor/generalinfoeditor/messaging/messagingwidget.h
    editor/generalinfoeditor/nicknamewidget.h
    editor/generalinfoeditor/mail/maillistwidget.h
    editor/generalinfoeditor/mail/mailwidget.h
    editor/generalinfoeditor/mail/mailtypecombobox.h
    editor/generalinfoeditor/mail/mailwidgetlister.h
    editor/generalinfoeditor/blogfeedwidget.h
    editor/generalinfoeditor/displaynameeditwidget.h
    editor/generalinfoeditor/namewidget.h
    editor/generalinfoeditor/categorieseditwidget.h
    editor/generalinfoeditor/nameeditdialog.h
    editor/generalinfoeditor/generalinfowidget.h
    editor/contacteditorwidget.h
    editor/customfieldeditor/customfieldsmodel.h
    editor/customfieldeditor/customfieldslistdelegate.h
    editor/customfieldeditor/customfieldswidget.h
    editor/customfieldeditor/customfieldslistwidget.h
    editor/customfieldeditor/customfieldeditorwidget.h
    editor/personaleditor/dateeditwidget.h
    editor/personaleditor/personaleditorwidget.h
    editor/widgets/categorieseditabstractwidget.h
    editor/widgets/imagewidget.h
    editor/widgets/kwidgetlister_p.h
    editor/widgets/preferredlineeditwidget.h
    editor/widgets/contacteditorcombobox.h
    editor/businesseditor/freebusyeditwidget.h
    editor/businesseditor/businesseditorwidget.h
    contacteditor_private_export.h
    contacteditorpageplugin.h
    abstractcontacteditorwidget_p.h
    customfieldmanager_p.h
    contactmetadatabase_p.h
    customfields_p.h

)

ecm_qt_declare_logging_category(KF5ContactEditor HEADER contacteditor_debug.h IDENTIFIER CONTACTEDITOR_LOG CATEGORY_NAME org.kde.pim.contacteditor
        DESCRIPTION "akonadicontact (contact editor)"
        EXPORT AKONADICONTACTS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5ContactEditor PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(KF5ContactEditor BASE_NAME contacteditor)


target_include_directories(KF5ContactEditor INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/AkonadiContactEditor>")
target_include_directories(KF5ContactEditor PUBLIC "$<BUILD_INTERFACE:${Akonadi-Contact_SOURCE_DIR}/src/contact-editor;${Akonadi-Contact_BINARY_DIR}/src/contact-editor>")

target_link_libraries(KF5ContactEditor
    PUBLIC
    KF5::Contacts
    Qt::Widgets
    PRIVATE
    KF5::Completion
    KF5::ConfigCore
    KF5::ConfigWidgets
    KF5::KIOWidgets
    KF5::I18n
    KF5::TextWidgets
    KF5::WidgetsAddons
    )

set_target_properties(KF5ContactEditor PROPERTIES
    VERSION ${AKONADICONTACT_VERSION}
    SOVERSION ${AKONADICONTACT_SOVERSION}
    EXPORT_NAME ContactEditor
    )

install(TARGETS
    KF5ContactEditor
    EXPORT KF5ContactEditorTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS}
    )

ecm_generate_pri_file(BASE_NAME ContactEditor
    LIB_NAME KF5ContactEditor
    DEPS "KContacts" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/ContactEditor
    )

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

ecm_generate_headers(ContactEditor_CamelCase_HEADERS
    HEADER_NAMES
    ContactEditorPagePlugin
    REQUIRED_HEADERS ContactEditor_HEADERS
    PREFIX Akonadi
    )

ecm_generate_headers(ContactEditorWidget_CamelCase_HEADERS
    HEADER_NAMES
    CategoriesEditAbstractWidget
    REQUIRED_HEADERS ContactEditorWidget_HEADERS
    PREFIX Akonadi
    RELATIVE editor/widgets/
    )

install( FILES
    ${ContactEditor_CamelCase_HEADERS}
    ${ContactEditorWidget_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/AkonadiContactEditor/Akonadi COMPONENT Devel
    )

install( FILES
    ${ContactEditor_HEADERS}
    ${ContactEditorWidget_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/contacteditor_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/AkonadiContactEditor/akonadi COMPONENT Devel
    )



if (BUILD_TESTING)
    add_subdirectory(editor/addresseditor/autotests/)
    add_subdirectory(editor/generalinfoeditor/autotests/)
    add_subdirectory(editor/generalinfoeditor/tests)
    add_subdirectory(editor/customfieldeditor/autotests/)
    add_subdirectory(editor/customfieldeditor/tests)
    add_subdirectory(editor/widgets/autotests/)
endif()

install(FILES editor/pics/world.jpg DESTINATION ${KDE_INSTALL_DATADIR_KF}/akonadi/contact/pics)
install(FILES editor/data/zone.tab DESTINATION ${KDE_INSTALL_DATADIR_KF}/akonadi/contact/data)

if (BUILD_QCH)
    ecm_add_qch(
        KF5ContactEditor_QCH
        NAME KF5ContactEditor
        BASE_NAME KF5ContactEditor
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${ContactEditor_HEADERS}
        ${ContactEditorWidget_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
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
   ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact-editor_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/AkonadiContactEditor COMPONENT Devel
)
