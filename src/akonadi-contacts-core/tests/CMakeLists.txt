# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
include(ECMMarkAsTest)

# convenience macro to add akonadi demo application
macro(add_akonadi_contact_demo _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test})
    target_link_libraries(
        ${_name}
        KPim6::AkonadiContactCore
        Qt::Widgets
        Qt::Test
    )
    ecm_mark_as_test(${_name})
endmacro()

########### next target ###############

add_akonadi_contact_demo(emailaddressselectionmodeltest.cpp)
