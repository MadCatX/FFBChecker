cmake_minimum_required(VERSION 2.8.13)

project(FFBChecker)

find_package(Qt5Widgets)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux-specific definitions
    set(PLATFORM_LINUX 1)
    add_definitions("-std=c++11 -Wall -Wextra")
    add_definitions("-DFFBC_PLATFORM_LINUX")

    if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
        add_definitions("-ggdb -g3")
    endif()

    # Try to utilize SDL2 if it is available
    include(FindPkgConfig)
    pkg_search_module(SDL2 sdl2)
    if (SDL2_FOUND)
        add_definitions("-DFFBC_HAVE_SDL2")
    endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(PLATFORM_WIN32 1)
    add_definitions("-DFFBC_PLATFORM_WIN32 -DFFBC_HAVE_SDL2")

    # Enforce SDL2 on Windows
    set(SDL2_FOUND 1)
    # Adjust these paths accordingly to your setup
    set(QT_LIBS_PATH "C://Qt-Static//bin_noicu")
    set(SDL2_INCLUDE_DIRS "C://Users//Sacrilegium//Hacking//SDL2-2.0.3//include")
    set(SDL2_LIBRARIES ${SDL2_LIBRARIES} "C://Users//Sacrilegium//Hacking//SDL2-2.0.3//lib//x86//SDL2.lib")
    # set(SDL2_LIBRARIES ${SDL2_LIBRARIES} "C://Users//Sacrilegium//Hacking//SDL2-2.0.3//lib//x86//SDL2main.lib")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(FFBChecker_SRCS
    conditioneffectsettings.cpp
    constanteffectsettings.cpp
    effectsettings.cpp
    envelopesettings.cpp    
    ffbconditioneffectparameters.cpp    
    ffbconstanteffectparameters.cpp
    ffbdevice.cpp
    ffbeffect.cpp    
    ffbeffectparameters.cpp
    ffbenvelopeparameters.cpp
    ffbnulleffect.cpp    
    ffbperiodiceffectparameters.cpp   
    ffbrampeffectparameters.cpp
    ffbrumbleeffectparameters.cpp
    globalsettings.cpp
    main.cpp
    mainwindow.cpp
    periodiceffectsettings.cpp
    rampeffectsettings.cpp
    rumbleeffectsettings.cpp)

if (PLATFORM_LINUX)
    set(FFBChecker_SRCS
        ${FFBChecker_SRCS}
        linuxdeviceprober.cpp
        linuxffbdevice.cpp
        linuxffbrumbleeffect.cpp
        linuxffbrampeffect.cpp
        linuxffbperiodiceffect.cpp
        linuxffbeffect.cpp
        linuxffbeffectfactory.cpp
        linuxffbconstanteffect.cpp
        linuxffbconditioneffect.cpp)
endif()

if (SDL2_FOUND)
    set(FFBChecker_SRCS
        ${FFBChecker_SRCS}
        sdl2ffbeffectfactory.cpp
        sdl2ffbdevice.cpp
        sdl2ffbeffect.cpp
        sdl2ffbconstanteffect.cpp
        sdl2ffbconditioneffect.cpp
        sdl2ffbperiodiceffect.cpp
        sdl2ffbrampeffect.cpp
        sdl2deviceprober.cpp)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

if (PLATFORM_WIN32)
    include_directories("${QT_LIBS_PATH}//include")
endif()

add_executable(FFBChecker ${FFBChecker_SRCS})

if (PLATFORM_LINUX)
    target_link_libraries(FFBChecker Qt5::Widgets)
elseif (PLATFORM_WIN32)
    target_link_libraries(FFBChecker "Ws2_32.lib")
    target_link_libraries(FFBChecker "imm32.lib")
    target_link_libraries(FFBChecker "winmm.lib")
    target_link_libraries(FFBChecker "${QT_LIBS_PATH}//plugins//platforms//qwindows.lib")
    target_link_libraries(FFBChecker "${QT_LIBS_PATH}//lib//qtpcre.lib")
    target_link_libraries(FFBChecker "${QT_LIBS_PATH}//lib//qtharfbuzzng.lib")
    target_link_libraries(FFBChecker "${QT_LIBS_PATH}//lib//qtfreetype.lib")
    target_link_libraries(FFBChecker "${QT_LIBS_PATH}//lib//Qt5Core.lib")
    target_link_libraries(FFBChecker "${QT_LIBS_PATH}//lib//Qt5PlatformSupport.lib")
    target_link_libraries(FFBChecker "${QT_LIBS_PATH}//lib//Qt5Gui.lib")
    target_link_libraries(FFBChecker "${QT_LIBS_PATH}//lib//Qt5Widgets.lib")
endif()

if (SDL2_FOUND)
    target_link_libraries(FFBChecker ${SDL2_LIBRARIES})
endif()

