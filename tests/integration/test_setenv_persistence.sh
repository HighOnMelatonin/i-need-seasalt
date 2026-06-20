#!/usr/bin/env bash

set -euo pipefail

OUTPUT=$(printf "setenv TESTVAR=hello\nenv\nexit\n" | timeout 3s ./cseshell)

if ! echo "$OUTPUT" | grep -F "TESTVAR=hello" > /dev/null; then
    echo "FAIL: environment variable not preserved"
    exit 1
fi

echo "PASS: environment variable preserved"