set(generalinfoeditor_SRCS
    main.cpp
    ../generalinfowidget.cpp
    ../../widgets/kwidgetlister.cpp
    ../web/webwidgetlister.cpp
    ../web/weblistwidget.cpp
    ../web/webwidget.cpp
    ../mail/maillistwidget.cpp
    ../mail/mailwidgetlister.cpp
    ../messaging/messaginglistwidget.cpp
    ../messaging/messagingwidgetlister.cpp
    ../../widgets/imagewidget.cpp
    ../namewidget.cpp
    ../../utils/utils.cpp
    ../categorieseditwidget.cpp
    ../nameeditdialog.cpp
    ../../widgets/preferredlineeditwidget.cpp
    ../displaynameeditwidget.cpp
    )

add_executable(generalinfoeditortest ${generalinfoeditor_SRCS})

target_link_libraries(generalinfoeditortest
    Qt::Widgets
    KPim${KF_MAJOR_VERSION}::ContactEditor
    KF${KF_MAJOR_VERSION}::Contacts
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::Completion
    KF${KF_MAJOR_VERSION}::IconThemes
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::KIOCore
    KPim${KF_MAJOR_VERSION}::AkonadiWidgets

    )

