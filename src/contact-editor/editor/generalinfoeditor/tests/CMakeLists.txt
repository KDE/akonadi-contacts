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
    KPim6::ContactEditor
    KF6::Contacts
    KF6::I18n
    KF6::Completion
    KF6::IconThemes
    KF6::WidgetsAddons
    KF6::KIOCore
    KPim6::AkonadiWidgets

    )

