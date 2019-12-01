cmake_minimum_required(VERSION 3.5)

# set the project name and version
project(client VERSION 1.0)

# add shared libraries
add_library(my_client SHARED "${PROJECT_SOURCE_DIR}/client.c")
add_library(my_server SHARED "${PROJECT_SOURCE_DIR}/server.c")

target_include_directories(my_client PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
    )
target_include_directories(my_server PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
    )

