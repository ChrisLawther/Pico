cmake_minimum_required(VERSION 3.12)

# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_executable (KitchenSink main.cpp)

target_link_libraries(KitchenSink Gyro Temperature)

# Disable serial UART, enable USB out
pico_enable_stdio_usb(KitchenSink 1)
pico_enable_stdio_uart(KitchenSink 0)

pico_add_extra_outputs(KitchenSink)


