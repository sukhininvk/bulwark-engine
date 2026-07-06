cmake_minimum_required(VERSION 4.2)
project(BulwarkEngine)

add_subdirectory(src)
add_subdirectory(vendor/SDL)

add_library(bulwark STATIC
        include/Bulwark/application.h
        include/Bulwark/window.h
        include/Bulwark/input.h

        src/main.cpp
        src/application.cpp
        src/window.cpp
        src/input.cpp
)

target_compile_features(bulwark PRIVATE cxx_std_20)
target_link_libraries(bulwark PUBLIC SDL3::SDL3)
target_include_directories(bulwark PUBLIC include)

set_target_properties(bulwark PROPERTIES PREFIX "")
