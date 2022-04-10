
add_library(galacticDrawable galacticDrawable.h galacticDrawable.cpp )
add_library(star star.h star.cpp )

# libr

target_link_libraries(star textures displayMode galacticDrawable  )