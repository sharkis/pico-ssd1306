cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(pico_oled)
pico_sdk_init()

add_executable(oled
	oled.c
	ssd1306.c
)

target_link_libraries(oled pico_stdlib hardware_i2c )

pico_add_extra_outputs(oled)

