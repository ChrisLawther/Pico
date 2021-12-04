cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PicoTinkering)

pico_sdk_init()

add_subdirectory (lib)
add_subdirectory (apps)

