cmake_minimum_required(VERSION 3.16)
project(pybind11testwin)
set(CMAKE_CXX_STANDARD 17)


# pybind11
add_subdirectory(extern/pybind11)


pybind11_add_module (
    pybind11testwin 
    mainBinding.cpp
)


target_include_directories ( pybind11testwin PRIVATE teststep)
