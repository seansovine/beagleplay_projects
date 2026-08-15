.PHONY: configure build clean run

configure:
	cmake -B build -S .

build:
	cmake --build build

clean:
	rm -rf build/*

hello:
	@build/hello

i2c:
	@build/i2c
