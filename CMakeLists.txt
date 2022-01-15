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

add_executable(lunar-client-qt ${SOURCE_FILES} ${LIB_SRC} res.qrc)
target_link_libraries(lunar-client-qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
        Qt::Network
        )
        
if (STATICCOMPILE)
        find_package(Freetype REQUIRED)
        find_package(PNG REQUIRED)
        find_package(JPEG REQUIRED)
        #find_package(Harfbuzz REQUIRED)
        #include(FindPCRE2.cmake)
	
if (DEFINED PCRE2_ROOT AND NOT PCRE2_ROOT)
	set (PCRE2_LIBRARY "" CACHE INTERNAL "")
	set (PCRE2_INCLUDE_DIR "" CACHE INTERNAL "")
	return ()
endif (DEFINED PCRE2_ROOT AND NOT PCRE2_ROOT)

if (UNIX AND NOT PCRE2_FOUND)
	find_program (PCRE2_CONFIG pcre2-config
		HINTS
		${PCRE2_DIR}
		${PCRE2_ROOT}
		$ENV{PCRE2_DIR}
		$ENV{PCRE2_ROOT}
		PATH_SUFFIXES bin
		PATHS
		/sw # Fink
		/opt/local # DarwinPorts
		/opt/csw # Blastwave
		/opt
		/usr/local
                /usr/x86_64-w64-mingw32
	)

	if (PCRE2_CONFIG)
		execute_process (COMMAND ${PCRE2_CONFIG} --cflags
			ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
			OUTPUT_VARIABLE PCRE2_CONFIG_CFLAGS)
		if (PCRE2_CONFIG_CFLAGS)
			string (REGEX MATCHALL "-I[^ ]+" _pcre2_dashI ${PCRE2_CONFIG_CFLAGS})
			string (REGEX REPLACE "-I" "" _pcre2_includepath "${_pcre2_dashI}")
			string (REGEX REPLACE "-I[^ ]+" "" _pcre2_cflags_other ${PCRE2_CONFIG_CFLAGS})
		endif (PCRE2_CONFIG_CFLAGS)
		execute_process (COMMAND ${PCRE2_CONFIG} --libs8
			ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
			OUTPUT_VARIABLE PCRE2_CONFIG_LIBS)
		if (PCRE2_CONFIG_LIBS)
			string (REGEX MATCHALL "-l[^ ]+" _pcre2_dashl ${PCRE2_CONFIG_LIBS})
			string (REGEX REPLACE "-l" "" _pcre2_lib "${_pcre2_dashl}")
			string (REGEX MATCHALL "-L[^ ]+" _pcre2_dashL ${PCRE2_CONFIG_LIBS})
			string (REGEX REPLACE "-L" "" _pcre2_libpath "${_pcre2_dashL}")
		endif (PCRE2_CONFIG_LIBS)
	endif (PCRE2_CONFIG)
endif (UNIX AND NOT PCRE2_FOUND)

find_path (PCRE2_INCLUDE_DIR pcre2.h
	HINTS
	${_pcre2_includepath}
	${PCRE2_DIR}
	${PCRE2_ROOT}
	$ENV{PCRE2_DIR}
	$ENV{PCRE2_ROOT}
	PATH_SUFFIXES
	include/pcre2
	include/PCRE2
	include
	PATHS
	~/Library/Frameworks/pcre2.framework/Headers
	/Library/Frameworks/pcre2.framework/Headers
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
	/usr/local
        /usr/x86_64-w64-mingw32
)

find_library (PCRE2_LIBRARY
	NAMES ${_pcre2_lib} pcre2-8 PCRE2
	HINTS
	${PCRE2_DIR}
	${PCRE2_ROOT}
	$ENV{PCRE2_DIR}
	$ENV{PCRE2_ROOT}
	${_pcre2_libpath}
	PATH_SUFFIXES lib
	PATHS
	~/Library/Frameworks/pcre2.framework
	/Library/Frameworks/pcre2.framework
	/sw
	/opt/local
	/opt/csw
	/opt
	/usr/local
        /usr/x86_64-w64-mingw32
)
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (PCRE2 DEFAULT_MSG PCRE2_LIBRARY PCRE2_INCLUDE_DIR)
set (PCRE2_LIBRARIES ${PCRE2_LIBRARY})
set (PCRE2_INCLUDE_DIRS ${PCRE2_INCLUDE_DIR})
## FindGRAPHITE2.cmake
##
## Copyright (C) 2016 Christian Schenk
## 
## This file is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published
## by the Free Software Foundation; either version 2, or (at your
## option) any later version.
## 
## This file is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this file; if not, write to the Free Software
## Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
## USA.

find_path(GRAPHITE2_INCLUDE_DIR
  NAMES
    graphite2/Font.h
)

find_library(GRAPHITE2_LIBRARY
  NAMES
    graphite2
)

find_package_handle_standard_args(GRAPHITE2 DEFAULT_MSG GRAPHITE2_LIBRARY GRAPHITE2_INCLUDE_DIR)

if(GRAPHITE2_FOUND)
  set(GRAPHITE2_INCLUDE_DIRS ${GRAPHITE2_INCLUDE_DIR})
  set(GRAPHITE2_LIBRARIES ${GRAPHITE2_LIBRARY})
else()
  set(GRAPHITE2_INCLUDE_DIRS)
  set(GRAPHITE2_LIBRARIES)
endif()

mark_as_advanced(GRAPHITE2_LIBRARY GRAPHITE2_INCLUDE_DIR)
	
        target_link_libraries(lunar-client-qt ${FREETYPE_LIBRARIES} ${PNG_LIBRARIES} ${JPEG_LIBRARIES} ${PCRE2_LIBRARIES} ${GRAPHITE2_LIBRARIES} ${HARFBUZZ_LIBRARIES}  "-static" "-lstdc++")
        target_include_directories(lunar-client-qt PRIVATE ${FREETYPE_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS} ${JPEG_INCLUDE_DIRS} ${PCRE2_INCLUDE_DIRS} ${GRAPHITE2_INCLUDE_DIRS} ${HARFBUZZ_INCLUDE_DIRS} )
        
endif()

target_include_directories(lunar-client-qt PRIVATE src)

# Removes the console window on windows and macos respectively
set_property(TARGET lunar-client-qt PROPERTY WIN32_EXECUTABLE true)
set_property(TARGET lunar-client-qt PROPERTY MACOSX_BUNDLE true)
