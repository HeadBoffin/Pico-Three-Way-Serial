# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "../../../pico-sdk")

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Pico-Three-Way-Serial C CXX)

# Initialise the Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Pico-Three-Way-Serial Pico-Three-Way-Serial.cpp )

pico_set_program_name(Pico-Three-Way-Serial "Pico-Three-Way-Serial")
pico_set_program_version(Pico-Three-Way-Serial "0.1")

pico_enable_stdio_usb(Pico-Three-Way-Serial 1)
pico_enable_stdio_uart(Pico-Three-Way-Serial 0)

# Add the standard library to the build
target_link_libraries(Pico-Three-Way-Serial pico_stdlib)

# Add any user requested libraries
target_link_libraries(Pico-Three-Way-Serial
        pico_stdlib
)

pico_add_extra_outputs(Pico-Three-Way-Serial)

