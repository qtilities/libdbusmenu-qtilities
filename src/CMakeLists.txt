configure_file(dbusmenu_export.h.in  ${CMAKE_CURRENT_BINARY_DIR}/dbusmenu_export.h  @ONLY)
configure_file(dbusmenu_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/dbusmenu_version.h @ONLY)

set(PROJECT_SOURCES
    dbusmenu_p.cpp
    dbusmenuexporter.cpp
    dbusmenuexporterdbus_p.cpp
    dbusmenuimporter.cpp
    dbusmenushortcut_p.cpp
    dbusmenutypes_p.cpp
    utils.cpp
    dbusmenu_p.h
    dbusmenuexporter.h
    dbusmenuexporterdbus_p.h
    dbusmenuexporterprivate_p.h
    dbusmenuimporter.h
    dbusmenushortcut_p.h
    dbusmenutypes_p.h
    debug_p.h
    utils_p.h
)
qt_add_dbus_adaptor(PROJECT_SOURCES
    com.canonical.dbusmenu.xml
    dbusmenuexporterdbus_p.h
    DBusMenuExporterDBus
)
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
source_group("" FILES ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION   ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
# Make sure linking to the target adds dbusmenu-qtilities install directory
target_include_directories(${PROJECT_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Widgets
    Qt::DBus
)
install(
    DIRECTORY              .
    DESTINATION            "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
    FILES_MATCHING PATTERN "*.h"
    PATTERN                "*_p.h" EXCLUDE
)
