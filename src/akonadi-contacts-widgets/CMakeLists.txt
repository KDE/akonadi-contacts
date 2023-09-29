# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause



add_library(KPim6AkonadiContactWidgets)
add_library(KPim6::AkonadiContactWidgets ALIAS KPim6AkonadiContactWidgets)


ecm_setup_version(PROJECT VARIABLE_PREFIX AKONADICONTACT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-contacts-widgets_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactWidgetsConfigVersion.cmake"
    SOVERSION 6
    )

ki18n_wrap_ui(akonadicontacts_widgets_UI_LIB_SRC contactgroupeditor.ui)

target_sources(KPim6AkonadiContactWidgets PRIVATE
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
    editor/widgets/imagewidget.h
    editor/widgets/kwidgetlister_p.h
    editor/widgets/preferredlineeditwidget.h
    editor/widgets/contacteditorcombobox.h
    editor/businesseditor/freebusyeditwidget.h
    editor/businesseditor/businesseditorwidget.h
    akonadi_contact_widgets_private_export.h
    contacteditorpageplugin.h
    abstractcontacteditorwidget_p.h
    customfieldmanager_p.h
    contactmetadatabase_p.h
    customfields_p.h

    contacteditordialog.cpp
    contacteditordialog.h

    contacteditor.cpp
    contacteditor.h

    standardcontactactionmanager.cpp
    standardcontactactionmanager.h

    contactviewer.cpp
    contactviewer.h

    contactviewerdialog.h
    contactviewerdialog.cpp

    contactmetadataakonadi.cpp
    contactmetadataakonadi_p.h

    contactgroupviewer.cpp
    contactgroupviewer.h

    textbrowser_p.h
    textbrowser.cpp
    grantlee/grantleecontactviewer.h
    grantlee/grantleecontactviewer.cpp

    # contact group editor
    contactgroupeditor_p.h
    contactgroupeditor.cpp
    contactgroupeditor.h
    contactgroupeditordialog.cpp
    contactgroupeditordialog.h
    contactgroupeditordelegate.cpp
    contactgroupeditordelegate_p.h
    
    waitingoverlay.cpp
    waitingoverlay_p.h
    
    abstractemailaddressselectiondialog.cpp
    abstractemailaddressselectiondialog.h
    emailaddressselectiondialog.cpp
    emailaddressselectiondialog.h
    emailaddressrequester.cpp
    emailaddressrequester.h
    emailaddressselectionwidget.cpp
    emailaddressselectionwidget.h
    ${akonadicontacts_widgets_UI_LIB_SRC}
)

target_sources(KPim6AkonadiContactWidgets PRIVATE
    job/addemailaddressjob.cpp
    job/addemaildisplayjob.cpp
    job/addemailaddressjob.h
    job/addemaildisplayjob.h
    job/addcontactjob.h
    job/addcontactjob.cpp
    job/openemailaddressjob.cpp
    job/openemailaddressjob.h
)

target_sources(KPim6AkonadiContactWidgets PRIVATE
    widgets/selectaddressbookdialog.cpp
    widgets/selectaddressbookdialog.h
)

target_sources(KPim6AkonadiContactWidgets PRIVATE
    recipientspicker/recipientseditormanager.cpp
    recipientspicker/recipientspickerwidget.cpp
    recipientspicker/recipientseditormanager.h
    recipientspicker/recipientspickerwidget.h
    )


