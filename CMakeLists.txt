cmake_minimum_required(VERSION 3.1)

project(FFBChecker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_definitions("-DQT_DEPRECATED_WARNINGS -DQT_DISABLE_DEPRECATED_BEFORE=0x060000")

if (UNIX)
    add_definitions("-DFFBC_PLATFORM_LINUX")
    add_definitions("-Wall -pedantic")

    if ("${SDL2_XDIR}" STREQUAL "")
        find_package(SDL2)
        if (SDL2_FOUND)
            add_definitions("-DFFBC_HAVE_SDL2")
            set(SDL2_CMAKE_AUTO 1)
        endif()
    else ()
        # Assume that SDL2 is available
        set(SDL2_FOUND 1)
    endif()
elseif (WIN32)
    add_definitions("-DFFBC_PLATFORM_WIN32 -DFFBC_HAVE_SDL2")

    # Enforce SDL2 on Win32
    set(SDL2_FOUND 1)
    # SDL2_XDIR has to be set manually
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

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
    rumbleeffectsettings.cpp
    )

if (UNIX)
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
        linuxffbconditioneffect.cpp
        )
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
        sdl2deviceprober.cpp
        )
endif()

if (SDL2_FOUND AND NOT SDL2_CMAKE_AUTO)
    include_directories(${INCLUDE_DIRECTORIES}
                        SYSTEM "${SDL2_XDIR}/include"
                        )
    link_directories(${LINK_DIRECTORIES}
                     "${SDL2_XDIR}/lib"
                     )
endif()

if (UNIX)
    add_executable(FFBChecker ${FFBChecker_SRCS})
elseif (WIN32)
    add_executable(FFBChecker WIN32 ${FFBChecker_SRCS})
endif ()

target_link_libraries(FFBChecker
                      PRIVATE Qt5::Core
                      PRIVATE Qt5::Gui
                      PRIVATE Qt5::Widgets
                      )

if (WIN32)
    target_link_libraries(FFBChecker
                          PRIVATE "Ws2_32.lib"
                          PRIVATE "winmm.lib"
                          PRIVATE "imm32.lib"
                          )
endif()

if (SDL2_FOUND)
    if (SDL2_CMAKE_AUTO)
        target_link_libraries(FFBChecker PRIVATE SDL2::SDL2)
    else ()
        target_link_libraries(FFBChecker PRIVATE SDL2)
    endif ()
endif()
