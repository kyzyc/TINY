cmake_minimum_required(VERSION 3.5.0)

project(TINY)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_subdirectory(lex)
# add_subdirectory(exercises)
# add_executable(tiny scan.c main.c util.c)
set (SOURCES
     main.c
     util.c
     scan.c
     parse.c
)
set (HEADERS
     util.h
     scan.h
     parse.h
     globals.h
)
add_executable(tiny ${HEADERS} ${SOURCES})
target_compile_options(tiny PRIVATE -g)
