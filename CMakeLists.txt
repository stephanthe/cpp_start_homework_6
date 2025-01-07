cmake_minimum_required(VERSION 3.5.0)
project(containers VERSION 0.2.0 LANGUAGES C CXX)

set(PROJECT_NAME
    Containers
)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
                src/main.cpp
                )