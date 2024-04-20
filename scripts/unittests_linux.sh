	mkdir ./work/unittests
	cd ./tests/unittests
	conan install . --output-folder=../../work/unittests  --build=missing --profile=../../data/conan/profiles/linux_x86_64.conf
	cd ../../work/unittests
	cmake ../../tests/unittests/ -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
	cmake --build .
	ctest