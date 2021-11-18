cmake_minimum_required(VERSION 3.16)
project(lunar-client-qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(lunar-client-qt src/main.cpp src/gui/mainwindow.cpp src/gui/mainwindow.h src/launch/launcher.cpp src/launch/launcher.h src/gui/pages/generalpage.cpp src/gui/pages/generalpage.h src/gui/pages/configurationpage.h src/gui/pages/configurationpage.cpp)
target_link_libraries(lunar-client-qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

target_include_directories(lunar-client-qt PRIVATE src)

