

add_library(gameState gameState.h gameState.cpp)

target_link_libraries(gameState sfml-graphics sfml-window utils globals galacticObjects inputs empire)