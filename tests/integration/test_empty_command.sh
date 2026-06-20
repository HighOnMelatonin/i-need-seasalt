#!/usr/bin/env bash
# tests/integration/test_empty_command.sh
#
# Checks that pressing Enter without typing a command
# does not crash the shell.

set -euo pipefail

OUTPUT=$(printf "\n\n\nexit\n" | timeout 3s ./cseshell)

if ! echo "$OUTPUT" | grep -F "$$" > /dev/null; then
  echo "FAIL: shell did not continue after empty input"
  echo "----- shell output -----"
  echo "$OUTPUT"
  echo "------------------------"
  exit 1
fi

echo "PASS: shell handles empty commands"