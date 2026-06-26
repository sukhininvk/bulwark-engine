cmake_minimum_required(VERSION 4.2)
project(Bulwark)

add_subdirectory(src)
add_subdirectory(vendor/SDL)

add_executable(Bulwark WIN32 src/main.cpp
        src/application.h
        src/application.cpp
        src/window.h
        src/window.cpp)

target_compile_features(Bulwark PRIVATE cxx_std_20)

target_link_libraries(Bulwark PRIVATE SDL3::SDL3)
