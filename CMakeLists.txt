cmake_minimum_required(VERSION 3.16)
project(lunar-client-qt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ----------------------- Options -------------------------

option(USE_QT6 "Use Qt 6 instead of Qt 5" OFF)
option(INCLUDE_UPDATER "Include update checker" ON)

if(USE_QT6)
    set(QT_VER Qt6)
else()
    set(QT_VER Qt5)
endif()

# ----------------------- Sources ------------------------

set(SOURCE_FILES
        src/main.cpp
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/launch/offlinelauncher.cpp
        src/launch/offlinelauncher.h
        src/gui/pages/generalpage.cpp
        src/gui/pages/generalpage.h
        src/gui/pages/configurationpage.h
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
        src/gui/widgets/widgetutils.h
        src/utils.cpp src/utils.h
        src/version.h
        src/gui/agents/agentsmodel.cpp
        src/gui/agents/agentsmodel.h)

set(UPDATER_SOURCES src/updater/updatechecker.cpp src/updater/updatechecker.h)

if(INCLUDE_UPDATER)
    list(APPEND SOURCE_FILES ${UPDATER_SOURCES})
endif()

# ------------------------- Dependencies --------------------------

set(QT_COMPONENTS Core Gui Widgets Svg)

if(INCLUDE_UPDATER)
    list(APPEND QT_COMPONENTS Network)
endif()

find_package(${QT_VER} COMPONENTS ${QT_COMPONENTS} REQUIRED)

# ---------------------------- Get current version and tag --------------------------------

set(LCQT_VERSION Unknown)
set(LCQT_VERSION_TAG Unknown)
find_package(Git)
if(Git_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --match "v[0-9]*"
            OUTPUT_VARIABLE tag
    )

    if(tag MATCHES "^v([0-9]+)\\.([0-9]+)\\.([0-9]+)")
        set(LCQT_VERSION ${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3})
        set(LCQT_VERSION_TAG v${LCQT_VERSION})
    endif()
endif()

configure_file(${CMAKE_SOURCE_DIR}/version.cpp.in ${CMAKE_BINARY_DIR}/version.cpp @ONLY)
set(VERSION_FILE ${CMAKE_BINARY_DIR}/version.cpp)

# ----------------------------- Executable --------------------------------------

add_executable(lunar-client-qt WIN32 MACOSX_BUNDLE ${SOURCE_FILES} ${VERSION_FILE} res.qrc)

# ----------------------------- Compile Definitions --------------------------------

if(INCLUDE_UPDATER)
    target_compile_definitions(lunar-client-qt PRIVATE INCLUDE_UPDATER)
endif()

# ------------------------- Copy java agents and libraries -----------------------

if(UNIX AND APPLE)
    set(JAR_DEST_DIR ${CMAKE_BINARY_DIR}/lunar-client-qt.app/Contents/MacOS)
else()
    set(JAR_DEST_DIR ${CMAKE_BINARY_DIR})
endif()

function(COPY_JARS DIR OUTPUT_LIST)
    add_custom_command(
            OUTPUT "${JAR_DEST_DIR}/${DIR}/"
            COMMAND ${CMAKE_COMMAND} -E make_directory ${JAR_DEST_DIR}/${DIR}/
    )

    set(COPIED_FILES "${JAR_DEST_DIR}/${DIR}/")

    file(GLOB JARS ${CMAKE_SOURCE_DIR}/java/${DIR}/*.jar)

    foreach(JAR ${JARS})
        get_filename_component(FILE_NAME ${JAR} NAME)
        add_custom_command(
                OUTPUT "${JAR_DEST_DIR}/${DIR}/${FILE_NAME}"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${JAR} ${JAR_DEST_DIR}/${DIR}/
                DEPENDS ${JAR}
                COMMENT "Copying ${FILE_NAME}"
        )
        list(APPEND COPIED_FILES ${JAR_DEST_DIR}/${DIR}/${FILE_NAME})
    endforeach()

    set(${OUTPUT_LIST} ${COPIED_FILES} PARENT_SCOPE)
endfunction()

copy_jars(agents COPIED_AGENTS)
copy_jars(libs COPIED_LIBRARIES)

add_custom_target(CopyJars ALL COMMAND DEPENDS ${COPIED_AGENTS} ${COPIED_LIBRARIES})
add_dependencies(lunar-client-qt CopyJars)

# ----------------------- Link against libraries ------------------------------

list(TRANSFORM QT_COMPONENTS PREPEND ${QT_VER}:: OUTPUT_VARIABLE QT_LIBS)

target_link_libraries(lunar-client-qt ${QT_LIBS})

# ---------------------- Set include directory ---------------------------

target_include_directories(lunar-client-qt PRIVATE src)