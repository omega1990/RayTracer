# RayTracer

*Work in progress*

This is my Ray Tracer/Caster implementation.

## Generating solution on Windows:

* Install CUDA (at least 9.1).
* Install VS v140 C++ toolkit.
* Run this in console: 

cmake -G "Visual Studio 15 2017 Win64" -H. -Bbuild -T v140
*The toolset needs to specified in order to mitigate issues with CUDA 9.1.*


## Working with MacOS:
* Install VS Code
* Install cmake
* Install C++ plugin for VS Code
* Install XCode (contains C++ build tools)
* Within VS Code press Command + Shift + P and run **CMake: Build a Target** (Choose RayCaster)


![alt text](raytracing2.PNG)
