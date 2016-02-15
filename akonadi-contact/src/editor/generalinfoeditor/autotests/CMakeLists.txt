set(phonewidgettest_SRCS phonewidgettest.cpp ../phone/phonewidget.cpp ../phone/phonecomboboxtype.cpp)
add_executable(phonewidgettest ${phonewidgettest_SRCS})
add_test(phonewidgettest phonewidgettest)
ecm_mark_as_test(phonewidgettest)
target_link_libraries(phonewidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion)


set(mailwidgettest_SRCS mailwidgettest.cpp ../mail/mailwidget.cpp)
add_executable(mailwidgettest ${mailwidgettest_SRCS})
add_test(mailwidgettest mailwidgettest)
ecm_mark_as_test(mailwidgettest)
target_link_libraries(mailwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion)

# FIXME: depends on messagingwidget but that one is not exported
# set(messagingwidgettest_SRCS messagingwidgettest.cpp )
# add_executable(messagingwidgettest ${messagingwidgettest_SRCS})
# add_test(messagingwidgettest messagingwidgettest)
# ecm_mark_as_test(messagingwidgettest)
# target_link_libraries(messagingwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion)
