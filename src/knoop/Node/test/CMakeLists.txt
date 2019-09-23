
add_executable( knoop.Node.test
                example.cpp
                ctor.test.cpp
                Node.test.cpp
                list.test.cpp
                map.test.cpp
                get.test.cpp
                assignment.test.cpp )
target_compile_options( knoop.Node.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${knoop_appended_flags} )
target_link_libraries( knoop.Node.test PUBLIC knoop ) 
add_test( NAME knoop.Node COMMAND knoop.Node.test )