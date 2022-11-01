cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(violet3)

# Set this to the minimal version you want to support
find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

add_subdirectory(lib/Unity-2.5.2/) # testing framework

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -pg")

file(GLOB_RECURSE SOURCES src/*.c)
set(HEADERS
  include/
  lib/C-Macro-Collections/src)

# This is the main part:
add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})
target_link_libraries(${PROJECT_NAME} raylib)

# Test code that checks if raylib is working properly
add_executable(raylib_free_cube_test
  test/raylib_free_camera.c
  )
#set(raylib_VERBOSE 1)
target_link_libraries(raylib_free_cube_test raylib violet3)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()


add_executable(violet3_test_all
  test/test_rendering.c
  )
target_link_libraries(violet3_test_all violet3 unity)

add_executable(violet3_test_application
  test/test_application.c)
target_link_libraries(violet3_test_application violet3 unity)
target_include_directories(violet3_test_application PUBLIC include/)

# That's it! You should have an example executable that you can run. Have fun!
