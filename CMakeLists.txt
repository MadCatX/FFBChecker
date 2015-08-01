cmake_minimum_required(VERSION 2.8.13)

project(FFBChecker)

add_definitions("-std=c++11 -Wall -Wextra")

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
  add_definitions("-ggdb -g3")
endif()

find_package(Qt5Widgets)

include(FindPkgConfig)
pkg_search_module(SDL2 sdl2)
if (SDL2_FOUND)
    add_definitions("-DFFBC_HAVE_SDL2")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(FFBChecker_SRCS
    conditioneffectsettings.cpp
    constanteffectsettings.cpp
    effectsettings.cpp
    envelopesettings.cpp
    linuxffbconditioneffect.cpp
    ffbconditioneffectparameters.cpp
    linuxffbconstanteffect.cpp
    ffbconstanteffectparameters.cpp
    ffbdevice.cpp
    ffbeffect.cpp
    linuxffbeffect.cpp
    linuxffbeffectfactory.cpp
    ffbeffectparameters.cpp
    ffbenvelopeparameters.cpp
    ffbnulleffect.cpp
    linuxffbperiodiceffect.cpp
    ffbperiodiceffectparameters.cpp
    linuxffbrampeffect.cpp
    ffbrampeffectparameters.cpp
    linuxffbrumbleeffect.cpp
    ffbrumbleeffectparameters.cpp
    globalsettings.cpp
    linuxdeviceprober.cpp
    linuxffbdevice.cpp
    main.cpp
    mainwindow.cpp
    periodiceffectsettings.cpp
    rampeffectsettings.cpp
    rumbleeffectsettings.cpp)

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

add_executable(FFBChecker ${FFBChecker_SRCS})
target_link_libraries(FFBChecker Qt5::Widgets)

if (SDL2_FOUND)
    target_link_libraries(FFBChecker ${SDL2_LIBRARIES})
endif()
