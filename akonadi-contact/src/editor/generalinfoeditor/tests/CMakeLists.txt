set(generalinfoeditor_SRCS
    main.cpp
    ../generalinfowidget.cpp
    ../phone/phonewidget.cpp
    ../phone/phonelistwidget.cpp
    ../phone/phonewidgetlister.cpp
    ../../widgets/kwidgetlister.cpp
    )

add_executable(generalinfoeditortest ${generalinfoeditor_SRCS})

target_link_libraries(generalinfoeditortest
    Qt5::Widgets
    KF5::AkonadiContact
    KF5::Contacts
    KF5::I18n
    KF5::Completion
    KF5::IconThemes
    KF5::WidgetsAddons
    )

