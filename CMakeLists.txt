cmake_minimum_required(VERSION 3.30)
project(busTransit)

set(CMAKE_CXX_STANDARD 20)

add_executable(busTransit main.cpp
        Vehicle.cpp
        Vehicle.h
        Bus.cpp
        Bus.h
        Stop.cpp
        Stop.h
        Route.cpp
        Route.h)
