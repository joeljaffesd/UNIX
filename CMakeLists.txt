cmake_minimum_required(VERSION 3.1)
project(UNIX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wav-write wav-write.cpp)
add_executable(wav-read wav-read.cpp)
add_executable(porcelain porcelain.cpp)

## Add lines here to make new executable targets
#add_executable(impulse-sweep impulse-sweep.cpp)
