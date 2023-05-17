cmake_minimum_required(VERSION 3.20)
project(MaineCoon)
set(CMAKE_CXX_STANDARD 17)
if(APPLE)
    message(STATUS "Including Objective-C++ for APPLE")
    list(APPEND LANGUAGES OBJC)
    list(APPEND LANGUAGES OBJCXX)
    set(CMAKE_OBJCXX_STANDARD 14)
    set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)
    set(CMAKE_OBJCXX_EXTENSIONS OFF)
endif()

###################################################################
# Local variables
###################################################################
set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(PROJECT_VENDOR_DIR "${CMAKE_CURRENT_LIST_DIR}/vendor")


# For GTK
# The `pkg_check_modules` function is created with this call
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} )

# Vendor/Libraries
set(IMGUI "${PROJECT_VENDOR_DIR}/imgui")
set(GLFW "${PROJECT_VENDOR_DIR}/glfw")
set(GLM "${PROJECT_VENDOR_DIR}/glm")
set(STB "${PROJECT_VENDOR_DIR}/stb_image")

###################################################################
# Project Sources and add library
###################################################################
file(GLOB_RECURSE PROJECT_SOURCES
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        )

# Additional project sources (vendors, etc.)
list(APPEND PROJECT_SOURCES
        # Vendor sources --------------------------
        "${IMGUI}/imconfig.h"
        "${IMGUI}/imgui.cpp"
        "${IMGUI}/imgui_draw.cpp"
        "${IMGUI}/imgui_widgets.cpp"
        "${IMGUI}/imgui_tables.cpp"
        "${IMGUI}/imgui_demo.cpp"
        "${IMGUI}/imgui_internal.h"
        "${IMGUI}/backends/imgui_impl_opengl3.cpp"
        "${IMGUI}/backends/imgui_impl_glfw.cpp"

        "${STB}/stb_image.h"
        # -----------------------------------------
        )

# Add library
add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_VENDOR_DIR}"
        )

###################################################################
# Libraries
###################################################################
add_subdirectory(${GLM})
add_subdirectory(${GLFW})
add_subdirectory(${PROJECT_VENDOR_DIR}) # ImGui. It needs glfw so cmake file is at one previous folder to be able to access glfw.

target_link_libraries(${PROJECT_NAME} PUBLIC
        "glfw"
        "glm"
        "imgui"
        ${OPENGL_LIBRARIES}
        "${MacLib}"
        )
# target_link_libraries()

###################################################################
# Compiler options
###################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE=1 Dosmesa=true)

# if (APPLE)
# #    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
#     target_compile_definitions(${PROJECT_NAME} PUBLIC TB_DEBUG=1 TB_PLATFORM_MACOS=1)
# elseif (WIN32)
#     target_compile_definitions(${PROJECT_NAME} PUBLIC TB_DEBUG=1 TB_PLATFORM_WINDOWS=1 TB_BUILD_DLL=1 BUILD_SHARED_LIBS=1)
# endif ()

# #Pass arguments----------------------------------------------------
# if(WIN32)
#     # add_compile_definitions(RC_PLATFORM_WINDOWS)
#     set(WINDOW
#             src/Platform/Windows/WindowsWindow.cpp
#             src/Platform/Windows/WindowsWindow.h
#             src/Platform/MacUtils.h
#             # src/Platform/Windows/processordetection.cpp
#             )

#     set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
#     set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
#     include_directories(GL)

#     target_compile_definitions(${PROJECT_NAME} PUBLIC TB_DEBUG=1 TB_PLATFORM_WINDOWS=1 TB_BUILD_DLL=1 BUILD_SHARED_LIBS=1)

# endif(WIN32)
if(APPLE)

    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit -framework Metal -framework Cocoa")

    set(MacLib
        "-framework Foundation"
        "-framework Cocoa"
        "-framework OpenGL"
        )

endif(APPLE)

###################################################################
# Precompiled header
###################################################################
target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/mcpch.h")