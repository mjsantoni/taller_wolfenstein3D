ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

.DEFAULT_GOAL := build

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
	./wolfenstein3d-server $(RUN_ARGS)

clean:
	rm -rf build

clean-all:
	rm -rf build
	rm -rf maps
	rm -rf config