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

int main() {
    int file_desc;
    uint8_t write_buf[2];
    uint8_t read_buf[3];
    uint8_t reg_addr;

    if ((file_desc = open(I2C_BUS_FILE, O_RDWR)) < 0) {
        perror("Error: Failed to open the I2C bus");
        return EXIT_FAILURE;
    }

    if (ioctl(file_desc, I2C_SLAVE, BMP280_ADDRESS) < 0) {
        perror("Error: Failed to communicate with slave device");
        close(file_desc);
        return EXIT_FAILURE;
    }

    reg_addr = REG_CHIP_ID;
    if (write(file_desc, &reg_addr, 1) != 1) {
        perror("Error: Writing to ID register failed");
    }
    if (read(file_desc, read_buf, 1) != 1) {
        perror("Error: Reading chip ID failed");
    } else {
        printf("BMP280 detected! Chip ID: 0x%02X (Expected: 0x58)\n", read_buf[0]);
    }

    close(file_desc);
    return EXIT_SUCCESS;
}

