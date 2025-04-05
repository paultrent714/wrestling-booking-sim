cmake_minimum_required(VERSION 3.16)

project(CMSC437Booking VERSION 0.1 LANGUAGES CXX)

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
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CMSC437Booking
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        randomUtilities.h
        match.h match.cpp
        show.h show.cpp
        championship.h championship.cpp
        team.h team.cpp

        gamedatamanager.h gamedatamanager.cpp


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CMSC437Booking APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CMSC437Booking SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CMSC437Booking
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CMSC437Booking PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Charts
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CMSC437Booking)
endif()
set_target_properties(CMSC437Booking PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CMSC437Booking
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# Define paths for fonts, database, data, and icons
set(FONTS_DIR ${CMAKE_BINARY_DIR}/fonts)
set(DB_DIR ${CMAKE_BINARY_DIR}/saveFiles)
set(DATA_DIR ${CMAKE_BINARY_DIR}/data)
set(ICONS_DIR ${CMAKE_BINARY_DIR}/icons)

# Ensure the directories exist (they will be created if they don't exist)
if(NOT EXISTS ${FONTS_DIR})
    file(MAKE_DIRECTORY ${FONTS_DIR})
endif()

if(NOT EXISTS ${DB_DIR})
    file(MAKE_DIRECTORY ${DB_DIR})
endif()

if(NOT EXISTS ${DATA_DIR})
    file(MAKE_DIRECTORY ${DATA_DIR})
endif()

if(NOT EXISTS ${ICONS_DIR})
    file(MAKE_DIRECTORY ${ICONS_DIR})
endif()

# Remove existing files and directories in the target folders
file(REMOVE_RECURSE ${FONTS_DIR}/*)
file(REMOVE_RECURSE ${DB_DIR}/*)
file(REMOVE_RECURSE ${DATA_DIR}/*)
file(REMOVE_RECURSE ${ICONS_DIR}/*)

# Copy entire directories (fonts, saveFiles, data, icons) to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/fonts/ DESTINATION ${FONTS_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/saveFiles/ DESTINATION ${DB_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${DATA_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/icons/ DESTINATION ${ICONS_DIR})

# Print messages for debugging purposes
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")


# Print messages for debugging purposes
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CMSC437Booking)
endif()
