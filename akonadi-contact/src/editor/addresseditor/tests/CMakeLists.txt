if (NOT QTWEBENGINE_EXPERIMENTAL_OPTION)
set(addresseditor_SRCS
    main.cpp
    ../addresseslocationwidget.cpp
    ../webkit/addresseslocationviewer.cpp
    ../addresseslocationgrantleeformater.cpp
    ../addressgrantleeobject.cpp
    ../iconnamecache.cpp
    ../addresslocationwidget.cpp
    ../selectaddresstypecombobox.cpp
    ../addresstypedialog.cpp
    )

add_executable(addresseditortest ${addresseditor_SRCS})

target_link_libraries(addresseditortest
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

endif()
