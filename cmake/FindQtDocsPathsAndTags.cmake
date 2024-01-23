# Attempt to detect the QT_INSTALL_DOCS path via qtpaths, or qmake.
if(NOT QT_INSTALL_DOCS)
    if(QT_VERSION VERSION_GREATER_EQUAL 6.2.0 AND TARGET Qt${QT_VERSION_MAJOR}::qtpaths)
        message(DEBUG "Fetching location of imported Qt${QT_VERSION_MAJOR}::qtpaths command")
        get_target_property(COMMAND Qt${QT_VERSION_MAJOR}::qtpaths LOCATION)
    elseif(TARGET Qt${QT_VERSION_MAJOR}::qmake)
        message(DEBUG "Fetching location of imported Qt${QT_VERSION_MAJOR}::qmake command")
        get_target_property(COMMAND Qt${QT_VERSION_MAJOR}::qmake LOCATION)
    else()
        message(STATUS "Neither Qt${QT_VERSION_MAJOR}::qtpaths nor Qt${QT_VERSION_MAJOR}::qmake available")
    endif()

    if(COMMAND)
        message(VERBOSE "Fetching QT_INSTALL_DOCS from ${COMMAND}")
        execute_process(
            COMMAND "${COMMAND}" -query QT_INSTALL_DOCS
            RESULT_VARIABLE COMMAND_RESULT
            OUTPUT_VARIABLE COMMAND_OUTPUT
            ERROR_VARIABLE COMMNAD_ERROR
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE
        )
        message(DEBUG "${COMMAND} result: ${COMMAND_RESULT}")
        message(DEBUG "${COMMAND} output: ${COMMAND_OUTPUT}")
        message(DEBUG "${COMMAND} error: ${COMMAND_ERROR}")

        if(COMMAND_RESULT EQUAL 0)
            set(QT_INSTALL_DOCS "${COMMAND_OUTPUT}")
            message(STATUS "Found QT_INSTALL_DOCS: ${QT_INSTALL_DOCS}")
        else()
            message(STATUS "Failed to find QT_INSTALL_DOCS: ${COMMAND_OUTPUT} ${COMMAND_ERROR} [${COMMAND_RESULT}]")
        endif()
    endif()
endif()

# Include Qt doc tagfiles, if available.
if(QT_INSTALL_DOCS)
    set(QT_DOCS_BASEURL "https://doc.qt.io/qt-${QT_VERSION_MAJOR}/")
    message(STATUS "Using Qt doc tagfiles ${QT_INSTALL_DOCS} (${QT_DOCS_BASEURL})")
    set(DOX_TAGFILES "\\
        \"${QT_INSTALL_DOCS}/qtcore/qtcore.tags=${QT_DOCS_BASEURL}\""
    )
endif()
