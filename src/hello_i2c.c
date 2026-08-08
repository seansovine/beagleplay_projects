#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS_FILE     "/dev/i2c-1"
#define BMP280_ADDRESS   0x76
#define REG_CHIP_ID      0xD0
#define REG_TEMP_MSB     0xFA

static int file_desc;
static uint8_t write_buf[2];
static uint8_t read_buf[3];

int setup_i2c()
{
    if ((file_desc = open(I2C_BUS_FILE, O_RDWR)) < 0)
    {
        perror("Error: Failed to open the I2C bus");
        return EXIT_FAILURE;
    }

    if (ioctl(file_desc, I2C_SLAVE, BMP280_ADDRESS) < 0)
    {
        perror("Error: Failed to communicate with slave device");
        close(file_desc);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int read_temp_raw()
{
    static uint8_t raw_data_buf[3] = {0};

    uint8_t data_reg = REG_TEMP_MSB;
    if (write(file_desc, &data_reg, 1) != 1 || read(file_desc, raw_data_buf, 3) != 3)
    {
        perror("Failed to read raw temperature data");
        return EXIT_FAILURE;
    }

    printf("Raw data: %02hhx %02hhx %02hhx\n", raw_data_buf[0], raw_data_buf[1], raw_data_buf[2]);
    return EXIT_SUCCESS;
}

int handle_failure()
{
    close(file_desc);
    return EXIT_FAILURE;
}

int main() {
    uint8_t reg_addr;

    if(setup_i2c())
    {
        return EXIT_FAILURE;
    }

    reg_addr = REG_CHIP_ID;
    if (write(file_desc, &reg_addr, 1) != 1)
    {
        perror("Error: Writing to ID register failed");
        return handle_failure();
    }

    if (read(file_desc, read_buf, 1) != 1)
    {
        perror("Error: Reading chip ID failed");
        return handle_failure();
    }
    else
    {
        printf("BMP280 detected! Chip ID: 0x%02X (Expected: 0x58)\n", read_buf[0]);
    }

    // TODO: Need to configure sensor and get calibration data.

    // Read raw temp data twice.
    if (read_temp_raw() || read_temp_raw())
    {
        return handle_failure();
    }

    // TODO: Need to convert raw data to calibrarted floating point.

    close(file_desc);
    return EXIT_SUCCESS;
}

