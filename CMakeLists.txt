cmake_minimum_required(VERSION 3.8)

set(CMAKE_CUDA_COMPILER
"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v9.1/bin/nvcc.exe")
set(CMAKE_CXX_COMPILER
"C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.11.25503/bin/HostX64/x64/cl.exe")

project(RayTracer LANGUAGES CXX CUDA)
set (CMAKE_CXX_STANDARD 17)

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
src/World.cpp
inc/WorldDrawer.hpp
src/WorldDrawer.cpp
inc/DrawPixel.hpp
src/DrawPixel.cpp
src/Sphere.cpp
inc/Sphere.hpp
)

set(SDL2_DIR
SDL2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(CUDA REQUIRED)

cuda_add_executable(RayTracer ${SRCS})

######################################################################################


target_link_libraries(RayTracer ${SDL2_LIBRARIES})

add_custom_command(TARGET RayTracer 
		   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_SOURCE_DIR}/SDL2/lib/x64/SDL2.dll $<TARGET_FILE_DIR:RayTracer>)

#add_custom_command(TARGET RayTracer 
#		   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy
#                       ${CMAKE_SOURCE_DIR}/CUDA/freeglut.dll $<TARGET_FILE_DIR:RayTracer>)
#
#add_custom_command(TARGET RayTracer 
#		   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy
#                       ${CMAKE_SOURCE_DIR}/CUDA/FreeImage.dll $<TARGET_FILE_DIR:RayTracer>)
#
#add_custom_command(TARGET RayTracer 
#		   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy
#                       ${CMAKE_SOURCE_DIR}/CUDA/glew64.dll $<TARGET_FILE_DIR:RayTracer>)