ecm_qt_declare_logging_category(KPim6AkonadiContactWidgets HEADER contacteditor_debug.h IDENTIFIER CONTACTEDITOR_LOG CATEGORY_NAME org.kde.pim.contacteditor
        DESCRIPTION "akonadicontact (contact editor)"
        EXPORT AKONADICONTACTS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim6AkonadiContactWidgets PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(KPim6AkonadiContactWidgets BASE_NAME akonadi-contact-widgets)


target_include_directories(KPim6AkonadiContactWidgets INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContactWidgets>")
target_include_directories(KPim6AkonadiContactWidgets PUBLIC "$<BUILD_INTERFACE:${Akonadi-Contact_SOURCE_DIR}/src/akonadi-contacts-widgets;${Akonadi-Contact_BINARY_DIR}/src/akonadi-contacts-widgets>")

target_link_libraries(KPim6AkonadiContactWidgets
    PUBLIC
    KF6::Contacts
    Qt::Widgets
    KPim6::AkonadiContactCore
    PRIVATE
    KF6::Completion
    KF6::ConfigCore
    KF6::KIOWidgets
    KF6::I18n
    KF6::TextWidgets
    KF6::WidgetsAddons
    KPim6::AkonadiWidgets
    KF6::Prison
    KF6::XmlGui
    KF6::Codecs
    )

set_target_properties(KPim6AkonadiContactWidgets PROPERTIES
    VERSION ${AKONADICONTACT_VERSION}
    SOVERSION ${AKONADICONTACT_SOVERSION}
    EXPORT_NAME AkonadiContactWidgets
    )

install(TARGETS
    KPim6AkonadiContactWidgets
    EXPORT KPim6AkonadiContactWidgetsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    )


ecm_generate_headers(AkonadiContactWidgets_CamelCase_HEADERS
    HEADER_NAMES
    ContactEditorPagePlugin
    ContactEditorDialog
    ContactEditor
    ContactViewer
    StandardContactActionManager
    ContactViewerDialog
    ContactGroupViewer
    ContactGroupEditor
    ContactGroupEditorDialog
    
    EmailAddressSelectionDialog
    AbstractEmailAddressSelectionDialog
    EmailAddressRequester
    EmailAddressSelectionWidget

    REQUIRED_HEADERS AkonadiContactWidgets_HEADERS
    PREFIX Akonadi
    )

ecm_generate_headers(AkonadiContactWidgetsRecipients_CamelCase_HEADERS
    HEADER_NAMES
    RecipientsEditorManager
    RecipientsPickerWidget
    REQUIRED_HEADERS AkonadiContactWidgetsRecipients_HEADERS
    PREFIX Akonadi
    RELATIVE recipientspicker
    )

ecm_generate_headers(AkonadiContactWidgetsGrantlee_CamelCase_HEADERS
    HEADER_NAMES
    GrantleeContactViewer
    REQUIRED_HEADERS AkonadiContactWidgetsGrantlee_HEADERS
    RELATIVE grantlee
    PREFIX Akonadi
)

ecm_generate_headers(AkonadiContactWidgetsWidgets_CamelCase_HEADERS
    HEADER_NAMES
    SelectAddressBookDialog
    REQUIRED_HEADERS AkonadiContactWidgetsWidgets_HEADERS
    PREFIX Akonadi
    RELATIVE widgets
    )

ecm_generate_headers(AkonadiContactWidgetsJob_CamelCase_HEADERS
    HEADER_NAMES
    AddEmailAddressJob
    AddEmailDisplayJob
    AddContactJob
    OpenEmailAddressJob
    REQUIRED_HEADERS AkonadiContactWidgetsJob_HEADERS
    PREFIX Akonadi
    RELATIVE job
    )


install( FILES
    ${AkonadiContactWidgets_CamelCase_HEADERS}
    ${AkonadiContactWidgetsJob_CamelCase_HEADERS}
    ${AkonadiContactWidgetsRecipients_CamelCase_HEADERS}
    ${AkonadiContactWidgetsWidgets_CamelCase_HEADERS}
    ${AkonadiContactWidgetsGrantlee_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContactWidgets/Akonadi COMPONENT Devel
    )

install( FILES
    ${AkonadiContactWidgets_HEADERS}
    ${AkonadiContactWidgetsJob_HEADERS}
    ${AkonadiContactWidgetsWidgets_HEADERS}
    ${AkonadiContactWidgetsRecipients_HEADERS}
    ${AkonadiContactWidgetsGrantlee_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact-widgets_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContactWidgets/akonadi COMPONENT Devel
    )



if (BUILD_TESTING)
    add_subdirectory(tests)
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
        KPim6AkonadiContactWidgets_QCH
        NAME KPim6AkonadiContactWidgets
        BASE_NAME KPim6AkonadiContactWidgets
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${AkonadiContactWidgets_HEADERS}
        ${AkonadiContactWidgetsRecipients_HEADERS}
        ${AkonadiContactWidgetsGrantlee_HEADERS}
        ${AkonadiContactWidgetsJob_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            AKONADI_CONTACT_WIDGETS_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()


set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6AkonadiContactWidgets")
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim6AkonadiContactWidgets_QCH
        FILE KPim6AkonadiContactWidgetsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim6AkonadiContactWidgetsQchTargets.cmake\")")
endif()
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimAkonadiContactWidgetsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactWidgetsConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactWidgetsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6AkonadiContactWidgetsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )


install(EXPORT KPim6AkonadiContactWidgetsTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KPim6AkonadiContactWidgetsTargets.cmake NAMESPACE KPim6::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contacts-widgets_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/AkonadiContactWidgets COMPONENT Devel
)
