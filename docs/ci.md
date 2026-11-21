# GitHub Actions in this fork

Platform builds run on code/configuration pushes to `master`, `next` and `next*`.
Markdown, `docs/` and attribution/license-only edits do not trigger them.
Each workflow can also be started manually from the Actions tab.

Build artifacts stay in GitHub Actions. SignPath signing and uploads to the
upstream nightly server run only in `AlbrechtL/welle.io`, never in this fork.
Windows builds here produce an unsigned installer.

## Failures observed on 21 November 2026

| Workflow | Failed step | Finding |
|---|---|---|
| Windows | Sign installer with SignPath | Missing `api-token`; build and unsigned installer completed |
| Android | Upload to nightly server | Upstream deployment step failed; APK build completed |
| Linux | Prepare flatpak build | Metadata validation failed; exact diagnostic requires the full job log |
| Raspberry Pi | Build | Build failed; subsequent artifact upload found no output |

The trigger and publishing corrections do not establish that Linux or Raspberry Pi
builds pass. Previous failed runs remain in Actions as historical results.
