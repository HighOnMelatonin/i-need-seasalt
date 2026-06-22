#!/usr/bin/env bash
# tests/integration/test_rc_parser.sh
#
# Verifies that the shell reads and executes commands from .cseshellrc at startup,
# such that commands in the rc file run before the user sees a prompt.
set -euo pipefail

SHELL_DIR=$(dirname "$(readlink -f ./cseshell)")
RC_FILE="$SHELL_DIR/.cseshellrc"
BACKUP_FILE="$SHELL_DIR/.cseshellrc.bak"

# Back up existing rc file if present
if [ -f "$RC_FILE" ]; then
    cp "$RC_FILE" "$BACKUP_FILE"
fi

# Write a test rc file that runs a command with observable output
cat > "$RC_FILE" << 'EOF'
# This is a comment — should be ignored
setenv TEST_RC_VAR hello_from_rc
EOF

# Run the shell — just enter and exit immediately
OUTPUT=$(printf "env\nexit\n" | timeout 3s ./cseshell)

# Restore original rc file
if [ -f "$BACKUP_FILE" ]; then
    mv "$BACKUP_FILE" "$RC_FILE"
else
    rm -f "$RC_FILE"
fi

# Check that the env var set in .cseshellrc is visible
if ! echo "$OUTPUT" | grep -F "TEST_RC_VAR=hello_from_rc" > /dev/null; then
    echo "FAIL: .cseshellrc was not parsed — TEST_RC_VAR not found in env output"
    echo "----- shell output -----"
    echo "$OUTPUT"
    echo "------------------------"
    exit 1
fi

echo "PASS: rc parser reads and executes commands from .cseshellrc at startup"