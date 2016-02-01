set(QT_REQUIRED_VERSION "5.4.0")
find_package(Qt5Test ${QT_REQUIRED_VERSION} CONFIG REQUIRED)

set(addresseslocationviewer_SRCS addresseslocationviewertest.cpp )
add_executable(addresseslocationviewer ${addresseslocationviewer_SRCS})
add_test(addresseslocationviewer addresseslocationviewer)
ecm_mark_as_test(addresseslocationviewer)
target_link_libraries(addresseslocationviewer Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n)


set(addresslocationwidget_SRCS addresslocationwidgettest.cpp )
add_executable(addresslocationwidget ${addresslocationwidget_SRCS})
add_test(addresslocationwidget addresslocationwidget)
ecm_mark_as_test(addresslocationwidget)
target_link_libraries(addresslocationwidget Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n)
