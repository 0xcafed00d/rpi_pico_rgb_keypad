cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(rgb_keypad C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(lib/pico_rgb_keypad)

add_executable(
	${CMAKE_PROJECT_NAME}
	src/main.cpp
	src/led.cpp
	src/usb_descriptors.cpp
)

# Make sure TinyUSB can find tusb_config.h
target_include_directories(
	${CMAKE_PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/src
)

if("${PICO_BOARD}" MATCHES "pico_w")
	target_link_libraries(${CMAKE_PROJECT_NAME}
		pico_stdlib
		pico_rgb_keypad
		pico_cyw43_arch_none
		tinyusb_device
		tinyusb_board)
else()
	target_link_libraries(${CMAKE_PROJECT_NAME}
		pico_stdlib
		pico_rgb_keypad
		tinyusb_device
		tinyusb_board)
endif()

pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)

# pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 1)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})
