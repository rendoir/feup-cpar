.PHONY: default build clean

default: build

build:
	g++ -std=c++17 -O3 main.cpp -o mult -lpapi

debug: 
	g++ -std=c++17 -ggdb3 main.cpp -o mult -lpapi

setup:
	sudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'

clean:
	rm -rf mult
