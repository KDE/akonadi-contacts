# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(categorieseditwidgetplugin SOURCES
    categorieseditwidget.cpp categorieseditwidget.h INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/akonadi/contacts/plugins)

target_link_libraries(categorieseditwidgetplugin
    KF5::AkonadiWidgets KF5::ContactEditor KF${KF_MAJOR_VERSION}::Service
    )
