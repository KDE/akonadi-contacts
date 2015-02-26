cmake_minimum_required(VERSION 2.8.12)

project(Akonadi-Contact)

# ECM setup
find_package(ECM 1.6.0 CONFIG REQUIRED)
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
set(KF5_VERSION "5.6.0")
set(KDEPIMLIBS_VERSION "4.82.0")
set(KCONTACTS_VERSION "4.80.0")
set(CALENDARCORE_VERSION "4.79.0")
set(KMIMELIB_VERSION "4.79.0")

ecm_setup_version(${KDEPIMLIBS_VERSION} VARIABLE_PREFIX AKONADICONTACT
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-contact_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiContactConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(KF5KDELibs4Support ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Completion ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Codecs ${KF5_VERSION} CONFIG REQUIRED)
find_package(Phonon4Qt5 CONFIG REQUIRED)



find_package(KF5Contacts ${KCONTACTS_VERSION} CONFIG REQUIRED)
find_package(KF5CalendarCore ${CALENDARCORE_VERSION} CONFIG REQUIRED)
find_package(KF5Mime ${KMIMELIB_VERSION} CONFIG REQUIRED)

if(${CMAKE_SOURCE_DIR} STREQUAL ${Akonadi-Contact_SOURCE_DIR})
  find_package(KF5Akonadi CONFIG REQUIRED)
  find_package(KF5AkonadiMime ${KDEPIMLIBS_VERSION} CONFIG REQUIRED)
else()
  # IMPORTED targets are scoped, so KF5::AkonadiPrivate found in ../akonadi
  # won't work here, and it is a PUBLIC dependency of KF5::Akonadi
  find_package(KF5AkonadiServer ${KF5AkonadiServer_MIN_VERSION} CONFIG REQUIRED)
endif()

########### Targets ###########

add_definitions(-DTRANSLATION_DOMAIN=\"akonadicontact5\")
add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")
add_subdirectory(src)
if (BUILD_TESTING)
  add_subdirectory(autotests)
  add_subdirectory(tests)
endif()
########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5AkonadiContact")

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
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
)
if (BUILD_TESTING)
   add_subdirectory(src/editor/autotests)
endif()
if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()

