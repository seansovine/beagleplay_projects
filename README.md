# BeaglePlay projects

Currently this contains a project with an example of connecting to a BMP280 temperature
and humidity sensor over the Grove I2C port and simply reading its device id. It's a 
simple program but we can expand out from there.

We're currently compiling directly on the board, and this will probably work for our 
applications, though we made a start at setting up a nice cross-compilation environment,
which lets us use more powerful tools like VS Code and Clangd. To make this work we'll 
need to get or build a cross toolchain with the same glibc version as the board. There
seems to be one of those available [here](https://github.com/AmanoTeam/obggcc).

Next we want to start reading the temperature values from the sensor and try to make 
them available to other machines on the network, maybe over TCP/IP. For interfacing with
the sensor effectively we can use 
[this](https://github.com/ebrezadev/BMP280-Barometric-Pressure-and-Temperature-Sensor-C-Driver)
C library for that purpose.
