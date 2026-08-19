cmake_minimum_required(VERSION 3.5)
project(background LANGUAGES C CXX)

#find_package(SDL2 REQUIRED CONFIG)
#target_link_libraries(myexe PRIVATE SDL2::SDL2)

add_subdirectory(external/pixeltoaster)

set(ENABLE_EXAMPLES OFF CACHE BOOL "" FORCE)
add_executable(main main.c display.cpp)

target_include_directories(main PRIVATE include)
target_include_directories(main PRIVATE external/pixeltoaster)
target_link_libraries(main PRIVATE PixelToaster)
