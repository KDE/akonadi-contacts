if (QTWEBENGINE_EXPERIMENTAL_OPTION)
    set(akonadicontact_addresslocation_web_editor_SRCS
        ../webengine/addresseslocationengineviewer.cpp
        ../webengine/addresseslocationenginepage.cpp
        )
    set(akonadicontact_webengine_LIB Qt5::WebEngine Qt5::WebEngineWidgets)
else()
   set(akonadicontact_addresslocation_web_editor_SRCS
       ../webkit/addresseslocationviewer.cpp
       )
   set(akonadicontact_webengine_LIB Qt5::WebKitWidgets)
endif()

ecm_qt_declare_logging_category(akonadicontact_addresslocation_web_editor_SRCS HEADER akonadi_contact_debug.h IDENTIFIER AKONADICONTACT_LOG CATEGORY_NAME log_akonadi_contact)

set(addresseditor_SRCS
    ${akonadicontact_addresslocation_web_editor_SRCS}
    main.cpp
    ../addresseslocationwidget.cpp
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
    Grantlee5::Templates
    KF5::IconThemes
    KF5::WidgetsAddons
    ${akonadicontact_webengine_LIB}
    )

