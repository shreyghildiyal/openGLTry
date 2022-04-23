

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

# add_library(displayMode )
# add_library(textures )
add_library(globals textures.h textures.cpp displayMode.h displayMode.cpp fonts.h fonts.cpp)

target_link_libraries(globals PUBLIC nlohmann_json::nlohmann_json)