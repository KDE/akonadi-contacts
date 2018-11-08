include(ECMMarkAsTest)

find_package(Qt5Test CONFIG REQUIRED)

set(phonewidgettest_SRCS phonewidgettest.cpp)
add_executable(phonewidgettest ${phonewidgettest_SRCS})
add_test(NAME phonewidgettest COMMAND phonewidgettest)
ecm_mark_as_test(phonewidgettest)
target_link_libraries(phonewidgettest Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion KF5::IconThemes)


set(mailwidgettest_SRCS mailwidgettest.cpp)
add_executable(mailwidgettest ${mailwidgettest_SRCS})
add_test(NAME mailwidgettest COMMAND mailwidgettest)
ecm_mark_as_test(mailwidgettest)
target_link_libraries(mailwidgettest Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion KF5::IconThemes)

set(messagingwidgettest_SRCS messagingwidgettest.cpp ../../widgets/preferredlineeditwidget.cpp)
add_executable(messagingwidgettest ${messagingwidgettest_SRCS})
add_test(NAME messagingwidgettest COMMAND messagingwidgettest)
ecm_mark_as_test(messagingwidgettest)
target_link_libraries(messagingwidgettest Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion KF5::Service KF5::IconThemes)



set(contactselecttypecomboboxtest_SRCS contactselecttypecomboboxtest.cpp)
add_executable(contactselecttypecomboboxtest ${contactselecttypecomboboxtest_SRCS})
add_test(NAME contactselecttypecomboboxtest COMMAND contactselecttypecomboboxtest)
ecm_mark_as_test(contactselecttypecomboboxtest)
target_link_libraries(contactselecttypecomboboxtest Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::I18n )


set(nicknamewidgettest_SRCS nicknamewidgettest.cpp)
add_executable(nicknamewidgettest ${nicknamewidgettest_SRCS})
add_test(NAME nicknamewidgettest COMMAND nicknamewidgettest)
ecm_mark_as_test(nicknamewidgettest)
target_link_libraries(nicknamewidgettest Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::I18n KF5::Completion)


set(messageformattingwidgettest_SRCS messageformattingwidgettest.cpp)
add_executable(messageformattingwidgettest ${messageformattingwidgettest_SRCS})
add_test(NAME messageformattingwidgettest COMMAND messageformattingwidgettest)
ecm_mark_as_test(messageformattingwidgettest)
target_link_libraries(messageformattingwidgettest Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::I18n )
