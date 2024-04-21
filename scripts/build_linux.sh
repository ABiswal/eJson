	#!/bin/sh
    workspace=$PWD
    mkdir $workspace/work/build_linux
	conan install . --output-folder=./work/build_linux  --build=missing --profile=./data/conan/profiles/linux_x86_64.conf
	cd ./work/build_linux
	cmake ./../.. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
	cmake --build .