# CMAKE header.
cmake_minimum_required(VERSION 3.13.4)
project(LLVM-Lab)

# Set binary output destination.
set(BINARY_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})

# Include project sources.
include_directories("src")
include_directories("/usr/include")
add_compile_options(-std=c++17 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.c")

# Get LLVM linker flags.
execute_process(COMMAND llvm-config --ldflags --system-libs --libs all OUTPUT_VARIABLE LLVM_FLAGS)

# Get rid of whitespace and replace newlines with spaces.
string(STRIP ${LLVM_FLAGS} LLVM_FLAGS)
string(REPLACE "\n" " " LLVM_FLAGS  ${LLVM_FLAGS})

# Finally link the program with LLVM.
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} "${LLVM_FLAGS}")
