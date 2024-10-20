cmake_minimum_required(VERSION 3.29)
project(Pong)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pong main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Lion/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Lion/SFML/include)
target_link_libraries(Pong sfml-system sfml-window sfml-graphics sfml-audio)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
