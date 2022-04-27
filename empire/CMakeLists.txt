
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)


add_library(empire empire.h empire.cpp)

target_link_libraries(empire PUBLIC globals galacticObjects nlohmann_json::nlohmann_json)