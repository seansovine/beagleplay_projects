# BeaglePlay projects

This contains projects using the BeaglePlay single-board Arm Linux computer.

## Development workflow

We're currently compiling directly on the board, and this will probably work for our applications.
We have made a start at setting up a nice cross-compilation environment, which would let us use
more powerful tools than we might want to run on the board, like Clangd. However, the board does
support the VS Code remote development server just fine.

To make cross-compilation work we'll need to get or build a cross toolchain with a glibc version
compatible with the one in the board's OS. One of those is available [here](https://github.com/AmanoTeam/obggcc).

To build and test on the board you can run:

```shell
# If needed.
git submodule update --init --recursive

make configure
make build

# Test sensor connection.
make i2c

# Run driver library example program.
make example

# Run the main program.
make run
```
## Reading sensor data

The [`bmp280_read`](src/bmp280/bmp280_read.c) program that is currently built is an adaptation of the
Linux example program from the C library mentioned below. It connects to the sensor over the I2C bus
that's wired to the board's Grove connector, and reads temperature and barometric pressure readings
from it once per second.

Eventually, I plan to add a TCP server to this, so that other machines on the local network can connect
and get readings from the sensor. Though the temperature readings are an interesting test of the home
HVAC system, this is mainly a test case for using the BeaglePlay and similar single-board computers to
interface with sensors and other lower-level hardware devices. More interesting projects could later use
a similar approach for interfacing with cameras, say, or for applications in robotics.

## Third-party sensor library

We're currently using the nice BMP280 C library available
[here](https://github.com/ebrezadev/BMP280-Barometric-Pressure-and-Temperature-Sensor-C-Driver)
for interfacing with the sensor. Our CMake project builds this library and also its Linux example
program.
