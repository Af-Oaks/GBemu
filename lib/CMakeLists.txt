file (GLOB sources CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/lib/*.c")

file (GLOB headers CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")

add_library(emu STATIC ${sources} ${headers})

target_include_directories(emu PUBLIC ${PROJECT_SOURCE_DIR}/include )

# Find SDL2 and SDL2_ttf libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project
target_link_libraries(emu ${SDL2_LIBRARIES})
target_link_libraries(emu ${SDL2_TTF_LIBRARIES})