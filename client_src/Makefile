.DEFAULT_GOAL := all

build: clean
	mkdir build && \
	cd build && \
	cmake .. && \
	make install -j 4

compile:
	cd build && \
	cmake .. && \
	make install -j 4

run: compile
	cd build && \
	./wolfenstein3d-client

all: build
	cd build && \
	./wolfenstein3d-client

clean:
	rm -rf build

clean-all:
	rm -rf build
	rm -rf maps
	rm -rf config