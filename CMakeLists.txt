cmake_minimum_required(VERSION 2.6.0)

project(TINY)

add_executable(tiny scan.c main.c util.c)
target_compile_options(tiny PRIVATE -g)
