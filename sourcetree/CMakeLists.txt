cmake_minimum_required(VERSION 2.8)

project(minimal_NaCl_GLES2)

include_directories(${CMAKE_SOURCE_DIR})

set(SRCS
    ./external/nacl/opengl_context.cc
    MinimalInstance.cpp
    MinimalModule.cpp
)

add_executable(minimal_nacl_gles2 ${SRCS})

target_link_libraries(minimal_nacl_gles2
    ppapi_cpp
    ppapi
    ppapi_gles2
)

set(BT ${CMAKE_SOURCE_DIR}/../binarytree)
file(COPY ${BT}/common.js DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${BT}/index.html DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${BT}/minimal_nacl_gles2.nmf DESTINATION ${CMAKE_BINARY_DIR})
