#eJson Library
===========================


eJson Library is a light weight library which provides parsing for JSON 
like file.

##Folder Structure
------------

```
eJson
   |-- data                      Contains configuration data e.g. conan  profiles
   |-- include                   Contains the header files
   |-- scripts                   contains the scripts used for build, test, etc.
   |-- scr                       Contains the source files
   |-- tests                     Contains Tests related files
   |     |--unittests            Contains Unit Tests
   |         |--conanfile.py     Configuration for Conan used for unittests
   |-- work                      Is used for various work such as build, test etc.
   |-- CMakeLists.txt            High Level CMake configuration
   |-- conanfile.py              Configuration for Conan used for builds
   |-- pyproject.toml            Configuration for poetry 
   |-- README.rst                Information about various things
```

##Build Instruction
------------

This libary uses cmake and conan environment for the builds of different
targets. The environment is maintained by poetry.

###Steps
-----
1. create python3 venv inside work
$python3 -m venv venv

2. install poetry
$./venv/bin/pip install poetry

3. activate environment
$source ./venv/bin/activate

4. activate poetry shell
$poetry shell

5. Build for a target
   - Linux x86_64 (ubuntu)
      - use command (from eJson root)
        $make build_linux
   - armv7 (*not tested)
      - use command (from eJson root)
         $make build_arm 

To clean the previous outputs , use 

$make clean


##unittests
--------

This project uses GoogleTest(gtest) framework for the unittesting of the code.

It is assumed that steps 1 to 5 for builds has been performed as a prerequisite.

To run the unittests , use command listed below (from eJson root)

$make unittests 

To clean the previous outputs , use 

$make clean

##Usage
-----



#Miscellaneous
~~~~~~~~~~~~~


#Contacts
---------
Achyutananda Biswal: greatANB@gmail.com
