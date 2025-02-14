cmake_minimum_required(VERSION 2.8.9)
project(myprog)

find_package(BLAS REQUIRED)

add_executable(myprog src/main.cpp)

target_link_libraries(myprog ${BLAS_LIBRARIES})

