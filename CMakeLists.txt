# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "5.240.43")

project(Akonadi-Contact VERSION ${PIM_VERSION})

# ECM setup

set(KF_MIN_VERSION "5.240.0")

find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
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
set(KMIMELIB_VERSION "5.240.40")
set(AKONADI_VERSION "5.240.40")
set(GRANTLEETHEME_LIB_VERSION "5.240.40")
set(KTEXTADDONS_MIN_VERSION "1.5.2")

set(QT_REQUIRED_VERSION "6.5.0")
find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test)
########### Find packages ###########
find_package(KF6KIO ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6I18n ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6CoreAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Completion ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Config ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6IconThemes ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Service ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6TextWidgets ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6WidgetsAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6XmlGui ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Prison ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Codecs ${KF_MIN_VERSION} CONFIG REQUIRED)

find_package(KF6Contacts ${KF_MIN_VERSION} CONFIG REQUIRED)

find_package(KPim6Mime ${KMIMELIB_VERSION} CONFIG REQUIRED)
find_package(KPim6Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)

find_package(KPim6GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)

find_package(KF6TextTemplate CONFIG REQUIRED)

find_package(KF6TextUtils ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)

############### Compilers flags ###############

if (MSVC)
    # This sets the __cplusplus macro to a real value based on the version of C++ specified by
    # the /std switch. Without it MSVC keeps reporting C++98, so feature detection doesn't work.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()

########### Targets ###########


ecm_set_disabled_deprecation_versions(QT 6.5  KF 5.240.0)


if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif()
option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()

add_subdirectory(src)
add_subdirectory(serializers)

ecm_qt_install_logging_categories(
        EXPORT AKONADICONTACTS
        FILE akonadi-contacts.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
        )


kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
