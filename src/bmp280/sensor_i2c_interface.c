#include "sensor_i2c_interface.h"

/*
 * Adaptation of the sensor library Linux example.
 */

static int BMP280_file_descriptor_;
static const char* bus_address_;

void set_bus_address(const char* bus_address)
{
    bus_address_ = bus_address;
}

/*initiates the I2C peripheral and sets its speed*/
int bmp280_i2c_init(uint8_t device_address)
{
	BMP280_file_descriptor_ = open(bus_address_, O_RDWR);
	if(BMP280_file_descriptor_ < 0)
	{
		perror("ERROR OPENING I2C BUS");
		return 1;
	}

	if(ioctl(BMP280_file_descriptor_, I2C_SLAVE, device_address) < 0)
	{
		perror("ERROR IN ACQUIRING BUS ACCESS");
		close(BMP280_file_descriptor_);
		return 2;
	}

	return 0;
}

/*initiates the I2C peripheral and sets its speed*/
int bmp280_i2c_deinit(uint8_t deviceAddress)
{
	close(BMP280_file_descriptor_);

	return 0;
}


/*writes an array (data[]) of arbitrary size (dataLength) to I2C address (deviceAddress), starting from an internal register address (startRegisterAddress)*/
int bmp280_write_array(uint8_t deviceAddress, uint8_t startRegisterAddress, uint8_t *data, uint8_t dataLength)
{
	uint8_t buffer[dataLength + 1];
	buffer[0] = startRegisterAddress;
	memcpy(&buffer[1], data, dataLength);

	if(write(BMP280_file_descriptor_, buffer, dataLength + 1) != dataLength + 1)
	{
		perror("ERROR IN I2C WRITE");
		close(BMP280_file_descriptor_);
		return 1;
	}

	return 0;
}

/*reads an array (data[]) of arbitrary size (dataLength) from I2C address (deviceAddress), starting from an internal register address (startRegisterAddress)*/
int bmp280_read_array(uint8_t deviceAddress, uint8_t startRegisterAddress, uint8_t *data, uint8_t dataLength)
{
	if(write(BMP280_file_descriptor_, (void *)&startRegisterAddress, 1) != 1)
	{
		perror("ERROR IN I2C WRITE");
		close(BMP280_file_descriptor_);
		return 1;
	}

	if(read(BMP280_file_descriptor_, (void *)data, dataLength) != dataLength)
	{
		perror("ERROR IN I2C READ");
		close(BMP280_file_descriptor_);
		return 2;
	}

	return 0;
}

/*a delay function for milliseconds delay*/
int delay_function(uint32_t delayMS)
{
	if(usleep(1000 * delayMS) != 0)
	{
		return 1;
	}

	return 0;
}

/*implements a power function (used in altitude calculation)*/
int power_function(float x, float y, float *result)
{
	*result = pow(x,y);

	return 0;
}
