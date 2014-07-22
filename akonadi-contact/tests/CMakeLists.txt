include(ECMMarkAsTest)

find_package(Qt5Test CONFIG REQUIRED)


# convenience macro to add akonadi demo application
macro(add_akonadi_contact_demo _source)
  set(_test ${_source})
  add_executable(${_test} ${_test})
  target_link_libraries(${_test}
      KF5::AkonadiMime
     KF5::AkonadiContact
     Qt5::Test)
  add_test(${_test} ${_test})
  ecm_mark_as_test(${_test})
endmacro()

########### next target ###############

add_akonadi_contact_demo(emailaddressselectionwidgettest.cpp)
add_akonadi_contact_demo(emailaddressselectiondialogtest.cpp)
