set(customfieldswidgettest_SRCS customfieldswidgettest.cpp ../customfieldswidget.cpp ../customfieldeditorwidget.cpp ../customfieldslistwidget.cpp ../customfieldsmodel.cpp
    ../customfieldslistdelegate.cpp ../../utils/utils.cpp)
add_executable(customfieldswidgettest ${customfieldswidgettest_SRCS})
add_test(NAME customfieldswidgettest COMMAND customfieldswidgettest)
ecm_mark_as_test(customfieldswidgettest)
target_link_libraries(customfieldswidgettest Qt5::Test Qt5::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion KF5::ConfigCore KF5::WidgetsAddons)


set(customfieldeditorwidgettest_SRCS customfieldeditorwidgettest.cpp ../customfieldeditorwidget.cpp)
add_executable(customfieldeditorwidgettest ${customfieldeditorwidgettest_SRCS})
add_test(NAME customfieldeditorwidgettest COMMAND customfieldeditorwidgettest)
ecm_mark_as_test(customfieldeditorwidgettest)
target_link_libraries(customfieldeditorwidgettest Qt5::Test Qt5::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion KF5::WidgetsAddons)

set(customfieldslistwidgettest_SRCS customfieldslistwidgettest.cpp ../customfieldslistwidget.cpp ../customfieldsmodel.cpp
    ../customfieldslistdelegate.cpp  ../../utils/utils.cpp)
add_executable(customfieldslistwidgettest ${customfieldslistwidgettest_SRCS})
add_test(NAME customfieldslistwidgettest COMMAND customfieldslistwidgettest)
ecm_mark_as_test(customfieldslistwidgettest)
target_link_libraries(customfieldslistwidgettest Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion KF5::ConfigCore KF5::WidgetsAddons)
