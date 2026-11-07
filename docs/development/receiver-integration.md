# Receiver integration test branch

The fork branch [`dg8ygz/receiver-integration-next`](https://github.com/dg8ygz/welle.io/tree/dg8ygz/receiver-integration-next)
collects the receiver corrections and GUI fixes tested together on 7 November
2026. It is a development test build, not an upstream release. The focused pull
requests remain the units of upstream review.

The application sources are the same as the tested snapshot
`5d0fc5e1df8a9c55f4744ea8fee7ecd3ff5ee73d`, based on upstream `next` at
`bb66c3f0cb6cc09f2a71fa95c50625d2699e8179`. That snapshot was initially kept
locally; it is now published with this documentation. Subsequent documentation
changes do not imply a new application build or a new hardware test.

## Included changes

| Pull request | Included head | Area |
| --- | --- | --- |
| [#974](https://github.com/AlbrechtL/welle.io/pull/974) | `63633572` | OFDM handoff, shutdown and stale-generation submissions |
| [#975](https://github.com/AlbrechtL/welle.io/pull/975) | `84e34db0` | MOT header, segment and character-data bounds |
| [#976](https://github.com/AlbrechtL/welle.io/pull/976) | `19b67533` | Socket ownership, repeated connections and high descriptors |
| [#977](https://github.com/AlbrechtL/welle.io/pull/977) | `c5e708f8` | DabAudio handoff, accepted counts and large valid fragments |
| [#978](https://github.com/AlbrechtL/welle.io/pull/978) | `880df757` | Soapy software AGC gain direction |
| [#979](https://github.com/AlbrechtL/welle.io/pull/979) | `3e094027` | Driver gain ranges, endpoints and step sizes |
| [#980](https://github.com/AlbrechtL/welle.io/pull/980) | `d79cc693` | Stored startup gain and restart error handling |
| [#981](https://github.com/AlbrechtL/welle.io/pull/981) | `a13a3c89` | Window-based software AGC and stream/thread lifecycle |
| [#982](https://github.com/AlbrechtL/welle.io/pull/982) | `401ef2a4` | RTL-TCP backpressure, retuning and partial headers |
| [#983](https://github.com/AlbrechtL/welle.io/pull/983) | `8f7ded69` | RTL-TCP pacing and controller-boundary tests |

The snapshot also includes Fridrich Strba's contributions:

- [#972](https://github.com/AlbrechtL/welle.io/pull/972), `1f9ed7ec`:
  discard services of the previous ensemble when the ensemble changes.
- [#973](https://github.com/AlbrechtL/welle.io/pull/973), `cdb8fa1d`:
  make the FEC test report decoder failure.
- [#984](https://github.com/AlbrechtL/welle.io/pull/984), `d7146893`:
  retry RTL-TCP connections and expose connection status.

Independent GUI changes are available in the fork as separate branches:

- [`dg8ygz/gui-accessibility-next`](https://github.com/dg8ygz/welle.io/tree/dg8ygz/gui-accessibility-next),
  `84a84d5f`: name the receiver settings button for accessibility and test it.
- [`dg8ygz/gui-contrast-next`](https://github.com/dg8ygz/welle.io/tree/dg8ygz/gui-contrast-next),
  `dd61c838`: use the window theme's foreground for the app bar and test contrast
  in light and dark themes at narrow and wide window sizes.
- [`dg8ygz/gui-icons-next`](https://github.com/dg8ygz/welle.io/tree/dg8ygz/gui-icons-next),
  `9b4f33cc`: verify that bundled SVG icons render. This detects missing SVG
  runtime support; it does not install Qt plugins.

These GUI changes are all present in the integration branch. No new upstream
pull request is implied by publishing the fork branches.

## Validation of the application snapshot

- Linux x86-64: CLI and GUI builds; all 20 selected CLI/unit CTest targets passed.
- Linux ARM64: CLI build; the same 20 CLI/unit targets passed.
- Final GUI on Linux x86-64 with Qt 6.8.2: OpenGL and software renderer runs,
  each with 15 passed targets and one skipped target (`gui.smoke_option`).
  Recording-dependent cases within UI tests were also skipped where the private
  recording data was unavailable.
- GUI counterchecks: removing SVG support made the icon test fail; restoring
  it passed. The contrast test detected the previous light-theme foreground.
- Targeted receiver tests cover invalid sizes, driver exceptions, stop/restart,
  stale reads, channel changes and transport boundaries. Deliberately
  reintroduced defects were used to check the relevant regression tests.
- A bounded live test of the final receiver integration exercised a real
  RTL-TCP server restart, reconnection and subsequent audio decoding.
  A longer 50-minute channel-switching run used an earlier integration and
  must not be treated as validation of all later changes.

These are results for this snapshot, not claims about current GitHub CI or
continuous monitoring. There is no ARM GUI or Windows validation. Private IQ
recording cases remain unavailable. No radio recordings or decoded audio are
included in this repository.

The ThreadSanitizer investigation is incomplete: ordinary targeted runs
reported a QtTest watchdog teardown race. Runs without that watchdog passed,
but Qt and the whole application were not fully instrumented. This is not a
claim of a clean full-application ThreadSanitizer run.

The pacing target remains bounded to 99–101% of nominal. A sustained source
rate outside the correction range can still exhaust buffering or move data
loss upstream. The tests do not establish a universal live detector for
duplicated source IQ. A foreign driver that never returns from `readStream()`
also remains outside the demonstrated shutdown guarantees. HTTP stream
termination during retuning is a separate open topic.

## Get and build this version

```sh
git clone --branch dg8ygz/receiver-integration-next --single-branch \
  https://github.com/dg8ygz/welle.io.git welle-integration
cd welle-integration
git rev-parse HEAD
```

Follow the [build instructions](building.md) for dependencies and configuration.
Build with GUI support to obtain `welle-io`; building only `welle-cli` does not
update a desktop installation. Install the newly built GUI in a separate test
prefix and point the desktop launcher's `Exec` at that installed program or its
wrapper. An existing launcher pointing at a previous upstream installation will
continue to run that older program.

Keep test settings separate with `XDG_CONFIG_HOME` and `XDG_DATA_HOME`. Existing
settings may be copied once into those test directories before the first start.
Local receiver addresses, credentials, deployment paths and operational logs
are intentionally not part of this public integration branch.
