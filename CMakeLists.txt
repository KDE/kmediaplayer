cmake_minimum_required(VERSION 3.16)

set(KF_VERSION "5.103.0") # handled by release scripts
set(KF_DEP_VERSION "5.103.0") # handled by release scripts
project(KMediaPlayer VERSION ${KF_VERSION})


#
# CMake stuff from ECM
#
include(FeatureSummary)
find_package(ECM 5.103.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://commits.kde.org/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)

include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMDeprecationSettings)
include(CMakePackageConfigHelpers)


#
# Version info
#
ecm_setup_version(PROJECT
   VARIABLE_PREFIX KMEDIAPLAYER
   VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kmediaplayer_version.h"
   PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5MediaPlayerConfigVersion.cmake"
   SOVERSION 5)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kmediaplayer_version.h
        DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KMediaPlayer
        COMPONENT Devel)


#
# Dependencies
#
set(REQUIRED_QT_VERSION 5.15.2)
find_package(Qt5DBus ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)
find_package(Qt5Widgets ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

find_package(KF5Parts ${KF_DEP_VERSION} REQUIRED)
find_package(KF5XmlGui ${KF_DEP_VERSION} REQUIRED)


#
# Subdirectories
#
ecm_set_disabled_deprecation_versions(
    QT 5.15.2
    KF 5.95
)

add_subdirectory(src)
if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()

#
# Config.cmake stuff
#
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5MediaPlayer")
configure_package_config_file(
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
