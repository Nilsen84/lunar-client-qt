cmake_minimum_required(VERSION 3.16)
project(lunar-client-qt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(USE_QT6 "Use Qt 6 instead of Qt 5" OFF)

if(USE_QT6)
    set(QT_VER 6)
else()
    set(QT_VER 5)
endif()

set(QT_COMPONENTS Core Gui Widgets Svg)

find_package(Qt${QT_VER} COMPONENTS ${QT_COMPONENTS} REQUIRED)

set(SOURCE_FILES
        src/main.cpp
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/launch/offlinelauncher.cpp
        src/launch/offlinelauncher.h
        src/gui/pages/generalpage.cpp
        src/gui/pages/generalpage.h
        src/gui/pages/configurationpage.h
        src/gui/pages/configurationpage.cpp
        src/gui/pages/agentspage.cpp
        src/gui/pages/agentspage.h
        src/launch/launcher.h
        src/launch/launcher.cpp
        src/config/config.cpp
        src/config/config.h
        src/gui/pages/minecraftpage.cpp
        src/gui/pages/minecraftpage.h
        src/gui/widgets/filechooser.cpp
        src/gui/widgets/filechooser.h
        src/gui/widgets/widgetutils.cpp
        src/gui/widgets/widgetutils.h)

add_executable(lunar-client-qt WIN32 MACOSX_BUNDLE ${SOURCE_FILES} ${LIB_SRC} res.qrc)

set(QT_LIBS ${QT_COMPONENTS})
list(TRANSFORM QT_LIBS PREPEND Qt${QT_VER}::)

target_link_libraries(lunar-client-qt ${QT_LIBS})

target_include_directories(lunar-client-qt PRIVATE src)