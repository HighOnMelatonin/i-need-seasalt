#!/usr/bin/env bash
# tests/integration/test_resource_usage.sh
#
# Checks that resource usage feedback is printed after a command.

set -euo pipefail

OUTPUT=$(printf "help\nexit\n" | timeout 3s ./cseshell)

if ! echo "$OUTPUT" | grep -F "Resource usage for 'help'" > /dev/null; then
  echo "FAIL: resource usage summary was not printed for help"
  echo "----- shell output -----"
  echo "$OUTPUT"
  echo "------------------------"
  exit 1
fi

if ! echo "$OUTPUT" | grep -F "CPU time" > /dev/null; then
  echo "FAIL: CPU time was not printed"
  exit 1
fi

if ! echo "$OUTPUT" | grep -F "Memory" > /dev/null; then
  echo "FAIL: memory usage was not printed"
  exit 1
fi

echo "PASS: resource usage feedback is printed"