cmake_minimum_required(VERSION 3.10)
project(AppLogger)

set (CXX_STANDARD_REQUIRED 17)
# target_compile_options(AppLogger PRIVATE cxx_std_17)
if (CMAKE_COMPILER_IS_GNUCXX)
    # Enable all warnings and treat them as errors
    add_compile_options(-Wall -Werror -Wextra -Wpedantic)
endif()

if (MSVC)
    # /W4 Warning level 4
    # /MD Multithreaded library will be used to link against GTest
    add_compile_options(/W4 /MD)
endif()

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
set(gtest_force_shared_crt ON CACHE BOOL TRUE FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_executable(AppLogger src/FileOutput.cpp src/ConsoleOutput.cpp src/TaskManager.cpp src/main.cpp)

project(LoggerTest)

# Test Files
set(TEST_FILES src/FileOutput.cpp src/ConsoleOutput.cpp src/TaskManager.cpp tests/test_task_manager.cpp tests/test_logger.cpp)

add_executable(Unit_Tests ${TEST_FILES})
target_link_libraries(Unit_Tests gtest_main)
