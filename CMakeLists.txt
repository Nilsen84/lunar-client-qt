cmake_minimum_required(VERSION 3.16)
project(lunar-client-qt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Svg
        Network)
if (NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS
            Core
            Gui
            Widgets
            Svg
            Network
            REQUIRED
            )
endif()

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
        src/gui/pages/helperspage.cpp
        src/gui/pages/helperspage.h
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

if (STATICCOMPILE)
        target_link_libraries(lunar-client-qt "-static")
endif()
add_executable(lunar-client-qt ${SOURCE_FILES} ${LIB_SRC} res.qrc)
target_link_libraries(lunar-client-qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
        Qt::Network
        )

target_include_directories(lunar-client-qt PRIVATE src)

# Removes the console window on windows and macos respectively
set_property(TARGET lunar-client-qt PROPERTY WIN32_EXECUTABLE true)
set_property(TARGET lunar-client-qt PROPERTY MACOSX_BUNDLE true)
