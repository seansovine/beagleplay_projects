# BMP280 data server.
add_executable(bmp280_read bmp280_read.c sensor_i2c_interface.c)
target_link_libraries(bmp280_read PRIVATE bmp280_driver m)
