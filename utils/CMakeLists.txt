
# include(FetchContent)
# FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
# FetchContent_MakeAvailable(json)

add_library(utils utils.h utils.cpp)
# add_library(textures textures.h textures.cpp)

# target_link_libraries(textures PUBLIC nlohmann_json::nlohmann_json)