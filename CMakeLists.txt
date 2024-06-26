cmake_minimum_required(VERSION 3.5)

project(ElementsCG VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/zone.cpp
        src/player.cpp
        src/card.cpp
        src/duel.cpp
        src/globals.cpp
        src/deck.cpp
        src/targetlist.cpp
        src/bot.cpp
        src/gamestate.cpp
        src/cards/cardbase.cpp
        src/cards/copperworm.cpp
        src/cards/silverwolf.cpp
        src/cards/dragonoidwarrior.cpp
        src/cards/whirlwind.cpp
        src/cards/dragonoidsage.cpp
        src/cards/tungstenfirefly.cpp
        src/cards/dragonoidscout.cpp
        src/cards/brassbeetle.cpp
        src/cards/tempestwyvern.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ElementsCG
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ElementsCG APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ElementsCG SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ElementsCG
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ElementsCG PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ElementsCG PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ElementsCG
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ElementsCG)
endif()
