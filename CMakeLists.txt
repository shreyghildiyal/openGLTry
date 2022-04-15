cmake_minimum_required(VERSION 3.0.0)
project(galaxyGame VERSION 0.1.0)

include(CTest)
enable_testing()

# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# include_directories(${SDL2_INCLUDE_DIRS})
find_package(SFML REQUIRED system graphics window)

add_executable(galaxyGame main.cpp)
# include_directories(${SFML_INCLUDE_DIR})
add_subdirectory(GalacticObjects)
add_subdirectory(globals)
# libra
target_link_libraries(galaxyGame sfml-graphics sfml-window displayMode star galacticDrawable)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
