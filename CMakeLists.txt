cmake_minimum_required(VERSION 3.10.0)
project(matrix_matrix)

find_package(PkgConfig REQUIRED )
pkg_check_modules(tesseract REQUIRED IMPORTED_TARGET tesseract lept)

add_executable(matrix_test Test.cpp functions.cpp)
add_executable(matrix matrix_read.cpp functions.cpp)
target_link_libraries(matrix_test PUBLIC -static default PkgConfig::tesseract)
target_link_libraries(matrix PUBLIC default PkgConfig::tesseract)
enable_testing()
add_test(matrix_test matrix_test)
#catch_discover_tests(matrix_test)