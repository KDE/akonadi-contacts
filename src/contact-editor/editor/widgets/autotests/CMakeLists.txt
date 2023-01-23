# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
set( preferredlineeditwidgettest_SRCS preferredlineeditwidgettest.cpp preferredlineeditwidgettest.h ../preferredlineeditwidget.cpp)
add_executable( preferredlineeditwidgettest ${preferredlineeditwidgettest_SRCS})
add_test(NAME preferredlineeditwidgettest COMMAND preferredlineeditwidgettest)
ecm_mark_as_test(preferredlineeditwidgettest)
target_link_libraries( preferredlineeditwidgettest Qt::Test Qt::Widgets KF${KF_MAJOR_VERSION}::Completion KF${KF_MAJOR_VERSION}::I18n)
