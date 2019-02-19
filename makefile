.PHONY: default build clean

default: build

build:
	g++ -O3 main.cpp -o mult -lpapi

clean:
	rm -rf mult
