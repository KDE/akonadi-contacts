include(ECMMarkAsTest)

#ecm_qt_declare_logging_category(contacteditor_addresslocation_web_editor_SRCS HEADER addresslocationeditorplugin_debug.h IDENTIFIER
#    ADDRESSLOCATIONEDITORPLUGIN_LOG CATEGORY_NAME org.kde.pim.addresslocationeditorplugin)

set(addresslocationwidget_SRCS addresslocationwidgettest.cpp ../addresslocationwidget.cpp ../selectaddresstypecombobox.cpp ../addresstypedialog.cpp)
add_executable(addresslocationwidget ${addresslocationwidget_SRCS})
add_test(NAME addresslocationwidget COMMAND addresslocationwidget)
ecm_mark_as_test(addresslocationwidget)
target_link_libraries(addresslocationwidget Qt::Test  Qt::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion KF5::WidgetsAddons)
