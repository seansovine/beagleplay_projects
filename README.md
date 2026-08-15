# BeaglePlay projects

This repository contains projects using the BeaglePlay single board Arm Linux computer.

## Demos

__* `src/demos/hello_i2c.c`__

This is a basic example of connecting to a BMP280 temperature and atmospheric pressure sensor
that is connected to the I2C bus that's wired to the Grove port, which is `/dev/i2c-1`. It
simply reads the sensor's device id to confirm the connection. It's a simple program but we can
expand out from here using the specific APIs of the sensor.

## Workflow

We're currently compiling directly on the board, and this will probably work for our applications.
Though, we've made a start at setting up a nice cross-compilation environment, which would let us use
more powerful tools than we might want to run on the board, like Clangd.

To make cross-compilation work we'll need to get or build a cross toolchain with the same glibc
version as on the board. There seems to be a nice one of those available
[here](https://github.com/AmanoTeam/obggcc).

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
```

## Next steps

Next we want to start reading the temperature values from the sensor and make them available
to other machines on the local Wifi network, maybe using a simple TCP/IP server. We could then
make various kinds of client programs to query and use data from the server. And, this same basic
model can be used for other kinds of sensors that we can iterface through the board.

Our initial implementation will use the nice "BMP280 Barometric Pressure and Temperature Sensor C Driver"
library  available [here](https://github.com/ebrezadev/BMP280-Barometric-Pressure-and-Temperature-Sensor-C-Driver)
for interfacing with the sensor. This library has been added as a submodule to this repo at
`thirdparty/bmp280-driver`, and we're building the library and its Linux example program as part
of the CMake project.

You can run the library example from the Makefile, as noted above.
