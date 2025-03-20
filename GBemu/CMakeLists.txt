set(MAIN_SOURCES
  main.c
)

file (GLOB headers "${PROJECT_SOURCE_DIR}/include/*.h")

add_executable(gbemu ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(gbemu emu)
target_include_directories(gbemu PUBLIC ${PROJECT_SOURCE_DIR}/include )

message(STATUS "SDL Libraries: ${SDL2_LIBRARIES} - ${SDL2_LIBRARY}")
message(STATUS "SDL TTF Libraries: ${SDL2_TTF_LIBRARIES} - ${SDL2_TTF_LIBRARY}")