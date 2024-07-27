cmake_minimum_required(VERSION 3.22)
project(maine-coon
	VERSION 0.0.3
    DESCRIPTION "Application Framework"
	HOMEPAGE_URL "https://github.com/tabdroid-1/MaineCoon"
    LANGUAGES CXX
)

if(APPLE)
    message(STATUS "Including Objective-C++ for APPLE")
    list(APPEND LANGUAGES OBJC)
    list(APPEND LANGUAGES OBJCXX)
    set(CMAKE_OBJCXX_STANDARD 14)
    set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)
    set(CMAKE_OBJCXX_EXTENSIONS OFF)
endif()

option(MC_DIST "Enable distrubition build" OFF)

if(MC_DIST)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build utility programs" FORCE)
endif(MAINECOON_DIST)

if (NOT MC_DIST AND NOT WIN32)
    add_definitions(-w) # disables warnings
endif()

set(PROJECT_SOURCE_DIR "src")
set(PROJECT_INCLUDE_DIR "include")
set(PROJECT_VENDOR_DIR "vendor")

# ##############################################################################
# Add dependencies 
# ##############################################################################

set(SDL2 "${PROJECT_VENDOR_DIR}/SDL2")
set(GLAD "${PROJECT_VENDOR_DIR}/glad")
set(STB "${PROJECT_VENDOR_DIR}/stb")
set(SPDLOG "${PROJECT_VENDOR_DIR}/spdlog")
set(IMGUI "${PROJECT_VENDOR_DIR}/imgui")
set(IMGUIZMO "${PROJECT_VENDOR_DIR}/imguizmo")
set(TRACY "${PROJECT_VENDOR_DIR}/tracy")
set(OPENAL "${PROJECT_VENDOR_DIR}/openal-soft")
set(LIBSNDFILE "${PROJECT_VENDOR_DIR}/libsndfile")

# ##############################################################################
# Project executable setup
# ##############################################################################

file(GLOB_RECURSE PROJECT_SOURCES 
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        )

# # Additional project sources (vendors, etc.)
list(APPEND PROJECT_SOURCES
        "${STB}/stb_image.h"
        "${STB}/stb_image.cpp"
        "${SDL2}/include/SDL.h"
        )


add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_VENDOR_DIR}) 
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIR}) 
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES_DIR}) 
target_include_directories(${PROJECT_NAME} PUBLIC ${SPDLOG}/include) 
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENAL}/include) 
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBSNDFILE}/include) 
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI}) 
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUIZMO}) 
target_include_directories(${PROJECT_NAME} PRIVATE ${STB}) 
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS}) 
target_include_directories(${PROJECT_NAME} PUBLIC ${TRACY}) 

# ####################
# Add Subdirectories
# ####################

set(ALSOFT_UTILS OFF CACHE BOOL "Build utility programs" FORCE)
set(ALSOFT_NO_CONFIG_UTIL OFF CACHE BOOL "Disable building the alsoft-config utility" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "Build example programs" FORCE)
set(ALSOFT_TESTS OFF CACHE BOOL "Build test programs" FORCE)
set(ALSOFT_INSTALL  OFF CACHE BOOL "Install main library" FORCE)
set(ALSOFT_INSTALL_CONFIG CACHE BOOL "Install alsoft.conf sample configuration file" FORCE)
set(ALSOFT_INSTALL_HRTF_DATA CACHE BOOL "Install HRTF data files" FORCE)
set(ALSOFT_INSTALL_AMBDEC_PRESETS CACHE BOOL "Install AmbDec preset files" FORCE)
set(ALSOFT_INSTALL_EXAMPLES BOOL "Install example programs (alplay, alstream, ...)" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries (libsndfile)" FORCE)
set(BUILD_PROGRAMS OFF CACHE BOOL "Build programs (libsndfile)" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples (libsndfile)" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "Build tests (libsndfile)" FORCE)
set(SDL_SHARED OFF CACHE BOOL "Build a shared version of the library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build a static version of the library" FORCE)
set(SDL_TEST OFF CACHE BOOL "Build the SDL2_test library" FORCE)

add_subdirectory(${SDL2} EXCLUDE_FROM_ALL)
add_subdirectory(${TRACY})
add_subdirectory(${SPDLOG})
add_subdirectory(${IMGUI})
add_subdirectory(${IMGUIZMO})
add_subdirectory(${LIBSNDFILE})

if (NOT EMSCRIPTEN)
add_subdirectory(${OPENAL})
endif()

if (WIN32)

    if (MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /experimental:c11atomics console)


        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /SUBSYSTEM:CONSOLE")
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
        endif()
    endif()

    if (MINGW)
        set(CMAKE_SYSTEM_NAME Windows)
        set(ENABLE_STATIC_RUNTIME ON CACHE BOOL "Enable static runtime" FORCE)
        target_link_options(${PROJECT_NAME} PUBLIC -static)
        target_compile_options(${PROJECT_NAME} PUBLIC -mconsole)

        if(MAINECOON_DIST)
            target_link_options(${PROJECT_NAME} PUBLIC -mwindows)
        else()
            target_link_options(${PROJECT_NAME} PUBLIC -mconsole)
        endif()

        # target_link_libraries(${PROJECT_NAME} PUBLIC mingw32) 
    endif()

    message(STATUS "Generating scripts for Windows")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        imgui
        # spdlog::spdlog gives multiple definition error
        SDL2::SDL2-static
        SDL2::SDL2main
        imguizmo
        sndfile
        tracy 
        OpenAL::OpenAL
        )


elseif (UNIX AND NOT APPLE AND NOT ANDROID AND NOT EMSCRIPTEN)

    find_package(OpenAL)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

    message(STATUS "Generating scripts for Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        imgui
        spdlog
        SDL2::SDL2-static
        imguizmo
        tracy 
        OpenAL::OpenAL
        sndfile
        PkgConfig::GTK4
        )
elseif (APPLE)
    message(STATUS "Generating scripts for Mac")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        tracy 
        imgui
        spdlog
        SDL2::SDL2-static
        imguizmo
        OpenAL::OpenAL
        sndfile
        )
elseif (EMSCRIPTEN)

    add_compile_definitions("__EMSCRIPTEN__")

    target_link_options(${PROJECT_NAME} PUBLIC -pthread)
    target_compile_options(${PROJECT_NAME} PUBLIC -pthread)


    message(STATUS "Generating scripts for EMSCRIPTEN")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        imgui
        tracy 
        spdlog
        sndfile
        imguizmo
        SDL2::SDL2-static
        )
elseif (ANDROID)
    message(STATUS "Generating scripts for Android")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        imgui
        spdlog
        SDL2::SDL2
        SDL2::SDL2main
        imguizmo
        GLESv2
        GLESv3
        EGL
        log
        android
        )
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DDEBUG -DMC_DEBUG=1")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_INCLUDE_DIR}/mcpch.h")
