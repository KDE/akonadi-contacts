add_definitions(-DTRANSLATION_DOMAIN=\"akonadicontact5-serializer\")

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()

add_library(akonadi_serializer_addressee MODULE)
target_sources(akonadi_serializer_addressee PRIVATE
    akonadi_serializer_addressee.cpp
)


ecm_qt_declare_logging_category(akonadi_serializer_addressee HEADER serializer_debug.h IDENTIFIER AKONADI_SERIALIZER_CONTACT_LOG CATEGORY_NAME org.kde.pim.contact_serializer
        DESCRIPTION "serializer contact (plugin)"
        EXPORT AKONADICONTACTS
    )


target_link_libraries(akonadi_serializer_addressee
    KF5::Contacts
    KF5::AkonadiCore
    KF5::I18n
)
install(TARGETS akonadi_serializer_addressee
    DESTINATION ${KDE_INSTALL_PLUGINDIR}
)
install(FILES akonadi_serializer_addressee.desktop
    DESTINATION ${KDE_INSTALL_DATADIR}/akonadi/plugins/serializer
)

##################################

add_library(akonadi_serializer_contactgroup MODULE)
target_sources(akonadi_serializer_contactgroup PRIVATE
    akonadi_serializer_contactgroup.cpp
)
target_link_libraries(akonadi_serializer_contactgroup
    KF5::Contacts
    KF5::AkonadiCore
    KF5::I18n
    KF5::AkonadiContact
)
install(TARGETS akonadi_serializer_contactgroup
    DESTINATION ${KDE_INSTALL_PLUGINDIR}
)
install(FILES akonadi_serializer_contactgroup.desktop
    DESTINATION ${KDE_INSTALL_DATADIR}/akonadi/plugins/serializer
)
