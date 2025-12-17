cmake_minimum_required(VERSION 4.1)
project(Neutronic_Decay)

set(CMAKE_CXX_STANDARD 20)

include_directories(include/)

if(WIN32)

    message(STATUS "- - - Windows build option - - -")
    link_directories(lib/Windows)

    add_executable(Neutronic_Decay
            src/main.cpp
            src/AnimatedSprite.cpp
            src/Entity.cpp
            src/Player.cpp
            src/Arrow.cpp
            src/Homing.cpp
    )

    target_link_libraries(Neutronic_Decay
            raylib
            winmm
            gdi32
            opengl32
    )

else()
    message(STATUS "- - - UNIX System option - - -")
    link_directories(lib/GNU-Linux)

    add_executable(Neutronic-Decay
            src/main.cpp
            src/AnimatedSprite.cpp
            src/Entity.cpp
            src/Player.cpp
            src/Arrow.cpp
            src/Homing.cpp
    )

    target_link_libraries(Neutronic_Decay
            raylib
            GL
            m
            pthread
            dl
            X11
    )

endif()
