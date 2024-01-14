cmake_minimum_required(VERSION 3.18)
project(dbusmenu-qtilities
    VERSION 0.9.3
    LANGUAGES CXX
)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(DBUSMENU_WITH_DOC              "Build Doxygen documentation [default: ON]" ON)
set(PROJECT_QT_VERSION 5 CACHE STRING "Qt version to use           [default: 5]")

set(DBUSMENU_NAME ${PROJECT_NAME}-qt${PROJECT_QT_VERSION})
configure_file(scripts/${PROJECT_NAME}.pc.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
#=======================================================================================================
# Qt
#=======================================================================================================
set(CMAKE_AUTOMOC ON)
find_package(QT NAMES Qt${PROJECT_QT_VERSION})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS DBus Widgets)
#=======================================================================================================
# Source files
#=======================================================================================================
add_subdirectory(src)
#add_subdirectory(tests)
#add_subdirectory(tools)
#=======================================================================================================
# Documentation
#=======================================================================================================
include(GNUInstallDirs)
if(DBUSMENU_WITH_DOC)
    configure_file(scripts/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ALL doxygen WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    install(DIRECTORY ${CMAKE_BINARY_DIR}/html/
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/qt${PROJECT_QT_VERSION}
    )
endif()
#=======================================================================================================
# CMake Config files
#=======================================================================================================
include(CMakePackageConfigHelpers)

set(DBUSMENU_QTILITIES_CMAKE_PATH "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}")
configure_package_config_file("cmake/DBusMenuQtilitiesConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/DBusMenuQtilitiesConfig.cmake"
    PATH_VARS DBUSMENU_QTILITIES_CMAKE_PATH
    INSTALL_DESTINATION "${DBUSMENU_QTILITIES_CMAKE_PATH}"
)
write_basic_package_version_file("DBusMenuQtilitiesConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)
#=======================================================================================================
# Installation
#=======================================================================================================
install(
    FILES       "${CMAKE_BINARY_DIR}/${DBUSMENU_NAME}.pc"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/pkgconfig"
)
install(
    FILES
        "${CMAKE_BINARY_DIR}/DBusMenuQtilitiesConfig.cmake"
        "${CMAKE_BINARY_DIR}/DBusMenuQtilitiesConfigVersion.cmake"
    DESTINATION
        "${DBUSMENU_QTILITIES_CMAKE_PATH}"
    COMPONENT
        Devel
)
install(
    TARGETS             ${DBUSMENU_NAME}
    EXPORT              ${DBUSMENU_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
    EXPORT      ${DBUSMENU_NAME}-targets
    DESTINATION ${DBUSMENU_QTILITIES_CMAKE_PATH}
)
install(
    DIRECTORY              .
    DESTINATION            ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
    PATTERN                "*_p.h" EXCLUDE
)
#install(
#    FILES       ${CMAKE_CURRENT_BINARY_DIR}/dbusmenu_version.h
#    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#)
