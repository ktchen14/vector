if (NOT BUILD_TESTING)
  return()
endif ()
cmake_minimum_required(VERSION 3.13) # target_link_options()

option(CODE_COVERAGE "Generate code coverage report" OFF)

# Define malloc, realloc, and free to stub_malloc, stub_realloc, and stub_free
# in a target that links to the stub.
add_library(stub SHARED EXCLUDE_FROM_ALL stub.c)
target_compile_definitions(stub INTERFACE
  malloc=stub_malloc realloc=stub_realloc free=stub_free)

define_vector_target(vector_test SHARED EXCLUDE_FROM_ALL)
target_compile_definitions(vector_test PUBLIC __vector_inline__=)
target_compile_options(vector_test PUBLIC -Wall -Wextra -Werror)
target_link_libraries(vector_test PRIVATE stub)

# On macOS with `dyld`: Alters how symbols are resolved at build time and
# runtime. With -flat_namespace, the linker searches all dylibs on the command
# line and all dylibs those original dylibs depend on. The linker does not
# record which dylib an external symbol came from, so at runtime dyld again
# searches all images and uses the first definition it finds.
include(CheckLinkerFlag)
check_linker_flag(-flat_namespace FLAT_NAMESPACE_FLAG)
if (FLAT_NAMESPACE_FLAG)
  target_link_options(vector_test PRIVATE -flat_namespace)
endif ()

# Add the --coverage option if code coverage is on
if (CODE_COVERAGE)
  target_compile_options(vector_test PRIVATE --coverage)
  target_link_options(vector_test PUBLIC --coverage)
endif ()

function(define_test name)
  add_executable("test_${name}" EXCLUDE_FROM_ALL test.h "${name}.c")
  # The _GNU_SOURCE feature test macro must be defined in order to obtain the
  # definitions of RTLD_DEFAULT and RTLD_NEXT from <dlfcn.h>.
  target_compile_definitions("test_${name}" PRIVATE _GNU_SOURCE)
  target_link_libraries("test_${name}" PRIVATE dl vector_test)
  add_test(NAME "${name}" COMMAND "${CMAKE_CTEST_COMMAND}"
    --build-and-test "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}"
    --build-generator "${CMAKE_GENERATOR}"
    --build-target "test_${name}" --build-nocmake --build-noclean
    --test-command "$<TARGET_FILE:test_${name}>")
endfunction(define_test)

function(define_veto name regexp)
  add_executable("test_${name}" EXCLUDE_FROM_ALL test.h "${name}.c")
  target_link_libraries("test_${name}" PRIVATE vector_test)
  add_test(NAME "test_${name}" COMMAND "${CMAKE_COMMAND}"
    --build "${CMAKE_BINARY_DIR}" --config "$<CONFIG>" --target "test_${name}")
  set_property(TEST "test_${name}" PROPERTY PASS_REGULAR_EXPRESSION "${regexp}")
endfunction(define_veto)

include(TestVector.cmake)
