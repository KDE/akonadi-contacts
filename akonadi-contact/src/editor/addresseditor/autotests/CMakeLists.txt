if (NOT QTWEBENGINE_EXPERIMENTAL_OPTION)
    set(addresseslocationviewer_SRCS addresseslocationviewertest.cpp ../webkit/addresseslocationviewer.cpp ../addresseslocationgrantleeformater.cpp
        ../addressgrantleeobject.cpp ../iconnamecache.cpp)
    add_executable(addresseslocationviewer ${addresseslocationviewer_SRCS})
    add_test(addresseslocationviewer addresseslocationviewer)
    ecm_mark_as_test(addresseslocationviewer)
    target_link_libraries(addresseslocationviewer Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n Qt5::WebKitWidgets Grantlee5::Templates KF5::IconThemes KF5::WidgetsAddons)


    set(addresslocationwidget_SRCS addresslocationwidgettest.cpp ../addresslocationwidget.cpp ../selectaddresstypecombobox.cpp ../addresstypedialog.cpp)
    add_executable(addresslocationwidget ${addresslocationwidget_SRCS})
    add_test(addresslocationwidget addresslocationwidget)
    ecm_mark_as_test(addresslocationwidget)
    target_link_libraries(addresslocationwidget Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion)

    set(addresseslocationwidget_SRCS addresseslocationwidgettest.cpp ../addresseslocationwidget.cpp ../webkit/addresseslocationviewer.cpp ../addresseslocationgrantleeformater.cpp
        ../addressgrantleeobject.cpp ../iconnamecache.cpp ../addresslocationwidget.cpp ../selectaddresstypecombobox.cpp ../addresstypedialog.cpp)
    add_executable(addresseslocationwidget ${addresseslocationwidget_SRCS})
    add_test(addresseslocationwidget addresseslocationwidget)
    ecm_mark_as_test(addresseslocationwidget)
    target_link_libraries(addresseslocationwidget Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion Qt5::WebKitWidgets
        Grantlee5::Templates KF5::IconThemes KF5::WidgetsAddons)
endif()
