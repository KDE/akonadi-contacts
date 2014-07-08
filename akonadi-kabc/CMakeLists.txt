cmake_minimum_required(VERSION 2.8.12)

project(Akonadi-KAbc)

# ECM setup
find_package(ECM 1.0.0 CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings)

set(KF5_VERSION "5.0.0")
set(KDEPIMLIBS_VERSION "4.70.0")

ecm_setup_version(${KDEPIMLIBS_VERSION} VARIABLE_PREFIX AKONADIKABC
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-kabc_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiKAbcConfigVersion.cmake"
                        SOVERSION 5
)

########### Targets ###########

add_subdirectory(src)

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5AkonadiKAbc")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5AkonadiKAbcConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiKAbcConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiKAbcConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiKAbcConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5AkonadiKAbcTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5AkonadiKAbcTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/akonadi-kabc_version.h
  DESTINATION ${KF5_INCLUDE_INSTALL_DIR} COMPONENT Devel
)


