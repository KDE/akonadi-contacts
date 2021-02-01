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
    Qt5::Widgets
    KF5::ContactEditor
    KF5::Contacts
    KF5::I18n
    KF5::Completion
    KF5::IconThemes
    KF5::WidgetsAddons
    KF5::KIOCore
    )

