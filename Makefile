.PHONY: configure build clean run

configure:
	cmake -B build -S .

build:
	cmake --build build

clean:
	rm -rf build/*

i2c:
	@build/bmp280_i2c_test

run:
	@build/bmp280_read

example:
	@build/thirdparty/bmp280_example
