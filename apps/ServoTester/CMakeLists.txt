cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(ServoController)

pico_sdk_init()

add_executable(ServoController
    controller.cpp
    servo.cpp
    servo_controller.cpp
)

# Disable serial UART, enable USB out
pico_enable_stdio_usb(ServoController 1)
pico_enable_stdio_uart(ServoController 0)

pico_add_extra_outputs(ServoController)

target_link_libraries(ServoController pico_stdlib hardware_pwm)
