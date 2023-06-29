cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(lcd1602 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()
add_executable(lcd1602 test.cpp)
pico_enable_stdio_usb(lcd1602 1)
pico_enable_stdio_uart(lcd1602 0)
pico_add_extra_outputs(lcd1602)
target_link_libraries(lcd1602 pico_stdlib hardware_i2c)

