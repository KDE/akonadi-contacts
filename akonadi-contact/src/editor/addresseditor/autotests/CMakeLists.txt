include(ECMMarkAsTest)

if (QTWEBENGINE_SUPPORT_OPTION)
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

set(addresseslocationviewer_SRCS addresseslocationviewertest.cpp ${akonadicontact_addresslocation_web_editor_SRCS} ../addresseslocationgrantleeformater.cpp
    ../addressgrantleeobject.cpp ../iconnamecache.cpp)
add_executable(addresseslocationviewer ${addresseslocationviewer_SRCS})
add_test(addresseslocationviewer addresseslocationviewer)
ecm_mark_as_test(addresseslocationviewer)
target_link_libraries(addresseslocationviewer Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n ${akonadicontact_webengine_LIB} Grantlee5::Templates
    KF5::IconThemes KF5::WidgetsAddons)

set(addresslocationwidget_SRCS addresslocationwidgettest.cpp ../addresslocationwidget.cpp ../selectaddresstypecombobox.cpp ../addresstypedialog.cpp)
add_executable(addresslocationwidget ${addresslocationwidget_SRCS})
add_test(addresslocationwidget addresslocationwidget)
ecm_mark_as_test(addresslocationwidget)
target_link_libraries(addresslocationwidget Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion)

set(addresseslocationwidget_SRCS addresseslocationwidgettest.cpp ../addresseslocationwidget.cpp ${akonadicontact_addresslocation_web_editor_SRCS} ../addresseslocationgrantleeformater.cpp
    ../addressgrantleeobject.cpp ../iconnamecache.cpp ../addresslocationwidget.cpp ../selectaddresstypecombobox.cpp ../addresstypedialog.cpp)
add_executable(addresseslocationwidget ${addresseslocationwidget_SRCS})
add_test(addresseslocationwidget addresseslocationwidget)
ecm_mark_as_test(addresseslocationwidget)
target_link_libraries(addresseslocationwidget Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion ${akonadicontact_webengine_LIB}
    Grantlee5::Templates KF5::IconThemes KF5::WidgetsAddons)
