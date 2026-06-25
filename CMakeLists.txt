cmake_minimum_required(VERSION 4.2)
project(Bulwark)

add_subdirectory(src/engine)
add_subdirectory(vendor/SDL)

add_executable(Bulwark WIN32 src/engine/main.cpp
        src/engine/application.h
        src/engine/application.cpp
        src/engine/window.h
        src/engine/window.cpp)

target_compile_features(Bulwark PRIVATE cxx_std_20)

target_link_libraries(Bulwark PRIVATE SDL3::SDL3)
