/*
 * This is currently a slight adaptation of the sensor library Linux example.
 *
 * Eventually it will run a TCP/IP server that allows clients to connect and
 * query for sensor readings.
 */

#include <bmp280.h>

#include "sensor_i2c_interface.h"

#include <stdio.h>

#define CHECK_RESULT(error)               \
    do                                              \
    {                                               \
        if (error != BMP280_ERROR_OK)               \
        {                                           \
            printf("ERROR CODE: %d\n", (int)error); \
            return (int)error;                      \
        }                                           \
    } while (0)

int main(int arg, char *argv[])
{
    bmp280_handle_t BMP280;
    bmp280_sensors_data_t sensorsData;

    BMP280.dependency_interface.bmp280_interface_init = bmp280_i2c_init;
    BMP280.dependency_interface.bmp280_interface_deinit = bmp280_i2c_deinit;
    BMP280.dependency_interface.bmp280_write_array = bmp280_write_array;
    BMP280.dependency_interface.bmp280_read_array = bmp280_read_array;
    BMP280.dependency_interface.bmp280_delay_function = delay_function;
    BMP280.dependency_interface.bmp280_power_function = power_function;

    // I2C bus of Grover connnector on BeaglePlay board.
    static const char * bus_address = "/dev/i2c-1";
    set_bus_address(bus_address);

    printf("Initializing sensor using i2c...\n");
    CHECK_RESULT(bmp280_init(&BMP280, BMP280_I2C, BMP280_I2C_ADDRESS_1));

    printf("Setting sensor mode...\n");
    CHECK_RESULT(bmp280_set_mode(&BMP280, BMP280_MODE_NORMAL));
    CHECK_RESULT(bmp280_set_temperature_oversampling(&BMP280, BMP280_OVERSAMPLING_4X));
    CHECK_RESULT(bmp280_set_pressure_oversampling(&BMP280, BMP280_OVERSAMPLING_16X));
    CHECK_RESULT(bmp280_set_standby_time(&BMP280, BMP280_T_STANDBY_250MS));
    CHECK_RESULT(bmp280_set_filter_coefficient(&BMP280, BMP280_FILTER_16X));

    printf("Reading from sensor...\n");
    for (;;)
    {
        CHECK_RESULT(bmp280_get_all(&BMP280, &sensorsData));
        CHECK_RESULT(bmp280_calculate_altitude_quick(&BMP280, &sensorsData.altitude, sensorsData.pressure));

        float temp_f = 9.0 * sensorsData.temperature / 5.0 + 32.0;
        printf("TEMP: %.2f °C (%.2f °F), PRESSURE: %d Pa, ALTITUDE: %.1f m\n",
            sensorsData.temperature, temp_f, sensorsData.pressure, sensorsData.altitude);

        sleep(1);
    }

    return 0;
}
