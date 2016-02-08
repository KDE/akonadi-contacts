set(phonewidgettest_SRCS phonewidgettest.cpp ../phone/phonewidget.cpp)
add_executable(phonewidgettest ${phonewidgettest_SRCS})
add_test(phonewidgettest phonewidgettest)
ecm_mark_as_test(phonewidgettest)
target_link_libraries(phonewidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n )


