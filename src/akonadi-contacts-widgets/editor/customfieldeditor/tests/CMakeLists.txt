# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
set(customfieldeditor_SRCS
    ../customfieldswidget.cpp
    ../customfieldeditorwidget.cpp
    ../customfieldslistwidget.cpp
    ../customfieldsmodel.cpp
    ../customfieldslistdelegate.cpp
    ../../utils/utils.cpp
    main.cpp
)

add_executable(customfieldeditortest ${customfieldeditor_SRCS})

target_link_libraries(customfieldeditortest
    Qt::Widgets
    KPim6::AkonadiContactWidgets
    KF6::Contacts
    KF6::I18n
    KF6::Completion
    KF6::IconThemes
    KF6::WidgetsAddons
    KF6::ConfigCore
)
