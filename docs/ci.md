# GitHub Actions in this fork

Code and configuration pushes to `master`, `next` and `next*` run the platform
builds. Markdown, `docs/` and attribution/license-only changes do not.
Use **Actions → workflow → Run workflow** for a manual build.
New runs supersede older runs of the same workflow and branch.

## Build outputs

All four linked runs passed for commit `fb9c3c1a` on 21 November 2026.

| Workflow | Artifact |
|---|---|
| [Windows](https://github.com/dg8ygz/welle.io/actions/runs/44922771077) | Unsigned Windows installer |
| [Linux](https://github.com/dg8ygz/welle.io/actions/runs/44922771105) | Flatpak bundles for x86-64 and ARM64 |
| [Android](https://github.com/dg8ygz/welle.io/actions/runs/44922771054) | Multi-ABI APK from CMake; ARM64 APK from qmake |
| [Raspberry Pi](https://github.com/dg8ygz/welle.io/actions/runs/44922771100) | ARMv6 `welle-cli` and its runtime library list |

Download artifacts from a successful run's summary. Builds use this repository's
checked-out commit. SignPath signing and the upstream FTP upload run only in
`AlbrechtL/welle.io`; this fork needs neither service's secrets.

The Pi build uses Raspbian Bookworm under QEMU and runs `welle-cli -v` before
exporting the binary. Its shared libraries must be installed on the target Pi;
this is a CLI build, not the Qt GUI. CI does not test radio hardware or reception.
Linux AppStream validation is mandatory; the separate Flathub publication
eligibility check remains advisory, as upstream configured it.

## Repairs on 21 November 2026

- Restricted upstream signing/publishing to the original repository.
- Replaced an unreachable AppStream help link with the project FAQ.
- Replaced the Pi's obsolete Buster/upstream-clone build with Bookworm and local source.
- Matched Android qmake to CMake's pinned SDK 33 / NDK r25b; runner SDK 36
  is incompatible with the older Qt 6.5 resource tools.

Old failed runs remain in Actions as history. Build-command failures now include
bounded diagnostic output in check annotations, alongside the complete job logs.
