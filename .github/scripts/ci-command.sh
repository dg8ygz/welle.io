#!/usr/bin/env bash
# Preserve a failed command's status and expose bounded diagnostics in its check.
set -uo pipefail
if (( $# == 0 )); then
  echo 'Usage: ci-command.sh COMMAND [ARG ...]' >&2
  exit 2
fi
ci_log=$(mktemp)
trap 'rm -f "$ci_log"' EXIT
"$@" 2>&1 | tee "$ci_log"
ci_status=${PIPESTATUS[0]}
if (( ci_status != 0 )); then
  ci_context=$(tail -n 35 "$ci_log")
  ci_context=${ci_context//'%'/'%25'}
  ci_context=${ci_context//$'\r'/'%0D'}
  ci_context=${ci_context//$'\n'/'%0A'}
  printf '::error title=Build command failed (exit %s)::%s\n' "$ci_status" "$ci_context"
fi
exit "$ci_status"
