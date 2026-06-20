#!/usr/bin/env bash
# tests/integration/test_builtin_usage.sh
#
# Verifies the usage builtin:
#   - usage cd prints usage information for cd.
#   - usage with an unknown command gives a helpful message.

#stop immediately if any command fails
set -euo pipefail

OUTPUT=$(printf "usage cd\nexit\n" | timeout 3s ./cseshell)
                      #look for the word cd 
if ! echo "$OUTPUT" | grep -F "cd" > /dev/null; then
  echo "FAIL: usage cd did not print cd usage information"
  echo "----- shell output -----"
  echo "$OUTPUT"
  echo "------------------------"
  exit 1
fi

OUTPUT=$(printf "usage banana\nexit\n" | timeout 3s ./cseshell)

if ! echo "$OUTPUT" | grep -F "banana" > /dev/null; then
  echo "FAIL: usage banana did not mention invalid command"
  echo "----- shell output -----"
  echo "$OUTPUT"
  echo "------------------------"
  exit 1
fi

echo "PASS: usage builtin works as expected"