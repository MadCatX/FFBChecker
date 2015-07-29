cmake_minimum_required(VERSION 2.8.13)

project(FFBChecker)

add_definitions("-std=c++11 -Wall -Wextra")

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
  add_definitions("-ggdb -g3")
endif()

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(FFBChecker_SRCS
    conditioneffectsettings.cpp
    constanteffectsettings.cpp
    deviceprober.cpp
    effectsettings.cpp
    envelopesettings.cpp
    ffbconditioneffect.cpp
    ffbconditioneffectparameters.cpp
    ffbconstanteffect.cpp
    ffbconstanteffectparameters.cpp
    ffbdevice.cpp
    ffbeffect.cpp
    ffbeffectfactory.cpp
    ffbeffectparameters.cpp
    ffbenvelopeparameters.cpp
    ffbnulleffect.cpp
    ffbperiodiceffect.cpp
    ffbperiodiceffectparameters.cpp
    ffbrampeffect.cpp
    ffbrampeffectparameters.cpp
    ffbrumbleeffect.cpp
    ffbrumbleeffectparameters.cpp
    globalsettings.cpp
    main.cpp
    mainwindow.cpp
    periodiceffectsettings.cpp
    rampeffectsettings.cpp
    rumbleeffectsettings.cpp)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(FFBChecker ${FFBChecker_SRCS})
target_link_libraries(FFBChecker Qt5::Widgets)
