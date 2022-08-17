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
    KF5::ContactEditor
    KF5::Contacts
    KF5::I18n
    KF5::Completion
    KF5::IconThemes
    KF5::WidgetsAddons
    KF5::ConfigCore
    )
