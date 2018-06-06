
add_executable( Knoop.Node.test
                assignment.test.cpp
                ctor.test.cpp
                example.cpp
                get.test.cpp
                list.test.cpp
                map.test.cpp
                Node.test.cpp )
target_compile_options( Knoop.Node.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${Knoop_appended_flags} )
target_link_libraries( Knoop.Node.test PUBLIC Knoop ) 
add_test( NAME Knoop.Node COMMAND Knoop.Node.test )