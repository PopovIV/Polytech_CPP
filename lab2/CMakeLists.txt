# CMakeList.txt: проект CMake для calculator; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("calculator")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (calculator "calculator.cpp" "calculator.h" "token.h" "token.cpp" "parser.h" "parser.cpp" "eval.h" "eval.cpp" "function.h" "function.cpp" "functionLoader.h" "functionLoader.cpp" "main.cpp")


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/expressions.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/answers.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/out.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
add_subdirectory("DLLs CODE")