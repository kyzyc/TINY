find_program(LEX_EXE
    flex
)
if(LEX_EXE STREQUAL "LEX_EXE-NOTFOUND")
    message(FATAL_ERROR "dear user, plase install flex!")
endif(LEX_EXE STREQUAL "LEX_EXE-NOTFOUND")

# reuseable cmake macro for lex
MACRO(LEX_FILE _filename)
    GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ./${_basename}.c
        COMMAND ${LEX_EXE}
                -o ${_basename}.c
                ./${_filename}
        DEPENDS ${_filename} )
ENDMACRO(LEX_FILE)

LEX_FILE(example2-20.l)
LEX_FILE(example2-21.l)
LEX_FILE(example2-22.l)
LEX_FILE(tiny.l)
# LEX_TARGET(Test ../src/test.l ../src/test.c)

add_executable(example2-20 example2-20.c)
add_executable(example2-21 example2-21.c)
add_executable(example2-22 example2-22.c)
add_executable(tiny_lex tiny.c ../main.c ../util.c)
