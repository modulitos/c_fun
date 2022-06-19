# taken from:
# https://github.com/modulitos/ostep-hw/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)
project(C fun)

set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add executable target with source files listed in SOURCE_FILES variable
set(
        SOURCE_FILES getifaddrs_explore.c
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(simple_example ${SOURCE_FILES})

# Additional executables can be added like so:
# add_executable(my_test my_dir/my_test.c)
