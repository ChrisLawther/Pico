cmake_minimum_required(VERSION 3.12)

# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (Temperature onBoardTemperature.cpp)

target_link_libraries(Temperature pico_stdlib hardware_adc hardware_i2c)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (Temperature PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

