cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project (my_game CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${my_game_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE my_game_SOURCES "src/*.cpp")

add_executable(my_game_app ${my_game_SOURCES})
target_link_libraries(my_game_app ${SDL2_LIBRARIES})

add_custom_command(TARGET my_game_app PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:my_game_app>/data)

add_custom_target(run
  COMMAND my_game_app
  DEPENDS my_game_app
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})
