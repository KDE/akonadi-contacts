set(phonewidgettest_SRCS phonewidgettest.cpp ../phone/phonewidget.cpp ../phone/phonecomboboxtype.cpp ../../widgets/akonadicontactcombobox.cpp ../akonadicontactselecttypecombobox.cpp ../phone/phonetypedialog.cpp
    ../../widgets/preferredlineeditwidget.cpp)
add_executable(phonewidgettest ${phonewidgettest_SRCS})
add_test(phonewidgettest phonewidgettest)
ecm_mark_as_test(phonewidgettest)
target_link_libraries(phonewidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion KF5::IconThemes)


set(mailwidgettest_SRCS mailwidgettest.cpp ../mail/mailwidget.cpp ../../widgets/akonadicontactcombobox.cpp ../akonadicontactselecttypecombobox.cpp ../../widgets/preferredlineeditwidget.cpp)
add_executable(mailwidgettest ${mailwidgettest_SRCS})
add_test(mailwidgettest mailwidgettest)
ecm_mark_as_test(mailwidgettest)
target_link_libraries(mailwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion KF5::IconThemes)

set(messagingwidgettest_SRCS messagingwidgettest.cpp ../messaging/messagingwidget.cpp ../../im/imaddress.cpp ../akonadicontactselecttypecombobox.cpp ../../widgets/akonadicontactcombobox.cpp ../../widgets/preferredlineeditwidget.cpp)
add_executable(messagingwidgettest ${messagingwidgettest_SRCS})
add_test(messagingwidgettest messagingwidgettest)
ecm_mark_as_test(messagingwidgettest)
target_link_libraries(messagingwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion KF5::Service KF5::IconThemes)



set(akonadicontactselecttypecomboboxtest_SRCS akonadicontactselecttypecomboboxtest.cpp ../akonadicontactselecttypecombobox.cpp ../../widgets/akonadicontactcombobox.cpp)
add_executable(akonadicontactselecttypecomboboxtest ${akonadicontactselecttypecomboboxtest_SRCS})
add_test(akonadicontactselecttypecomboboxtest akonadicontactselecttypecomboboxtest)
ecm_mark_as_test(akonadicontactselecttypecomboboxtest)
target_link_libraries(akonadicontactselecttypecomboboxtest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::I18n )
