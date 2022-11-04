cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)


# Rename your project
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Disable if not pico w
set(PICO_BOARD pico_w)

pico_sdk_init()

add_executable(test
    main.cpp
)

# Rename your binary
pico_enable_stdio_usb(test 0)
pico_enable_stdio_uart(test 1)
pico_add_extra_outputs(test)

target_include_directories(test PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(test pico_cyw43_arch_lwip_threadsafe_background pico_stdlib)