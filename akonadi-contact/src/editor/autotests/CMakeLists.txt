set(emaileditdialogtesttest_SRCS emaileditdialogtest.cpp ../emaileditwidget.cpp)
add_executable(emaileditdialogtestNAME emaileditdialogtest ${emaileditdialogtesttest_SRCS})
add_test(emaileditdialogtest emaileditdialogtest)
ecm_mark_as_test(emaileditdialogtest)
target_link_libraries(emaileditdialogtest Qt5::Test  KF5::Contacts)

