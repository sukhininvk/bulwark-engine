cmake_minimum_required(VERSION 4.2)
project(BulwarkEngine)

add_subdirectory(src)
add_subdirectory(vendor/SDL)

add_library(bulwark SHARED
        include/Bulwark/application.h
        include/Bulwark/window.h
        include/Bulwark/input.h

        src/application.cpp
        src/window.cpp
        src/input.cpp
)

add_library(bulwark_entry OBJECT
        entry/main.cpp
)

target_compile_features(bulwark PRIVATE cxx_std_20)
target_link_libraries(bulwark PUBLIC SDL3::SDL3)
target_link_libraries(bulwark_entry PUBLIC bulwark)
target_include_directories(bulwark PUBLIC include)

set_target_properties(bulwark PROPERTIES PREFIX "")
