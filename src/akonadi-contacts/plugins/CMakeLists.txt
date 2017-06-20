set(categorieseditwidgetplugin_SRCS
    categorieseditwidget.cpp
    )

kcoreaddons_add_plugin(categorieseditwidgetplugin JSON categorieseditwidgetplugin.json SOURCES
    ${categorieseditwidgetplugin_SRCS} INSTALL_NAMESPACE akonadi/contacts/plugins)

target_link_libraries(categorieseditwidgetplugin
    KF5::AkonadiWidgets KF5::ContactEditor KF5::Service
    )
