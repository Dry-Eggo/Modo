
all: build

build:
	@cmake --build build

run: build
	@build/modo $(a)

.PHONY: run build
