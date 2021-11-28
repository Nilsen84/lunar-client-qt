cmake_minimum_required(VERSION 3.16)
project(lunar-client-qt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Svg
        Network
        REQUIRED)

set(SOURCE_FILES
        src/main.cpp
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/launch/offlinelauncher.cpp
        src/launch/offlinelauncher.h
        src/gui/pages/generalpage.cpp
        src/gui/pages/generalpage.h
        src/gui/pages/configurationpage.h
        src/gui/pages/configurationpage.cpp src/gui/pages/agentspage.cpp src/gui/pages/agentspage.h src/launch/launcher.h src/launch/launcher.cpp)

add_executable(lunar-client-qt ${SOURCE_FILES} ${LIB_SRC} res.qrc)
target_link_libraries(lunar-client-qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
        Qt::Network
        )

target_include_directories(lunar-client-qt PRIVATE src)

#This line removes the console window when building on windows
set_property(TARGET lunar-client-qt PROPERTY WIN32_EXECUTABLE true)

