# Install dev tools:

https://aricodes.net/posts/picoprobe-dap-init-failed/

## Mac prereqs

Install cmake and other build tools

```
brew install libtool automake texinfo wget gcc pkg-config libusb
```

Install

```
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc
```

## To set up...

Make a build directory and build

```
mkdir build
cd build
cmake .. && make -j4
```
