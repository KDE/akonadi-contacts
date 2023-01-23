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
    KF${KF_MAJOR_VERSION}::Contacts
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::Completion
    KF${KF_MAJOR_VERSION}::IconThemes
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::ConfigCore
    )
