#!/bin/bash

WINDOW_NAME=cub3D

for i in $(find maps/ -type f); do
	echo $i
	valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=mlx_mouse_hide.supp ./cub3D $i &
	PID=$!
	until xdotool search --name $WINDOW_NAME windowfocus &> /dev/null; do
		if ps -p $PID > /dev/null
			then
			sleep 1
			else
				break
		fi
	done
	xdotool search --name $WINDOW_NAME windowfocus key Escape
	wait $PID
done