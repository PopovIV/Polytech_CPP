cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../out/build/x64-Debug/DLLs)



project ("MathLibrary")
add_library(MathLibrary SHARED "MathLibrary.cpp" "../../function.cpp")