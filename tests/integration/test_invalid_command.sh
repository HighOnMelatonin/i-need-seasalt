#!/usr/bin/env bash
# tests/integration/test_invalid_command.sh
#
# Checks that an invalid command prints an error
# and the shell does not crash.

set -euo pipefail

OUTPUT=$(printf "banana\nexit\n" | timeout 3s ./cseshell)

if ! echo "$OUTPUT" | grep -F "not found" > /dev/null; then
  echo "FAIL: invalid command did not show not found message"
  echo "----- shell output -----"
  echo "$OUTPUT"
  echo "------------------------"
  exit 1
fi

echo "PASS: invalid command handled safely"