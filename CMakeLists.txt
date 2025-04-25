cmake_minimum_required(VERSION 3.5.0)
project(containers VERSION 1.0.0 LANGUAGES C CXX)

set(PROJECT_NAME
    Containers
)


# Download and build googletest
# @see https://github.com/google/googletest/blob/master/googletest/README.md
# Incorporating Into An Existing CMake Project

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)
# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()



project(${PROJECT_NAME})

# Main target
add_executable(${PROJECT_NAME} 
                src/main.cpp
                )

# Test target
add_executable(
    test_serial_container
    test/test_serial_container.cpp
)


# Add src to the include directories for the test target
target_include_directories(
  test_serial_container PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/libs"
)

# Link test target against gtest libraries
target_link_libraries(
  test_serial_container PRIVATE
    gtest gtest_main
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(test_serial_container PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(
      test_serial_container PRIVATE
        /W4
    )
    target_compile_options(
      test_serial_container PRIVATE
        /W4
    )
else ()
    target_compile_options(
        ${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
      test_serial_container PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()