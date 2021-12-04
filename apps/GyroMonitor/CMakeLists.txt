cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(temperatureMonitor)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.cpp
    onBoardTemperature.cpp
    mpu6050.cpp
)

# Disable serial UART, enable USB out
pico_enable_stdio_usb(temperatureMonitor 1)
pico_enable_stdio_uart(temperatureMonitor 0)

pico_add_extra_outputs(temperatureMonitor)

target_link_libraries(temperatureMonitor pico_stdlib hardware_adc hardware_i2c)
