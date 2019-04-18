cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_COMPILER
"C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.11.25503/bin/HostX64/x64/cl.exe")

project(RayTracer LANGUAGES CXX)
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
src/ScopedPerfTracker.cpp
inc/ScopedPerfTracker.h
inc/Sphere.hpp
src/LightSource.cpp
inc/LightSource.h
inc/Shading.h
src/Shading.cpp
inc/Debug.h
src/Debug.cpp
inc/Material.h
src/Material.cpp
inc/Reflection.h
src/Reflection.cpp
inc/MassBody.hpp
src/MassBody.cpp
inc/Line.hpp
src/Line.cpp
inc/DebugHandler.h
src/DebugHandler.cpp
inc/Singleton.h
)

set(SDL2_DIR
SDL2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(RayTracer ${SRCS})

######################################################################################


target_link_libraries(RayTracer ${SDL2_LIBRARIES})

add_custom_command(TARGET RayTracer 
		   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_SOURCE_DIR}/SDL2/lib/x64/SDL2.dll $<TARGET_FILE_DIR:RayTracer>)