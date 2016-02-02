
set(addresseslocationviewer_SRCS addresseslocationviewertest.cpp ../addresseslocationviewer.cpp ../addresseslocationgrantleeformater.cpp ../addressgrantleeobject.cpp)
add_executable(addresseslocationviewer ${addresseslocationviewer_SRCS})
add_test(addresseslocationviewer addresseslocationviewer)
ecm_mark_as_test(addresseslocationviewer)
target_link_libraries(addresseslocationviewer Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n Qt5::WebKitWidgets Grantlee5::Templates)


set(addresslocationwidget_SRCS addresslocationwidgettest.cpp ../addresslocationwidget.cpp)
add_executable(addresslocationwidget ${addresslocationwidget_SRCS})
add_test(addresslocationwidget addresslocationwidget)
ecm_mark_as_test(addresslocationwidget)
target_link_libraries(addresslocationwidget Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion)
