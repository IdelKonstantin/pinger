cmake_minimum_required(VERSION 3.7)

project(inet_pinger)

set(compiller_options -Wall -std=c++1z -g -O0)

set(INC_PATH "inc")
set(SRC_PATH "src")

file(GLOB HEADERS ${INC_PATH}/*.h)
file(GLOB SOURCES ${SRC_PATH}/*.cpp)

include_directories(${INC_PATH})

add_executable(${PROJECT_NAME}
	${SOURCES} 
	${HEADERS}
	main.cpp
)

target_link_libraries(${PROJECT_NAME} curl)

target_compile_options(${PROJECT_NAME} PRIVATE ${compiller_options})
