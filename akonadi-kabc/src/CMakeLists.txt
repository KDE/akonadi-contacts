set(akonadikabc_LIB_SRC
  contactparts.cpp 
)

add_library(KF5AkonadiKAbc ${akonadikabc_LIB_SRC})

generate_export_header(KF5AkonadiKAbc BASE_NAME akonadi-kabc)

add_library(KF5::KF5AkonadiKAbc ALIAS KF5AkonadiKAbc)

target_include_directories(KF5AkonadiKAbc INTERFACE "$<INSTALL_INTERFACE:${KF5_INCLUDE_INSTALL_DIR}/Akonadi/KAbc;${Boost_INCLUDE_DIR}>")
target_include_directories(KF5AkonadiKAbc PUBLIC "$<BUILD_INTERFACE:${Akonadi-KAbc_SOURCE_DIR}/src;${Akonadi-KAbc_BINARY_DIR}/src>")

target_link_libraries(KF5AkonadiKAbc
PUBLIC
    Qt5::Core
)

set_target_properties(KF5AkonadiKAbc PROPERTIES
    VERSION ${AKONADIKABC_VERSION_STRING}
    SOVERSION ${AKONADIKABC_SOVERSION}
    EXPORT_NAME AkonadiKAbc
)

install(TARGETS
    KF5AkonadiKAbc
    EXPORT KF5AkonadiKAbcTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS}
)

ecm_generate_headers(AkonadiKAbc_CamelCase_HEADERS
  HEADER_NAMES

  ContactParts
  REQUIRED_HEADERS AkonadiKAbc_HEADERS
  PREFIX Akonadi/KAbc
)

install(FILES
    ${AkonadiKAbc_CamelCase_HEADERS}
    DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Akonadi/KAbc
    COMPONENT Devel
)

install(FILES
    ${AkonadiKAbc_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/akonadi-kabc_export.h
    ${AkonadiKAbc_CamelCase_HEADERS}
    DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/akonadi/kabc
    COMPONENT Devel
)

ecm_generate_pri_file(BASE_NAME AkonadiKAbc LIB_NAME KF5AkonadiKAbc DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KF5_INCLUDE_INSTALL_DIR}/Akonadi/kabc)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

