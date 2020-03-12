cmake_minimum_required( VERSION 3.13 )
project( Kalculator )

add_executable( Kalculator
    ${CMAKE_SOURCE_DIR}/sources/main.cpp    
)

enable_testing()

file( GLOB test_samples "samples/*.test" )
foreach( file ${test_samples} )
    get_filename_component( nn ${file} NAME )

    add_test( NAME Print_${nn} COMMAND ${CMAKE_BINARY_DIR}/Kalculator print ${file} )
endforeach()

add_test( NAME Print_Invalid COMMAND ${CMAKE_BINARY_DIR}/Kalculator print ssd )
set_tests_properties( Print_Invalid PROPERTIES WILL_FAIL true )
