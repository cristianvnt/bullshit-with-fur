cmake_minimum_required(VERSION 3.21)
project(bullshit-with-fur VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(tomlplusplus CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE 
	ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets"
)
target_include_directories(${PROJECT_NAME} PRIVATE 
	${CMAKE_SOURCE_DIR}/src
	${Stb_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
	glad::glad
	glfw
	glm::glm
	tomlplusplus::tomlplusplus
)
