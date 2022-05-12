# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "5.20.2")

project(Akonadi-Contact VERSION ${PIM_VERSION})

# ECM setup

set(KF5_MIN_VERSION "5.91.0")

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)

include(ECMSetupVersion)
include(FeatureSummary)
include(KDEGitCommitHooks)
include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

include(ECMInstallIcons)
include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)
include(ECMAddQch)


option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")


set(AKONADI_CONTACTS_VERSION ${PIM_VERSION})
set(KMIMELIB_VERSION "5.20.1")
set(AKONADI_VERSION "5.20.1")
set(GRANTLEETHEME_LIB_VERSION "5.20.1")
set(GRANTLEE_LIB_VERSION "5.2")

set(QT_REQUIRED_VERSION "5.15.2")
find_package(Qt${QT_MAJOR_VERSION} ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test)
########### Find packages ###########
find_package(KF5KIO ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5CoreAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Completion ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5IconThemes ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Service ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5TextWidgets ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5WidgetsAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Prison ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5KCMUtils ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(KF5Contacts ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(KF5Mime ${KMIMELIB_VERSION} CONFIG REQUIRED)
find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)

find_package(KF5GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)

if (QT_MAJOR_VERSION STREQUAL "5")
    find_package(Grantlee5 ${GRANTLEE_VERSION} CONFIG REQUIRED)
    set(MAIN_LIB Grantlee5::Templates)
else()
    find_package(KF6TextTemplate ${KF5_MIN_VERSION} CONFIG REQUIRED)
    set(MAIN_LIB KF6TextTemplate::Templates)
endif()

############### Compilers flags ###############

if (MSVC)
    # This sets the __cplusplus macro to a real value based on the version of C++ specified by
    # the /std switch. Without it MSVC keeps reporting C++98, so feature detection doesn't work.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()

########### Targets ###########


ecm_set_disabled_deprecation_versions(QT 5.14.0 KF 5.92.0)


if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif()
option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()

add_subdirectory(src)
add_subdirectory(kcm)
add_subdirectory(serializers)

ecm_qt_install_logging_categories(
        EXPORT AKONADICONTACTS
        FILE akonadi-contacts.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
        )


kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
