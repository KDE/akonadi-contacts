cmake_minimum_required(VERSION 2.8.12)

project(Akonadi-Contact)

# ECM setup
find_package(ECM 0.0.15 CONFIG REQUIRED)
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
include(ECMInstallIcons)
set(KF5_VERSION "5.0.0")

ecm_setup_version(${KF5_VERSION} VARIABLE_PREFIX AKONADICONTACT
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(KF5KDELibs4Support ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Completion ${KF5_VERSION} CONFIG REQUIRED)
find_package(Phonon4Qt5 CONFIG REQUIRED)

if(${CMAKE_SOURCE_DIR} STREQUAL "${Akonadi-Contact_SOURCE_DIR}")
  set(AkonadiServer_MIN_VERSION "1.72.43")
  find_package(Akonadi ${AkonadiServer_MIN_VERSION} CONFIG REQUIRED)
  find_package(KF5Abc ${KF5_VERSION} CONFIG REQUIRED)
  find_package(KF5Akonadi CONFIG REQUIRED)
  find_package(KF5AkonadiMime CONFIG REQUIRED)
  find_package(KF5CalendarCore ${KF5_VERSION} CONFIG REQUIRED)
  find_package(KF5Mime ${KF5_VERSION} CONFIG REQUIRED)
  find_package(KF5PimUtils ${KF5_VERSION} CONFIG REQUIRED)
endif()

########### Targets ###########

add_definitions(-DTRANSLATION_DOMAIN=\"akonadicontact5\")

add_subdirectory(src)
add_subdirectory(autotests)

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5AkonadiContact")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5AkonadiContactConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5AkonadiContactTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5AkonadiContactTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_version.h
  DESTINATION ${KF5_INCLUDE_INSTALL_DIR} COMPONENT Devel
)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()

