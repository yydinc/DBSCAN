cmake_minimum_required(VERSION 3.25)
project(dbscan C)

set(CMAKE_C_STANDARD 11)

add_library(dbscan SHARED dbscan.c
        stack.c
        helpers.c
)
