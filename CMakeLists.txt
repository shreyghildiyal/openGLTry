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
add_subdirectory(utils)
add_subdirectory(gameState)
add_subdirectory(input)
# libra
target_link_libraries(galaxyGame sfml-graphics sfml-window utils globals galacticObjects gameState)

# add_custom_command(
#     TARGET galaxyGame POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#             ${CMAKE_SOURCE_DIR}/gameData/stars.json
#             ${CMAKE_CURRENT_BINARY_DIR}/gameData/stars.json)

# add_custom_command(
#     TARGET galaxyGame POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#             ${CMAKE_SOURCE_DIR}/gameData/textures.json
#             ${CMAKE_CURRENT_BINARY_DIR}/gameData/textures.json)

configure_file(${CMAKE_SOURCE_DIR}/gameData/stars.json ${CMAKE_CURRENT_BINARY_DIR}/gameData/stars.json)
configure_file(${CMAKE_SOURCE_DIR}/gameData/textures.json ${CMAKE_CURRENT_BINARY_DIR}/gameData/textures.json)
configure_file(${CMAKE_SOURCE_DIR}/gameData/starConnections.json ${CMAKE_CURRENT_BINARY_DIR}/gameData/starConnections.json)
configure_file(${CMAKE_SOURCE_DIR}/gameData/planets.json ${CMAKE_CURRENT_BINARY_DIR}/gameData/planets.json)

add_custom_command(
    TARGET galaxyGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/sprites
            ${CMAKE_CURRENT_BINARY_DIR}/sprites)

add_custom_command(
    TARGET galaxyGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/fonts
            ${CMAKE_CURRENT_BINARY_DIR}/fonts)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
