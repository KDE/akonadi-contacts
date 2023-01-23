# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
include(ECMMarkAsTest)

#ecm_qt_declare_logging_category(contacteditor_addresslocation_web_editor_SRCS HEADER addresslocationeditorplugin_debug.h IDENTIFIER
#    ADDRESSLOCATIONEDITORPLUGIN_LOG CATEGORY_NAME org.kde.pim.addresslocationeditorplugin)

set(addresslocationwidget_SRCS addresslocationwidgettest.cpp addresslocationwidgettest.h ../addresslocationwidget.cpp ../selectaddresstypecombobox.cpp ../addresstypedialog.cpp)
add_executable(addresslocationwidget ${addresslocationwidget_SRCS})
add_test(NAME addresslocationwidget COMMAND addresslocationwidget)
ecm_mark_as_test(addresslocationwidget)
target_link_libraries(addresslocationwidget Qt::Test  Qt::Widgets KF5::ContactEditor KF${KF_MAJOR_VERSION}::Contacts KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::Completion KF${KF_MAJOR_VERSION}::WidgetsAddons)
