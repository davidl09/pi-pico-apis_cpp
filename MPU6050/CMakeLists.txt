cmake_minimum_required(VERSION 3.22)

include(pico_sdk_import.cmake)

project(MPU6050 C CXX ASM)

include_directories(~/pico/pico-apis-cpp)

pico_sdk_init()

add_executable(MPU6050 test.cpp)
pico_enable_stdio_usb(MPU6050 1)
pico_enable_stdio_uart(MPU6050 0)
pico_add_extra_outputs(MPU6050)
target_link_libraries(MPU6050 pico_stdlib hardware_i2c)
