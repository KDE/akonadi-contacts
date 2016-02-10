set(customfieldeditor_SRCS
    ../customfieldswidget.cpp
    ../customfieldeditorwidget.cpp
    main.cpp
    )

add_executable(customfieldeditortest ${customfieldeditor_SRCS})

target_link_libraries(customfieldeditortest
    Qt5::Widgets
    KF5::AkonadiContact
    KF5::Contacts
    KF5::I18n
    KF5::Completion
    KF5::IconThemes
    KF5::WidgetsAddons
    )
