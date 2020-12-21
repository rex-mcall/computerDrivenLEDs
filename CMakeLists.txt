cmake_minimum_required(VERSION 3.13)

# set the project name
project(UART_LEDs)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES uartLEDs.cpp)
add_executable(uartLEDs ${SOURCE_FILES})