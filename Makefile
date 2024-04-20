SHELL=/bin/bash
workspace=.
.oneshell:

.phony: all clean

all: build_linux unittests

build_arm:

build_linux:
	source ${PWD}/scripts/build_linux.sh
unittests:
	source $(PWD)/scripts/unittests_linux.sh


clean:
	rm -rf ./work/build_linux/
	rm -rf ./work/unittests/
