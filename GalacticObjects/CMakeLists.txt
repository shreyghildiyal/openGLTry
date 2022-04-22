

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(galacticObjects star.h star.cpp galacticDrawable.h galacticDrawable.cpp planet.cpp planet.h)
# libr

target_link_libraries(galacticObjects PUBLIC textures displayMode nlohmann_json::nlohmann_json)