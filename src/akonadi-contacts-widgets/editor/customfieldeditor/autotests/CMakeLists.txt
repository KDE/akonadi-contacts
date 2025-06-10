# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
set(customfieldswidgettest_SRCS
    customfieldswidgettest.cpp
    customfieldswidgettest.h
    ../customfieldswidget.cpp
    ../customfieldeditorwidget.cpp
    ../customfieldslistwidget.cpp
    ../customfieldsmodel.cpp
    ../customfieldslistdelegate.cpp
    ../../utils/utils.cpp
)
add_executable(customfieldswidgettest ${customfieldswidgettest_SRCS})
add_test(NAME customfieldswidgettest COMMAND customfieldswidgettest)
ecm_mark_as_test(customfieldswidgettest)
target_link_libraries(
    customfieldswidgettest
    Qt::Test
    Qt::Widgets
    KPim6::AkonadiContactWidgets
    KF6::Contacts
    KF6::I18n
    KF6::Completion
    KF6::ConfigCore
    KF6::WidgetsAddons
)

add_executable(
    customfieldeditorwidgettest
    customfieldeditorwidgettest.cpp
    customfieldeditorwidgettest.h
    ../customfieldeditorwidget.cpp
)
add_test(NAME customfieldeditorwidgettest COMMAND customfieldeditorwidgettest)
ecm_mark_as_test(customfieldeditorwidgettest)
target_link_libraries(
    customfieldeditorwidgettest
    Qt::Test
    Qt::Widgets
    KPim6::AkonadiContactWidgets
    KF6::Contacts
    KF6::I18n
    KF6::Completion
    KF6::WidgetsAddons
)

add_executable(customfieldslistwidgettest)
target_sources(
    customfieldslistwidgettest
    PRIVATE
        customfieldslistwidgettest.cpp
        customfieldslistwidgettest.h
        ../customfieldslistwidget.cpp
        ../customfieldsmodel.cpp
        ../customfieldslistdelegate.cpp
        ../../utils/utils.cpp
)
add_test(NAME customfieldslistwidgettest COMMAND customfieldslistwidgettest)
ecm_mark_as_test(customfieldslistwidgettest)
target_link_libraries(
    customfieldslistwidgettest
    Qt::Test
    Qt::Widgets
    KPim6::AkonadiContactWidgets
    KF6::Contacts
    KF6::I18n
    KF6::Completion
    KF6::ConfigCore
    KF6::WidgetsAddons
)
