# Wrapper to build library from BMP280 driver code.

file(GLOB BMP280_DRIVER_SOURCE CONFIGURE_DEPENDS "./bmp280-driver/src/*.c")
file(GLOB BMP280_DRIVER_HEADERS CONFIGURE_DEPENDS "./bmp280-driver/inc/*.h")

add_library(bmp280_driver STATIC ${BMP280_DRIVER_SOURCE} ${BMP280_DRIVER_HEADERS})

target_include_directories(bmp280_driver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/bmp280-driver/inc")

set(
    EXAMPLE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/bmp280-driver/example/linux/main.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/bmp280-driver/example/linux/interface.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/bmp280-driver/example/linux/interface.c"
)

add_executable(bmp280_example ${EXAMPLE_SOURCES})
target_link_libraries(bmp280_example PRIVATE bmp280_driver m)
