cmake_minimum_required(VERSION 3.31)
project(retangulosCli C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-pedantic -Wall -Wextra)

add_executable(retangulosCli main.c retangulos.c mundo.c)
