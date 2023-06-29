cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(I2C_master C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()
add_executable(I2C_master main.cpp)
pico_enable_stdio_usb(I2C_master 1)
pico_enable_stdio_uart(I2C_master 0)
pico_add_extra_outputs(I2C_master)
target_link_libraries(I2C_master pico_stdlib hardware_i2c)

