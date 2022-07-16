cmake_minimum_required(VERSION 3.21)
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

# ---------------------------- Get current version and tag --------------------------------

set(LCQT_VERSION Unknown)
set(LCQT_VERSION_TAG Unknown)

find_package(Git)
if(Git_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --match "v[0-9]*"
            OUTPUT_VARIABLE tag
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    if(tag MATCHES "^v([0-9]+)\\.([0-9]+)\\.([0-9]+)")
        set(LCQT_VERSION ${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3})
        set(LCQT_VERSION_TAG v${LCQT_VERSION})

        message(STATUS "Found version tag: ${LCQT_VERSION_TAG}")
    else()
        message(WARNING "Couldn't find latest version tag, disabling update checker.")
        set(INCLUDE_UPDATER Off)
    endif()
else()
    message(WARNING "Couldn't find git, disabling update checker.")
    set(INCLUDE_UPDATER Off)
endif()

# ----------------------- Parse json config file -----------------------------

file(READ ${CMAKE_CURRENT_LIST_DIR}/config.json CONFIG)

macro(CONFIG_VAR KEY OUTPUT_VAR)
    string(JSON ${OUTPUT_VAR} GET ${CONFIG} ${KEY})
endmacro()

config_var("agentsDestDir" AGENTS_DEST_DIR)
config_var("libsDestDir" LIBS_DEST_DIR)
config_var("githubReleaseApiLink" GITHUB_RELEASE_LINK)

# ----------------------- Replace values in cpp file -----------------------------

configure_file(${CMAKE_SOURCE_DIR}/buildconfig.cpp.in ${CMAKE_BINARY_DIR}/buildconfig.cpp @ONLY)
set(VERSION_FILE ${CMAKE_BINARY_DIR}/buildconfig.cpp)

set_source_files_properties(${VERSION_FILE} PROPERTIES COMPILE_DEFINITIONS "QSL=QStringLiteral")

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
        src/buildconfig.h
        src/gui/agents/agentsmodel.cpp
        src/gui/agents/agentsmodel.h
        src/gui/agents/agentsview.cpp
        src/gui/agents/agentsview.h
        src/gui/style/removeoutline.cpp
        src/gui/style/removeoutline.h
        src/util/fs.cpp src/util/fs.h
        src/util/utils.cpp
        src/util/utils.h
        src/util/sysinfo.cpp
        src/util/sysinfo.h
)

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

macro(COPY_JARS S_DIR T_DIR NEW_DIR)
    add_custom_command(
            OUTPUT "${JAR_DEST_DIR}/${T_DIR}"
            COMMAND ${CMAKE_COMMAND}
            -Dsrc_dir=${CMAKE_CURRENT_LIST_DIR}/java/${S_DIR}
            -Ddst_dir=${JAR_DEST_DIR}/${T_DIR}
            -P ${CMAKE_CURRENT_LIST_DIR}/cmake/copy_jars.cmake
            COMMENT "Copying '${S_DIR}' to '${T_DIR}'"
            VERBATIM
    )
    set(${NEW_DIR} "${JAR_DEST_DIR}/${T_DIR}")
endmacro()

copy_jars(agents ${AGENTS_DEST_DIR} COPIED_AGENTS)
copy_jars(libs ${LIBS_DEST_DIR} COPIED_LIBRARIES)

add_custom_target(CopyJars ALL DEPENDS ${COPIED_AGENTS} ${COPIED_LIBRARIES})
add_dependencies(lunar-client-qt CopyJars)

# ----------------------- Link against libraries ------------------------------

list(TRANSFORM QT_COMPONENTS PREPEND ${QT_VER}:: OUTPUT_VARIABLE QT_LIBS)

target_link_libraries(lunar-client-qt ${QT_LIBS})

# ---------------------- Set include directory ---------------------------

target_include_directories(lunar-client-qt PRIVATE src)