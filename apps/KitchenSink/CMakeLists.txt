cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(KitchenSink)

pico_sdk_init()

include_directories(../../lib)

add_executable(${PROJECT_NAME}
    main.cpp
    ../../lib/gyro/mpu6050.cpp
    ../../lib/temperature/onBoardTemperature.cpp
)

# Disable serial UART, enable USB out
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_adc hardware_i2c)