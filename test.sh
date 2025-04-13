#!/bin/sh

while true; do
	pid=$(pgrep -o minishell)
	if [ -z "$pid" ]; then
		echo "Waiting for 'minishell' to start..."
		sleep 1
		clear
		continue
	fi

	echo "Monitoring 'minishell' with PID: $pid"

	while kill -0 "$pid" 2>/dev/null; do
		leaks -q "$pid"
		sleep 1
		clear
	done

	echo "'minishell' exited. Restarting search..."
done

