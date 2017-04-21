set(phonewidgettest_SRCS phonewidgettest.cpp ../phone/phonewidget.cpp ../phone/phonecomboboxtype.cpp ../phone/phonetypedialog.cpp
    ../../widgets/preferredlineeditwidget.cpp)
add_executable(phonewidgettest ${phonewidgettest_SRCS})
add_test(phonewidgettest phonewidgettest)
ecm_mark_as_test(phonewidgettest)
target_link_libraries(phonewidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion KF5::IconThemes)


set(mailwidgettest_SRCS mailwidgettest.cpp ../mail/mailwidget.cpp ../../widgets/preferredlineeditwidget.cpp)
add_executable(mailwidgettest ${mailwidgettest_SRCS})
add_test(mailwidgettest mailwidgettest)
ecm_mark_as_test(mailwidgettest)
target_link_libraries(mailwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion KF5::IconThemes)

set(messagingwidgettest_SRCS messagingwidgettest.cpp ../messaging/messagingwidget.cpp ../../im/imaddress.cpp ../../widgets/preferredlineeditwidget.cpp)
add_executable(messagingwidgettest ${messagingwidgettest_SRCS})
add_test(messagingwidgettest messagingwidgettest)
ecm_mark_as_test(messagingwidgettest)
target_link_libraries(messagingwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion KF5::Service KF5::IconThemes)



set(akonadicontactselecttypecomboboxtest_SRCS akonadicontactselecttypecomboboxtest.cpp)
add_executable(akonadicontactselecttypecomboboxtest ${akonadicontactselecttypecomboboxtest_SRCS})
add_test(akonadicontactselecttypecomboboxtest akonadicontactselecttypecomboboxtest)
ecm_mark_as_test(akonadicontactselecttypecomboboxtest)
target_link_libraries(akonadicontactselecttypecomboboxtest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::I18n )


set(nicknamewidgettest_SRCS nicknamewidgettest.cpp)
add_executable(nicknamewidgettest ${nicknamewidgettest_SRCS})
add_test(nicknamewidgettest nicknamewidgettest)
ecm_mark_as_test(nicknamewidgettest)
target_link_libraries(nicknamewidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::I18n )


set(messageformattingwidgettest_SRCS messageformattingwidgettest.cpp)
add_executable(messageformattingwidgettest ${messageformattingwidgettest_SRCS})
add_test(messageformattingwidgettest messageformattingwidgettest)
ecm_mark_as_test(messageformattingwidgettest)
target_link_libraries(messageformattingwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::I18n )
