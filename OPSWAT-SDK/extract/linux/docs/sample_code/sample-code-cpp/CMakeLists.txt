cmake_minimum_required(VERSION 3.5.1)

project(sample-code-cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)
include_directories(sample-code-cpp)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

file (GLOB SOLIBS "libs/*.so")

file (GLOB CPP "sample-code-cpp/*.cpp")

add_executable(sample-code-cpp ${CPP})
target_link_libraries(sample-code-cpp ${SOLIBS})
