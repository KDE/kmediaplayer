cmake_minimum_required(VERSION 2.8.12)

project(KMediaPlayer)


#
# CMake stuff from ECM
#
include(FeatureSummary)
find_package(ECM 5.27.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://projects.kde.org/projects/kdesupport/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)


include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMPackageConfigHelpers)

set(KF5_VERSION "5.28.0") # handled by release scripts
set(KF5_DEP_VERSION "5.27.0") # handled by release scripts

#
# Version info
#
ecm_setup_version(${KF5_VERSION}
   VARIABLE_PREFIX KMEDIAPLAYER
   VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kmediaplayer_version.h"
   PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5MediaPlayerConfigVersion.cmake"
   SOVERSION 5)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kmediaplayer_version.h
        DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}
        COMPONENT Devel)


#
# Dependencies
#
set(REQUIRED_QT_VERSION 5.5.0)
find_package(Qt5DBus ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)
find_package(Qt5Widgets ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

find_package(KF5Parts ${KF5_DEP_VERSION} REQUIRED)
find_package(KF5XmlGui ${KF5_DEP_VERSION} REQUIRED)


#
# Subdirectories
#
include_directories (
   ${CMAKE_CURRENT_SOURCE_DIR}/src
   ${CMAKE_CURRENT_BINARY_DIR}/src)

add_subdirectory(src)
add_subdirectory(autotests)


#
# Config.cmake stuff
#
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5MediaPlayer")
ecm_configure_package_config_file(
   "${CMAKE_CURRENT_SOURCE_DIR}/KF5MediaPlayerConfig.cmake.in"
   "${CMAKE_CURRENT_BINARY_DIR}/KF5MediaPlayerConfig.cmake"
   INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/KF5MediaPlayerConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/KF5MediaPlayerConfig.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT KF5MediaPlayerTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE KF5MediaPlayerTargets.cmake
        NAMESPACE KF5::)


#
# Feature summary
#
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
