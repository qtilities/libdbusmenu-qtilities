configure_file(dbusmenu_export.h.in  ${CMAKE_CURRENT_BINARY_DIR}/dbusmenu_export.h  @ONLY)
configure_file(dbusmenu_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/dbusmenu_version.h @ONLY)

set(PROJECT_SOURCES
    com.canonical.dbusmenu.xml
    dbusmenuexporter.h
    dbusmenuexporter.cpp
    dbusmenuimporter.h
    dbusmenuimporter.cpp
    utils.cpp
    debug_p.h
    dbusmenu_p.h
    dbusmenu_p.cpp
    dbusmenuexporterdbus_p.h
    dbusmenuexporterdbus_p.cpp
    dbusmenuexporterprivate_p.h
    dbusmenushortcut_p.h
    dbusmenushortcut_p.cpp
    dbusmenutypes_p.h
    dbusmenutypes_p.cpp
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
