# SPDX-FileCopyrightText: 2024 Paul Colby <git@colby.id.au>
# SPDX-License-Identifier: BSD-3-Clause

# Attempt to detect the QT_INSTALL_DOCS path via qtpaths, or qmake.
if(NOT QT_INSTALL_DOCS)
    if(QT_VERSION VERSION_GREATER_EQUAL 6.2.0 AND TARGET Qt${QT_VERSION_MAJOR}::qtpaths)
        message(DEBUG "Fetching location of imported Qt${QT_VERSION_MAJOR}::qtpaths command")
        get_target_property(_queryCommand Qt${QT_VERSION_MAJOR}::qtpaths LOCATION)
    elseif(TARGET Qt${QT_VERSION_MAJOR}::qmake)
        message(DEBUG "Fetching location of imported Qt${QT_VERSION_MAJOR}::qmake command")
        get_target_property(_queryCommand Qt${QT_VERSION_MAJOR}::qmake LOCATION)
    else()
        message(STATUS "Neither Qt${QT_VERSION_MAJOR}::qtpaths nor Qt${QT_VERSION_MAJOR}::qmake available")
    endif()

    if(_queryCommand)
        message(VERBOSE "Fetching QT_INSTALL_DOCS from ${_queryCommand}")
        execute_process(
            COMMAND "${_queryCommand}" -query QT_INSTALL_DOCS
            RESULT_VARIABLE _commandResult
            OUTPUT_VARIABLE _commandOutput
            ERROR_VARIABLE _commandError
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE
        )
        message(DEBUG "${_queryCommand} result: ${_commandResult}")
        message(DEBUG "${_queryCommand} output: ${_commandOutput}")
        message(DEBUG "${_queryCommand} error: ${_commandError}")

        if(_commandResult EQUAL 0)
            set(QT_INSTALL_DOCS "${_commandOutput}")
            message(STATUS "Found QT_INSTALL_DOCS: ${QT_INSTALL_DOCS}")
        else()
            message(STATUS "Failed to find QT_INSTALL_DOCS: ${_commandOutput} ${_commandError} [${_commandResult}]")
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
