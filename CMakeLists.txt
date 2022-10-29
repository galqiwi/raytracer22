cmake_minimum_required(VERSION 3.23)
project(raytracer22)

set(CMAKE_CXX_STANDARD 20)

add_executable(raytracer22 main.cpp src/netbpm/net_bpm_image.h src/netbpm/public.h src/netbpm/net_bpm_image.cpp src/raytracer/public.h src/raytracer/vector_3d.hpp src/raytracer/ray.h src/raytracer/scene.h src/raytracer/color.hpp src/raytracer/scene.cpp src/raytracer/camera.h src/raytracer/camera.cpp src/raytracer/vector_3d.cpp)
