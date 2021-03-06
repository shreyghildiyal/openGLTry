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
add_subdirectory(empire)
# libra
target_link_libraries(galaxyGame sfml-graphics sfml-window utils globals galacticObjects gameState empire)

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

# configure_file(${CMAKE_SOURCE_DIR}/gameData/stars.json ${CMAKE_CURRENT_BINARY_DIR}/gameData/stars.json)
# configure_file(${CMAKE_SOURCE_DIR}/gameData/textures.json ${CMAKE_CURRENT_BINARY_DIR}/gameData/textures.json)
# configure_file(${CMAKE_SOURCE_DIR}/gameData/starConnections.json ${CMAKE_CURRENT_BINARY_DIR}/gameData/starConnections.json)
# configure_file(${CMAKE_SOURCE_DIR}/gameData/planets.json ${CMAKE_CURRENT_BINARY_DIR}/gameData/planets.json)
# configure_file(${CMAKE_SOURCE_DIR}/gameData/empires.json ${CMAKE_CURRENT_BINARY_DIR}/gameData/empires.json)

# add_custom_command(
#     TARGET galaxyGame POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_SOURCE_DIR}/sprites
#             ${CMAKE_CURRENT_BINARY_DIR}/sprites)

# add_custom_command(
#     TARGET galaxyGame POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_SOURCE_DIR}/fonts
#             ${CMAKE_CURRENT_BINARY_DIR}/fonts)


add_custom_target(copy_game_data
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/staticFiles/gameData ${CMAKE_CURRENT_BINARY_DIR}/staticFiles/gameData
)
add_dependencies(galaxyGame copy_game_data)

add_custom_target(copy_sprites
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/staticFiles/sprites ${CMAKE_CURRENT_BINARY_DIR}/staticFiles/sprites
)
add_dependencies(galaxyGame copy_sprites)

add_custom_target(copy_fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/staticFiles/fonts ${CMAKE_CURRENT_BINARY_DIR}/staticFiles/fonts
)
add_dependencies(galaxyGame copy_fonts)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
