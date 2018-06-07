
cmake_minimum_required( VERSION 3.2 ) 
set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported configuration types" FORCE )
        
if ( NOT GIT_EXECUTABLE )
    find_package( Git 2.1 )
    if ( NOT GIT_FOUND )
        message( FATAL_ERROR "git installation was not found." )
    endif()
endif()

if( NOT ROOT_DIRECTORY )
    set( ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
    if ( NOT fetched_subprojects )
        if ( NOT PYTHON_EXECUTABLE )
            find_package( PythonInterp 3.4 )
            if ( NOT PYTHONINTERP_FOUND )
                message( FATAL_ERROR "Python interpeter installation was not found." )
            endif()
        endif()
        execute_process( COMMAND ${PYTHON_EXECUTABLE} "./metaconfigure/fetch_subprojects.py"
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                         RESULT_VARIABLE fetch_failure )
        if ( NOT fetch_failure )
            set( fetched_subprojects TRUE CACHE BOOL "fetch script ran" )
        else()
            message( FATAL_ERROR "Failed to fetch dependencies" )
        endif()
    endif()
endif()

project( Knoop LANGUAGES CXX )
get_directory_property( is_subproject PARENT_DIRECTORY )
include( CMakeDependentOption REQUIRED )

set( Knoop_AppleClang_minimum_version 8.0 )
set( Knoop_GNU_minimum_version 6.2 )
set( Knoop_Clang_minimum_version 3.8 )

if( Knoop_${CMAKE_CXX_COMPILER_ID}_minimum_version )
    if( CMAKE_CXX_COMPILER_VERSION AND
        CMAKE_CXX_COMPILER_VERSION VERSION_LESS
        ${Knoop_${CMAKE_CXX_COMPILER_ID}_minimum_version} )
        message( FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} version must be greater than ${Knoop_${CMAKE_CXX_COMPILER_ID}_minimum_version}" )
    endif()
endif()

# general properties
option( Knoop_strict "Compile time warnings are converted to errors" ON )

# binary instrumentation
option( coverage "Enable binary instrumentation to collect test coverage information in the DEBUG configuration" )
option( profile_generate "Enable binary instrumentation to generation execution profiles in the RELEASE configuration which may be used to guide later optimization" )

# additional optimizations
option( link_time_optimization "Enable link time optimization in the RELEASE configuration" )
option( profile_use "In the RELEASE configuration, leverage previously generated exeution profile to inform optimization decisions" )
option( nonportable_optimization "Enable optimizations which compromise portability of resulting binary in the RELEASE configuration" )

# libraries and linking
option( static "Statically link component and environment libraries" OFF )
if ( static AND ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" ) )
    message( FATAL_ERROR "Static binaries not supported on OSX" )
endif()

CMAKE_DEPENDENT_OPTION( static_libraries "Statically link component libraries" OFF "NOT static" ON )

option( unit_tests "Compile the Knoop unit tests and integrate with ctest" ON ) 

if ( profile_generate AND profile_use )
    message( FATAL_ERROR "Cannot both generate and use execution profile in the same configuration" )
endif()

if ( profile_generate )
    file( MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/profiling" )
endif()

set( Knoop_AppleClang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( Knoop_AppleClang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( Knoop_AppleClang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_AppleClang_Darwin_strict_flags "-Werror" )
set( Knoop_AppleClang_Darwin_coverage_flags "--coverage" )
set( Knoop_AppleClang_Darwin_subproject_flags  )
set( Knoop_AppleClang_Darwin_base_project_flags  )
set( Knoop_AppleClang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_AppleClang_Darwin_link_time_optimization_flags "-flto" )
set( Knoop_AppleClang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_AppleClang_Darwin_nonportable_optimization_flags "-march=native" )
set( Knoop_AppleClang_Darwin_static_flags "-static" )
set( Knoop_GNU_Windows_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( Knoop_GNU_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( Knoop_GNU_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_GNU_Windows_strict_flags "-Werror" )
set( Knoop_GNU_Windows_coverage_flags "--coverage" )
set( Knoop_GNU_Windows_subproject_flags  )
set( Knoop_GNU_Windows_base_project_flags  )
set( Knoop_GNU_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_Windows_link_time_optimization_flags "-flto" )
set( Knoop_GNU_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_Windows_nonportable_optimization_flags "-march=native" )
set( Knoop_GNU_Windows_static_flags "-static" )
set( Knoop_GNU_Darwin_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( Knoop_GNU_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( Knoop_GNU_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_GNU_Darwin_strict_flags "-Werror" )
set( Knoop_GNU_Darwin_coverage_flags "--coverage" )
set( Knoop_GNU_Darwin_subproject_flags  )
set( Knoop_GNU_Darwin_base_project_flags  )
set( Knoop_GNU_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_Darwin_link_time_optimization_flags "-flto" )
set( Knoop_GNU_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_Darwin_nonportable_optimization_flags "-march=native" )
set( Knoop_GNU_Darwin_static_flags "-static" )
set( Knoop_GNU_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( Knoop_GNU_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( Knoop_GNU_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_GNU_MinGW_strict_flags "-Werror" )
set( Knoop_GNU_MinGW_coverage_flags "--coverage" )
set( Knoop_GNU_MinGW_subproject_flags  )
set( Knoop_GNU_MinGW_base_project_flags  )
set( Knoop_GNU_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_MinGW_link_time_optimization_flags "-flto" )
set( Knoop_GNU_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_MinGW_nonportable_optimization_flags "-march=native" )
set( Knoop_GNU_MinGW_static_flags "-static" )
set( Knoop_GNU_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++14" )
set( Knoop_GNU_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( Knoop_GNU_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_GNU_CYGWIN_strict_flags "-Werror" )
set( Knoop_GNU_CYGWIN_coverage_flags "--coverage" )
set( Knoop_GNU_CYGWIN_subproject_flags  )
set( Knoop_GNU_CYGWIN_base_project_flags  )
set( Knoop_GNU_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_CYGWIN_link_time_optimization_flags "-flto" )
set( Knoop_GNU_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_CYGWIN_nonportable_optimization_flags "-march=native" )
set( Knoop_GNU_CYGWIN_static_flags "-static" )
set( Knoop_GNU_Linux_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( Knoop_GNU_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( Knoop_GNU_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_GNU_Linux_strict_flags "-Werror" )
set( Knoop_GNU_Linux_coverage_flags "--coverage" )
set( Knoop_GNU_Linux_subproject_flags  )
set( Knoop_GNU_Linux_base_project_flags  )
set( Knoop_GNU_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_Linux_link_time_optimization_flags "-flto" )
set( Knoop_GNU_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_GNU_Linux_nonportable_optimization_flags "-march=native" )
set( Knoop_GNU_Linux_static_flags "-static" )
set( Knoop_Clang_Windows_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( Knoop_Clang_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( Knoop_Clang_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_Clang_Windows_strict_flags "-Werror" )
set( Knoop_Clang_Windows_coverage_flags "--coverage" )
set( Knoop_Clang_Windows_subproject_flags  )
set( Knoop_Clang_Windows_base_project_flags  )
set( Knoop_Clang_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_Windows_link_time_optimization_flags "-flto" )
set( Knoop_Clang_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_Windows_nonportable_optimization_flags "-march=native" )
set( Knoop_Clang_Windows_static_flags "-static" )
set( Knoop_Clang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( Knoop_Clang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( Knoop_Clang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_Clang_Darwin_strict_flags "-Werror" )
set( Knoop_Clang_Darwin_coverage_flags "--coverage" )
set( Knoop_Clang_Darwin_subproject_flags  )
set( Knoop_Clang_Darwin_base_project_flags  )
set( Knoop_Clang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_Darwin_link_time_optimization_flags "-flto" )
set( Knoop_Clang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_Darwin_nonportable_optimization_flags "-march=native" )
set( Knoop_Clang_Darwin_static_flags "-static" )
set( Knoop_Clang_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( Knoop_Clang_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( Knoop_Clang_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_Clang_MinGW_strict_flags "-Werror" )
set( Knoop_Clang_MinGW_coverage_flags "--coverage" )
set( Knoop_Clang_MinGW_subproject_flags  )
set( Knoop_Clang_MinGW_base_project_flags  )
set( Knoop_Clang_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_MinGW_link_time_optimization_flags "-flto" )
set( Knoop_Clang_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_MinGW_nonportable_optimization_flags "-march=native" )
set( Knoop_Clang_MinGW_static_flags "-static" )
set( Knoop_Clang_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++14" )
set( Knoop_Clang_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( Knoop_Clang_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_Clang_CYGWIN_strict_flags "-Werror" )
set( Knoop_Clang_CYGWIN_coverage_flags "--coverage" )
set( Knoop_Clang_CYGWIN_subproject_flags  )
set( Knoop_Clang_CYGWIN_base_project_flags  )
set( Knoop_Clang_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_CYGWIN_link_time_optimization_flags "-flto" )
set( Knoop_Clang_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_CYGWIN_nonportable_optimization_flags "-march=native" )
set( Knoop_Clang_CYGWIN_static_flags "-static" )
set( Knoop_Clang_Linux_common_flags "-stdlib=libstdc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( Knoop_Clang_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( Knoop_Clang_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( Knoop_Clang_Linux_strict_flags "-Werror" )
set( Knoop_Clang_Linux_coverage_flags "--coverage" )
set( Knoop_Clang_Linux_subproject_flags  )
set( Knoop_Clang_Linux_base_project_flags  )
set( Knoop_Clang_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_Linux_link_time_optimization_flags "-flto" )
set( Knoop_Clang_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( Knoop_Clang_Linux_nonportable_optimization_flags "-march=native" )
set( Knoop_Clang_Linux_static_flags "-static" )
get_directory_property( is_subproject PARENT_DIRECTORY )

if( NOT TARGET catch-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/catch-adapter )
endif()

if( NOT TARGET range-v3-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/range-v3-adapter )
endif()

if( NOT TARGET valuable-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/valuable-adapter )
endif()

if( NOT TARGET variant-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/variant-adapter )
endif()


if ( NOT GIT_EXECUTABLE )
    find_package( Git )
    if ( NOT GIT_FOUND )
        message( FATAL_ERROR "git installation was not found." )
    endif()
endif()

execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
) 

message( STATUS "" )
message( STATUS "-----------------------------------------------------------" )
message( STATUS "" )
message( STATUS "Knoop" )
message( STATUS "Git current branch: ${GIT_BRANCH}" )
message( STATUS "Git commit hash: ${GIT_HASH}" )
message( STATUS "" )
message( STATUS "-----------------------------------------------------------" )

add_library( Knoop INTERFACE )
target_sources( Knoop INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/assignmentOperator.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/bracketOperator.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/contains.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/erase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/get.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/insert.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/keys.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/list.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/pop_back.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/pop_front.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/push_back.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/push_front.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/put.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/knoop/Node/src/values.hpp" )

target_include_directories( Knoop INTERFACE src/ )

set( PREFIX Knoop_${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME} )

target_link_libraries( Knoop INTERFACE "$<$<AND:$<CONFIG:RELEASE>,$<BOOL:${link_time_optimization}>>:${${PREFIX}_RELEASE_flags};${${PREFIX}_link_time_optimization_flags}$<$<BOOL:${profile_generate}>:${${PREFIX}_profile_generate_flags};>$<$<BOOL:${profile_use}>:${${PREFIX}_profile_use_flags};>$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags};>>$<$<CONFIG:DEBUG>:$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags};>>$<$<BOOL:CXX_appended_flags>:${CXX_appended_flags};>$<$<BOOL:Knoop_appended_flags>:${Knoop_appended_flags};>" )

target_link_libraries( Knoop INTERFACE catch-adapter INTERFACE range-v3-adapter INTERFACE valuable-adapter INTERFACE variant-adapter )

if( NOT is_subproject )
    enable_testing() 
    if ( unit_tests )
        add_subdirectory( src/knoop/Node/test )
    endif() 
endif()

install( DIRECTORY src// DESTINATION include
         FILE_PERMISSIONS OWNER_READ OWNER_WRITE 
                          GROUP_READ 
                          WORLD_READ
         DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE 
                               GROUP_READ 
                               WORLD_READ
         FILES_MATCHING REGEX ".*\.h[+][+]$|.*\.hxx$|.*\.hpp$|.*\.hh$|.*\.h$"  )

                    INCLUDE(CPack)
                    