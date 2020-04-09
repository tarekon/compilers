cmake_minimum_required( VERSION 3.13 )
project( Kalculator )

find_package( FLEX )
find_package( BISON )

FLEX_TARGET( KalcLexer ${CMAKE_SOURCE_DIR}/sources/lexer.l
    ${CMAKE_BINARY_DIR}/kLexer.cpp
    COMPILE_FLAGS --header=${CMAKE_BINARY_DIR}/kLexer.h )

BISON_TARGET( KalcParser ${CMAKE_SOURCE_DIR}/sources/parser.y
    ${CMAKE_BINARY_DIR}/kParser.cpp
    VERBOSE
)

add_executable( Kalculator
    ${CMAKE_SOURCE_DIR}/sources/main.cpp
    ${CMAKE_SOURCE_DIR}/sources/CalcVisitor.cpp
    ${FLEX_KalcLexer_OUTPUTS}
    ${BISON_KalcParser_OUTPUTS}
)
target_include_directories( Kalculator PRIVATE ${CMAKE_BINARY_DIR} )
target_include_directories( Kalculator PRIVATE ${CMAKE_SOURCE_DIR}/sources )


enable_testing()

file( GLOB test_samples "samples/*.test" )
foreach( file ${test_samples} )
    get_filename_component( nn ${file} NAME )

    add_test( NAME Print_${nn} COMMAND ${CMAKE_BINARY_DIR}/Kalculator print ${file} )
    add_test( NAME Lexer_${nn} COMMAND ${CMAKE_BINARY_DIR}/Kalculator lexer ${file} )
    add_test( NAME Calc_${nn} COMMAND ${CMAKE_BINARY_DIR}/Kalculator calc ${file} )
    add_test( NAME Valgrind_calc_${nn} COMMAND valgrind ${CMAKE_BINARY_DIR}/Kalculator calc ${file} )
endforeach()

set_tests_properties( Calc_complex.test PROPERTIES PASS_REGULAR_EXPRESSION "Result is 7" )
set_tests_properties( Calc_mul.test PROPERTIES PASS_REGULAR_EXPRESSION "Result is 80810730" )
set_tests_properties( Calc_sum.test PROPERTIES PASS_REGULAR_EXPRESSION "Result is 23657" )

set_tests_properties( Valgrind_calc_invalid.test PROPERTIES WILL_FAIL true )
set_tests_properties( Calc_invalid.test PROPERTIES WILL_FAIL true )

add_test( NAME Print_Invalid COMMAND ${CMAKE_BINARY_DIR}/Kalculator print ssd )
set_tests_properties( Print_Invalid PROPERTIES WILL_FAIL true )
