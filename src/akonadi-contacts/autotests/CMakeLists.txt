include(ECMMarkAsTest)
include(ECMAddTests)

# convenience macro to add akonadi demo application
macro(add_akonadi_contact_demo _source)
  set(_test ${_source})
  get_filename_component( _name ${_source} NAME_WE )
  add_executable( ${_name} ${_test} )
  add_test(NAME ${_name} COMMAND ${_name} )
  target_link_libraries(${_name}
     KF5::AkonadiContact
     Qt::Test)
  ecm_mark_as_test(${_name})
endmacro()

########### next target ###############

add_akonadi_contact_demo(contactmetadataattributetest.cpp)

ecm_add_test(grantleeprinttest.cpp
    LINK_LIBRARIES KF5::AkonadiContact Qt::Test KF5::Contacts
)
