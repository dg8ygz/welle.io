# Building welle.io

Choose the [branch](../README.md#fork-branches) before building. Commands below
run from its repository root. CMake builds both GUI and CLI by default.

## Linux CLI

For a Debian/Ubuntu CLI build with RTL-SDR:

```sh
sudo apt install git cmake build-essential libfaad-dev libmpg123-dev \
  libfftw3-dev librtlsdr-dev libusb-1.0-0-dev libmp3lame-dev libasound2-dev

git clone https://github.com/dg8ygz/welle.io.git
cd welle.io
cmake -S . -B build -DBUILD_WELLE_IO=OFF -DRTLSDR=ON
cmake --build build --parallel
./build/welle-cli -h
```

To build the combined receiver changes, run `git switch dg8ygz/receiver-fixes`
after cloning and before configuring. Its validation notes apply to that branch.
The CLI does not require Qt. An optional system-wide installation is
`sudo cmake --install build`; running from `build/` does not require installation.

## GUI and Windows

The source documentation targets Qt 6.8 or newer with Quick/QML, Quick Controls,
Widgets, Charts and Multimedia. Install Qt and the required native libraries,
then open `CMakeLists.txt` in Qt Creator or configure a separate build:

```sh
cmake -S . -B build-gui -DRTLSDR=ON
cmake --build build-gui --parallel
```

If CMake cannot find a separately installed Qt, set `CMAKE_PREFIX_PATH` to its
installation directory. Linux GUI builds also use Qt DBus.
For Windows, use the matching Qt/compiler kit and the
[upstream Windows libraries](https://github.com/AlbrechtL/welle.io-win-libs).

## CMake

| Option | Purpose |
|---|---|
| `-DBUILD_WELLE_IO=OFF` | CLI only |
| `-DBUILD_WELLE_CLI=OFF` | GUI only |
| `-DRTLSDR=ON` | RTL-SDR backend; requires librtlsdr |
| `-DSOAPYSDR=ON` | SoapySDR backend; requires its library and a driver for the device |
| `-DAIRSPY=ON` | Airspy backend; requires libairspy |
| `-DFLAC=ON` | FLAC streaming; requires libFLAC++ |
| `-DKISS_FFT=ON` | KISS FFT instead of FFTW |
| `-DPROFILING=ON` | CPU profiling output |

Options and dependencies are defined in [CMakeLists.txt](../CMakeLists.txt).
Use separate build directories when comparing backend or GUI configurations.

## Other platforms

The inherited macOS, Android and FreeBSD instructions are
[historical upstream documentation](https://github.com/AlbrechtL/welle.io/blob/fdcd3c588a6e592b9640aad71648dcf6228fa98f/README.md).
They are not a validation of this fork on those platforms.
