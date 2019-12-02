cmake_minimum_required(VERSION 3.5)

# set the project name and version
#project(clieServ VERSION 1.0)

# add shared libraries
add_library(client SHARED "${CMAKE_CURRENT_SOURCE_DIR}/client.c")
add_library(server SHARED "${CMAKE_CURRENT_SOURCE_DIR}/server.c")

target_include_directories(client PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )
target_include_directories(server PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

