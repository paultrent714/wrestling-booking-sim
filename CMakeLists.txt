cmake_minimum_required(VERSION 3.16)

project(ToasterWrestling VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SQL Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SQL Charts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    wrestler.h
    wrestler.cpp
    randomUtilities.h
    match.h match.cpp
    show.h show.cpp
    championship.h championship.cpp
    team.h team.cpp
    gamedatamanager.h gamedatamanager.cpp
    rivalry.h rivalry.cpp
    resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ToasterWrestling
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ToasterWrestling SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ToasterWrestling
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ToasterWrestling PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Charts
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ToasterWrestling)
endif()

set_target_properties(ToasterWrestling PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ToasterWrestling
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Only copy saveFiles if they are writable (like game_data.db)
set(DB_DIR ${CMAKE_BINARY_DIR}/saveFiles)

if(NOT EXISTS ${DB_DIR})
    file(MAKE_DIRECTORY ${DB_DIR})
endif()

file(REMOVE_RECURSE ${DB_DIR}/*)
file(COPY ${CMAKE_SOURCE_DIR}/saveFiles/ DESTINATION ${DB_DIR})

# Debug info
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ToasterWrestling)
endif()
