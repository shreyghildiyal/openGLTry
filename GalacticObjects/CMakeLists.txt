

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(galacticDrawable galacticDrawable.h galacticDrawable.cpp )
add_library(star star.h star.cpp )

# libr

target_link_libraries(star PUBLIC textures displayMode galacticDrawable   nlohmann_json::nlohmann_json)