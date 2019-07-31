cmake_minimum_required(VERSION 3.5)
set(PIM_VERSION "5.11.90")

project(Akonadi-Contact VERSION ${PIM_VERSION})

# ECM setup

set(KF5_MIN_VERSION "5.60.0")

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)

include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMQtDeclareLoggingCategory)


set(AKONADI_CONTACTS_VERSION ${PIM_VERSION})
set(KCONTACTS_VERSION "5.11.90")
set(KMIMELIB_VERSION "5.11.90")
set(AKONADI_VERSION "5.11.90")

set(QT_REQUIRED_VERSION "5.11.0")
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test)
########### Find packages ###########
find_package(KF5KIO ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Completion ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Codecs ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5IconThemes ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5DBusAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Service ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5TextWidgets ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5WidgetsAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Prison ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(KF5Contacts ${KCONTACTS_VERSION} CONFIG REQUIRED)
find_package(KF5Mime ${KMIMELIB_VERSION} CONFIG REQUIRED)
find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)


########### Targets ###########


add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
add_definitions(-DQT_NO_FOREACH)

add_subdirectory(src)
add_subdirectory(kcm)
add_subdirectory(serializers)

install( FILES akonadi-contacts.renamecategories akonadi-contacts.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR} )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
