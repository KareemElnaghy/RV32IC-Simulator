cmake_minimum_required(VERSION 3.28)
project(RV32IC_Simulator)

set(CMAKE_CXX_STANDARD 23)

add_executable(RV32IC_Simulator main.cpp
        Register.h
        Register.cpp
        Instructions.cpp
        Instructions.h
        Global.h
)
