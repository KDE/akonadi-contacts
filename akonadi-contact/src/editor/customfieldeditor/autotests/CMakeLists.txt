set(customfieldswidgettest_SRCS customfieldswidgettest.cpp ../customfieldswidget.cpp ../customfieldeditorwidget.cpp ../customfieldslistwidget.cpp ../customfieldsmodel.cpp
    ../../../customfields.cpp ../customfieldslistdelegate.cpp ../../../customfieldmanager.cpp)
add_executable(customfieldswidgettest ${customfieldswidgettest_SRCS})
add_test(customfieldswidgettest customfieldswidgettest)
ecm_mark_as_test(customfieldswidgettest)
target_link_libraries(customfieldswidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion KF5::ConfigCore KF5::WidgetsAddons)


set(customfieldeditorwidgettest_SRCS customfieldeditorwidgettest.cpp ../customfieldeditorwidget.cpp ../../../customfields.cpp)
add_executable(customfieldeditorwidgettest ${customfieldeditorwidgettest_SRCS})
add_test(customfieldeditorwidgettest customfieldeditorwidgettest)
ecm_mark_as_test(customfieldeditorwidgettest)
target_link_libraries(customfieldeditorwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion KF5::WidgetsAddons)

set(customfieldslistwidgettest_SRCS customfieldslistwidgettest.cpp ../customfieldslistwidget.cpp ../../../customfields.cpp ../customfieldsmodel.cpp
    ../customfieldslistdelegate.cpp ../../../customfieldmanager.cpp)
add_executable(customfieldslistwidgettest ${customfieldslistwidgettest_SRCS})
add_test(customfieldslistwidgettest customfieldslistwidgettest)
ecm_mark_as_test(customfieldslistwidgettest)
target_link_libraries(customfieldslistwidgettest Qt5::Test  Qt5::Widgets KF5::AkonadiContact KF5::Contacts KF5::I18n KF5::Completion KF5::ConfigCore KF5::WidgetsAddons)
