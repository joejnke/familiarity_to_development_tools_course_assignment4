cmake_minimum_required(VERSION 3.5)

project(clieServModule VERSION 1.0)
set(PY_BINDER_SRC
    "${PROJECT_SOURCE_DIR}/src/py_binder.c"
    "${PROJECT_SOURCE_DIR}/src/client.c"
    "${PROJECT_SOURCE_DIR}/src/server.c"
    "${PROJECT_SOURCE_DIR}/src/clieserv_helper.c"
)

add_library(clieServModule SHARED ${PY_BINDER_SRC})

set_target_properties(
    clieServModule
    PROPERTIES
        PREFIX ""
        OUTPUT_NAME "clieServModule"
        LINKER_LANGUAGE C
)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

target_include_directories(clieServModule PUBLIC
    ${PYTHON_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
    )

target_link_libraries(clieServModule 
    my_client
    my_server
    ${PYTHON_LIBRARIES}
    )

#install(TARGETS my_client my_server DESTINATION "${PROJECT_SOURCE_DIR}/lib")
#install(FILES MathFunctions.h DESTINATION "${PROJECT_SOURCE_DIR}/include")
