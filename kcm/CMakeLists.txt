
add_definitions(-DTRANSLATION_DOMAIN=\"kcm_akonadicontact_actions\")
########### next target ###############
add_library(kcm_akonadicontact_actions MODULE)

target_sources(kcm_akonadicontact_actions PRIVATE
    kcmakonadicontactactions.cpp)

ki18n_wrap_ui(kcm_akonadicontact_actions akonadicontactactions.ui)

configure_file( ${Akonadi-Contact_SOURCE_DIR}/src/akonadi-contacts/actions/contactactionssettings.kcfg.cmake ${CMAKE_CURRENT_BINARY_DIR}/contactactionssettings.kcfg @ONLY)
kconfig_add_kcfg_files(kcm_akonadicontact_actions ${Akonadi-Contact_SOURCE_DIR}/src/akonadi-contacts/actions/contactactionssettings.kcfgc)



#kcoreaddons_desktop_to_json(kcm_akonadicontact_actions akonadicontact_actions.desktop DEFAULT_SERVICE_TYPE)

target_link_libraries(kcm_akonadicontact_actions KF5::ConfigWidgets KF5::I18n KF5::Completion) 



install(TARGETS kcm_akonadicontact_actions DESTINATION ${KDE_INSTALL_PLUGINDIR})

########### install files ###############

install(FILES akonadicontact_actions.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
