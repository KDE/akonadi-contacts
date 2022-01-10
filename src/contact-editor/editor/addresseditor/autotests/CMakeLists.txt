# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
include(ECMMarkAsTest)

#ecm_qt_declare_logging_category(contacteditor_addresslocation_web_editor_SRCS HEADER addresslocationeditorplugin_debug.h IDENTIFIER
#    ADDRESSLOCATIONEDITORPLUGIN_LOG CATEGORY_NAME org.kde.pim.addresslocationeditorplugin)

set(addresslocationwidget_SRCS addresslocationwidgettest.cpp addresslocationwidgettest.h ../addresslocationwidget.cpp ../selectaddresstypecombobox.cpp ../addresstypedialog.cpp)
add_executable(addresslocationwidget ${addresslocationwidget_SRCS})
add_test(NAME addresslocationwidget COMMAND addresslocationwidget)
ecm_mark_as_test(addresslocationwidget)
target_link_libraries(addresslocationwidget Qt${QT_MAJOR_VERSION}::Test  Qt${QT_MAJOR_VERSION}::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion KF5::WidgetsAddons)
