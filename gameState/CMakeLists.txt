

add_library(gameState gameState.h gameState.cpp)

target_link_libraries(gameState sfml-graphics sfml-window utils displayMode galacticObjects inputs)