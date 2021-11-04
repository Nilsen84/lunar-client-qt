cmake_minimum_required(VERSION 3.21)
project(lunar_client_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(lunar_client_qt src/main.cpp)
target_link_libraries(lunar_client_qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

