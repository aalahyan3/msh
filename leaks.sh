#!/bin/bash

# Get the first PID of the process named 'minishell'
pid=$(pgrep -o minishell)

# Check if the PID is found
if [ -z "$pid" ]; then
    echo "No 'minishell' process found."
    exit 1
fi

echo "Monitoring 'minishell' process with PID: $pid"

# Run leaks continuously on the PID
while true; do
    leaks -q "$pid"
    sleep 1
    clear
done
