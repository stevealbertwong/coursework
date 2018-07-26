#!/bin/bash

## http://tldp.org/LDP/Bash-Beginners-Guide/html/sect_12_02.html

trap "echo Booh!" SIGINT SIGTERM
echo "pid is $$"

while :			# This is the same as "while true".
do
        sleep 60	# This script is not really doing anything.
done