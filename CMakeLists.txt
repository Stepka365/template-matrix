cmake_minimum_required(VERSION 3.23)
project(Labo_2nd)

set(CMAKE_CXX_STANDARD 17)

file(GLOB my_src *.cpp)

add_executable(Labo_2nd ${my_src})
