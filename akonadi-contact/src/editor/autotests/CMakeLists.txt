set(QT_REQUIRED_VERSION "5.2.0")
find_package(Qt5Test ${QT_REQUIRED_VERSION} CONFIG REQUIRED)

set( emaileditdialogtest_source emaileditdialogtest.cpp ../emaileditwidget.cpp )
add_executable( emaileditdialogtest ${emaileditdialogtest_source})
add_test(emaileditdialogtest emaileditdialogtest)
ecm_mark_as_test(emaileditdialogtest)
target_link_libraries( emaileditdialogtest Qt5::Test Qt5::Widgets KF5::Contacts KF5::AkonadiContact)


set(emaileditwidgettest_SRCS emaileditwidgettest.cpp ../emaileditwidget.cpp)
add_executable(emaileditwidgettest ${emaileditwidgettest_SRCS})
add_test(emaileditwidgettest emaileditwidgettest)
ecm_mark_as_test(emaileditwidgettest)
target_link_libraries(emaileditwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts)


