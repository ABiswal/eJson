# eJson Library



eJson Library is a light weight library which provides parsing for JSON 
like file.

## Folder Structure


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

## Build Instruction


This libary uses cmake and conan environment for the builds of different
targets. The environment is maintained by poetry.

### Steps

1. create python3 venv inside work

``` $python3 -m venv venv ```

2. install poetry

``` $./venv/bin/pip install poetry ```

3. activate environment

``` $source ./venv/bin/activate ```

4. activate poetry shell

``` $poetry shell ```

5. Build for a target
   - Linux x86_64 (ubuntu)
      - use command (from eJson root)

        ``` $make build_linux ```

   - armv7 (*not tested)
      - use command (from eJson root)

         ``` $make build_arm ```

To clean the previous outputs , use 

   ``` $make clean ```

## Tests
### unittests


This project uses GoogleTest(gtest) framework for the unittesting of the code.

It is assumed that steps 1 to 5 for builds has been performed as a prerequisite.

To run the unittests , use command listed below (from eJson root)

``` $make unittests ```

To clean the previous outputs , use 

``` $make clean ```

## API Usage

This library provides a wrapper and extends the API provided by jsont library.

### Class eJsonTokenizer

Creates a Tockenizer object from a eJson file.

e.g:

```
  eJson::eJsonTokenizer E("test.eJson");
  jsont::Token tok;
  tok=E.tockenizer.next();
  // tok contains the token value
  if (tok == eJson::jsont::Error){
      // handle error
  }

```

#### Reading tokens

- `const Token& next() throw(Error)` — Read next token, possibly throwing an `Error`
- `const Token& current() const` — Access current token

#### Reading values

- `bool hasValue() const` — True if the current token has a value
- `size_t dataValue(const char const** bytes)` — Returns a slice of the input which represents the current value, or nothing (returns 0) if the current token has no value (e.g. start of an object).
- `std::string stringValue() const` — Returns a *copy* of the current string value.
- `double floatValue() const` — Returns the current value as a double-precision floating-point number.
- `int64_t intValue() const` — Returns the current value as a signed 64-bit integer.

#### Handling errors

- `ErrorCode error() const` — Returns the error code of the last error
- `const char* errorMessage() const` — Returns a human-readable message for the last error. Never returns NULL.



## Miscellaneous



## Contacts

Achyutananda Biswal: greatANB@gmail.com
