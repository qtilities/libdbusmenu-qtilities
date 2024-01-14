configure_file(dbusmenu_config.h.in  ${CMAKE_CURRENT_BINARY_DIR}/dbusmenu_config.h @ONLY)
configure_file(dbusmenu_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/dbusmenu_version.h)

set(DBUSMENU_SOURCES
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
    dbusmenushortcut_p.h
    dbusmenutypes_p.h
    debug_p.h
    utils_p.h
)
qt_add_dbus_adaptor(DBUSMENU_SOURCES
    com.canonical.dbusmenu.xml
    dbusmenuexporterdbus_p.h
    DBusMenuExporterDBus
)
add_library(${DBUSMENU_NAME} SHARED ${DBUSMENU_SOURCES})
add_library(qt::dbusmenu_qtilities ALIAS ${DBUSMENU_NAME})

set_target_properties(${DBUSMENU_NAME} PROPERTIES
    VERSION   ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
# Make sure linking to the target adds dbusmenu-qt install directory
target_include_directories(${DBUSMENU_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_libraries(${DBUSMENU_NAME} PRIVATE
    Qt::Widgets
    Qt::DBus
)
