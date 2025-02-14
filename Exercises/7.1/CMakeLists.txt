cmake_minimum_required(VERSION 2.8.9)
project(myprog)

find_package(BLAS REQUIRED)

add_executable(myprog src/main.cpp src/testFunction.cpp src/blasStuff.cpp)

target_link_libraries(myprog ${BLAS_LIBRARIES})

# Specify the output directory for the binaries
set_target_properties(myprog PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

