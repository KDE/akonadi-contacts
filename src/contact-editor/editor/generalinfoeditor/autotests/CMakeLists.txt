# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
include(ECMMarkAsTest)

set(phonewidgettest_SRCS phonewidgettest.cpp phonewidgettest.h)
add_executable(phonewidgettest ${phonewidgettest_SRCS})
add_test(NAME phonewidgettest COMMAND phonewidgettest)
ecm_mark_as_test(phonewidgettest)
target_link_libraries(phonewidgettest Qt${QT_MAJOR_VERSION}::Test  KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion)


set(mailwidgettest_SRCS mailwidgettest.cpp mailwidgettest.h)
add_executable(mailwidgettest ${mailwidgettest_SRCS})
add_test(NAME mailwidgettest COMMAND mailwidgettest)
ecm_mark_as_test(mailwidgettest)
target_link_libraries(mailwidgettest Qt${QT_MAJOR_VERSION}::Test KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion)

set(messagingwidgettest_SRCS messagingwidgettest.cpp messagingwidgettest.h ../../widgets/preferredlineeditwidget.cpp)
add_executable(messagingwidgettest ${messagingwidgettest_SRCS})
add_test(NAME messagingwidgettest COMMAND messagingwidgettest)
ecm_mark_as_test(messagingwidgettest)
target_link_libraries(messagingwidgettest Qt${QT_MAJOR_VERSION}::Test KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion KF5::Service)



set(contactselecttypecomboboxtest_SRCS contactselecttypecomboboxtest.cpp contactselecttypecomboboxtest.h)
add_executable(contactselecttypecomboboxtest ${contactselecttypecomboboxtest_SRCS})
add_test(NAME contactselecttypecomboboxtest COMMAND contactselecttypecomboboxtest)
ecm_mark_as_test(contactselecttypecomboboxtest)
target_link_libraries(contactselecttypecomboboxtest Qt${QT_MAJOR_VERSION}::Test  Qt${QT_MAJOR_VERSION}::Widgets KF5::ContactEditor KF5::I18n )


set(nicknamewidgettest_SRCS nicknamewidgettest.cpp nicknamewidgettest.h)
add_executable(nicknamewidgettest ${nicknamewidgettest_SRCS})
add_test(NAME nicknamewidgettest COMMAND nicknamewidgettest)
ecm_mark_as_test(nicknamewidgettest)
target_link_libraries(nicknamewidgettest Qt${QT_MAJOR_VERSION}::Test  Qt${QT_MAJOR_VERSION}::Widgets KF5::ContactEditor KF5::I18n KF5::Completion)

set(blogfeedwidgettest_SRCS blogfeedwidgettest.cpp blogfeedwidgettest.h)
add_executable(blogfeedwidgettest ${blogfeedwidgettest_SRCS})
add_test(NAME blogfeedwidgettest COMMAND blogfeedwidgettest)
ecm_mark_as_test(blogfeedwidgettest)
target_link_libraries(blogfeedwidgettest Qt${QT_MAJOR_VERSION}::Test  Qt${QT_MAJOR_VERSION}::Widgets KF5::ContactEditor KF5::I18n KF5::Completion)


set(messageformattingwidgettest_SRCS messageformattingwidgettest.cpp messageformattingwidgettest.h)
add_executable(messageformattingwidgettest ${messageformattingwidgettest_SRCS})
add_test(NAME messageformattingwidgettest COMMAND messageformattingwidgettest)
ecm_mark_as_test(messageformattingwidgettest)
target_link_libraries(messageformattingwidgettest Qt${QT_MAJOR_VERSION}::Test  Qt${QT_MAJOR_VERSION}::Widgets KF5::ContactEditor KF5::I18n )
