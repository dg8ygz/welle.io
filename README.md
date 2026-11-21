# welle.io — dg8ygz fork

DAB/DAB+ software radio with a Qt interface and a command-line receiver,
including a web interface for service information and audio streaming.
Based on [AlbrechtL/welle.io](https://github.com/AlbrechtL/welle.io).

## Fork branches

| Branch | Purpose |
|---|---|
| `master` | Upstream-based source; receiver fixes below are maintained separately |
| [`dg8ygz/receiver-fixes`](https://github.com/dg8ygz/welle.io/tree/dg8ygz/receiver-fixes) | Combined receiver work, regression tests and validation notes |
| `dg8ygz/*-next` | Separate development branches; inspect their diffs before use |

Details for the combined branch: [receiver changes](https://github.com/dg8ygz/welle.io/blob/dg8ygz/receiver-fixes/docs/receiver-fixes.md)
and [validation](https://github.com/dg8ygz/welle.io/blob/dg8ygz/receiver-fixes/docs/test-validation.md).
Upstream packages do not necessarily contain these changes.

## Build and use

- [Build instructions](docs/building.md): Linux/Windows, CMake and optional SDR backends.
- [Usage](docs/usage.md): GUI controls, command-line reception and streaming.
- [Supported hardware](docs/hardware.md): RTL-SDR, Airspy, SoapySDR and recorded I/Q.
- [Upstream downloads](https://github.com/AlbrechtL/welle.io/releases) and [user documentation](https://www.welle.io).

CLI-only CMake build, after installing the dependencies in the build guide:

```sh
cmake -S . -B build -DBUILD_WELLE_IO=OFF -DRTLSDR=ON
cmake --build build --parallel
./build/welle-cli -c 12A -w 7979
```

Open `http://localhost:7979/`. Select a DAB channel available at your location;
`12A` is an example. Build the GUI with Qt instead if desktop playback is preferred.

## Development

Fork-specific issues: [dg8ygz/welle.io](https://github.com/dg8ygz/welle.io/issues).
Upstream development: [AlbrechtL/welle.io](https://github.com/AlbrechtL/welle.io).
For profiling, build with `-DPROFILING=ON`; output includes CSV files and
`profiling.dot`, which Graphviz can render with `dot -Tpdf profiling.dot > profiling.pdf`.

[License](COPYING) · [Authors](AUTHORS) · [Acknowledgements and sponsors](docs/credits.md)
