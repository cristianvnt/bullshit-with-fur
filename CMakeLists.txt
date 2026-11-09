cmake_minimum_required(VERSION 3.21)
project(bullshit-with-fur LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(bullshit src/main.cpp)
target_link_libraries(bullshit PRIVATE glfw glm::glm glad::glad)
