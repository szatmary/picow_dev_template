cmake_minimum_required(VERSION 3.13)


set(PICO_BOARD pico_w)
set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

include(FetchContent)
FetchContent_Declare(
  freertos
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG  V10.5.1
)
FetchContent_Populate(freertos)
add_subdirectory("${freertos_SOURCE_DIR}/portable/ThirdParty/GCC/RP2040" FreeRTOS-Kernel)

# Set this to your projects name
set(NAME test)
project(${NAME}_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()
add_executable(${NAME}
    src/main.cpp
)

pico_enable_stdio_usb(${NAME} 0)
pico_enable_stdio_uart(${NAME} 1)
pico_add_extra_outputs(${NAME})

target_include_directories(${NAME} PRIVATE
    "${freertos_SOURCE_DIR}/include"
    "${freertos_SOURCE_DIR}/portable/ThirdParty/GCC/RP2040/include/"
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${NAME} PRIVATE
    pico_stdlib
    # pico_cyw43_arch_lwip_threadsafe_background
    pico_cyw43_arch_lwip_sys_freertos
    FreeRTOS-Kernel-Heap4
)