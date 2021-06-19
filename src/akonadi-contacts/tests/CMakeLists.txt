include(ECMMarkAsTest)

# convenience macro to add akonadi demo application
macro(add_akonadi_contact_demo _source)
  set(_test ${_source})
  get_filename_component( _name ${_source} NAME_WE )
  add_executable( ${_name} ${_test} )
  target_link_libraries(${_name}
     KF5::AkonadiContact
     KF5::Completion
     KF5::I18n
     KF5::WidgetsAddons
     Qt::Test)
  ecm_mark_as_test(${_name})
endmacro()

########### next target ###############

add_akonadi_contact_demo(emailaddressselectionwidgettest.cpp)
add_akonadi_contact_demo(emailaddressselectiondialogtest.cpp)
add_akonadi_contact_demo(emailaddressselectionmodeltest.cpp)
