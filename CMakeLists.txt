cmake_minimum_required(VERSION 3.7)

project(RayTracer)

include_directories(${MY_SOURCE_DIR}/src)
include_directories(${MY_SOURCE_DIR}/inc)

set(SRCS
	
src/Camera.cpp
inc/Camera.hpp
src/Color.cpp
inc/Color.hpp
inc/Defaults.hpp
src/main.cpp
inc/main.hpp
src/Plane.cpp
inc/Plane.hpp
src/Point.cpp
inc/Point.hpp
src/Shape.cpp
inc/Shape.hpp
inc/Vector.hpp
inc/World.hpp
src/Sphere.cpp
inc/Sphere.hpp
)

set(SDL2_DIR
SDL2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable (RayTracer ${SRCS})
target_link_libraries(RayTracer ${SDL2_LIBRARIES})

add_custom_command(TARGET RayTracer 
		   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_SOURCE_DIR}/SDL2/lib/x86/SDL2.dll $<TARGET_FILE_DIR:RayTracer>)


