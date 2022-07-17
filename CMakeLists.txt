cmake_minimum_required(VERSION 3.22)
project(obj_model_viewer C)

set(CMAKE_C_STANDARD 99)

add_executable(obj_model_viewer main.c obj.c obj.h)
