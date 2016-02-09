set(customfieldeditor_SRCS
    main.cpp
    )

add_executable(customfieldeditortest ${customfieldeditor_SRCS})

target_link_libraries(customfieldeditortest
    Qt5::Widgets
    KF5::AkonadiContact
    KF5::Contacts
    KF5::I18n
    KF5::Completion
    Qt5::WebKitWidgets
    Grantlee5::Templates
    KF5::IconThemes
    KF5::WidgetsAddons
    )
