add_definitions(-DTRANSLATION_DOMAIN=\"akonadicontact5-serializer\")

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()

set(akonadi_serializer_addressee_SRCS
    akonadi_serializer_addressee.cpp
)
add_library(akonadi_serializer_addressee MODULE ${akonadi_serializer_addressee_SRCS})
target_link_libraries(akonadi_serializer_addressee
    KF5::Contacts
    KF5::AkonadiCore
    KF5::I18n
    KF5::AkonadiSearch
)
install(TARGETS akonadi_serializer_addressee
    DESTINATION ${KDE_INSTALL_PLUGINDIR}
)
install(FILES akonadi_serializer_addressee.desktop
    DESTINATION ${KDE_INSTALL_DATADIR}/akonadi/plugins/serializer
)



set(akonadi_serializer_contactgroup_SRCS
    akonadi_serializer_contactgroup.cpp
)
add_library(akonadi_serializer_contactgroup MODULE ${akonadi_serializer_contactgroup_SRCS})
target_link_libraries(akonadi_serializer_contactgroup
    KF5::Contacts
    KF5::AkonadiCore
    KF5::I18n
    KF5::AkonadiContact
    KF5::AkonadiSearch
)
install(TARGETS akonadi_serializer_contactgroup
    DESTINATION ${KDE_INSTALL_PLUGINDIR}
)
install(FILES akonadi_serializer_contactgroup.desktop
    DESTINATION ${KDE_INSTALL_DATADIR}/akonadi/plugins/serializer
)
