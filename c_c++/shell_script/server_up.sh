#!/bin/bash
# Chatbox Server Screen Start Up Script
# Copyright Linnovs
# License MIT
# Version 0.0.9

script_name=$(basename $0)
session='Chatbot'
version='0.0.9'
fuc='MAIN'

if [[ $(id -u) -ne 0 ]];then
	print "This script must start with root privileges!" "ERROR"
	exit 1
fi

if [[ ! -f "./${session}_screen.pid" ]];then touch "${session}_screen.pid"; fi

function usages(){
	echo "[$script_name v$version] Python Script run in Daemon(Screen Session)"
	echo "Created by "
	echo
	echo "Usage $script_name [start|stop|restart|status|log]"
	echo
	echo "  [start]   - start the Chatbox server in screen session"
	echo "    options"
	echo "      [-s (session_name)]  - create the new screen with given session name"
	echo "  [stop]    - stop the current running screen session of Chatbox"
	echo "  [restart] - restart the Chatbox screen session"
	echo "  [status]  - check Chatbox screen session is running or not"
	echo "  [log]     - get the log from current or last running session of Chatbox"
	echo "    options"
	echo "      [-n (n)] - get lastest (n) line log msg"
	echo "      [-f]     - get lastest (n) line (defualt 10 line if -n option is not given) and track the log for changes"
	echo
	exit 1
}

function print(){
	printf "[ $session ][ $fuc ][ ${2:-"DEBUG"} ] $1 \n"
}

function un_expect(){
	opt=$1
	shift
	for var in "$@";do
		if [[ "$var" == -* ]];then
			print "[$opt] unexpected option [$var]" "ERROR"
			error=1
		fi
	done
	if [[ -n $error ]]; then
		exit 1
	fi
}

function log(){
	whoiam=$1
	shift
	for opt in "$@";do
		if [[ "$opt" == -* ]];then
			case $opt in
				"-n")
				shift
				line="-n $1"
				shift
				;;
				"-f")
				shift
				tailf="-f"
				;;
				*)
				un_expect $whoiam $@
				;;
			esac
		fi
	done

	if [[ ! -f ./screenlog.0 ]];then
		print "Cannot find screen session log file (screenlog.0)" "ERROR"
		exit 1
	fi
	# echo "tail $tailf ${line:=-n 10} "./screenlog.0""
	tail $tailf ${line:=-n 10} "./screenlog.0"
	echo
}

function check_running() {
	pgrep -F "./${session}_screen.pid" > /dev/null 2>&1
	[[ $? -eq 0 ]] && return 0 || return 1
}

function start(){
	printf "" > ./screenlog.0
	if check_running;then
		print "Detected last screen session still working." "Warning"
		print "Cannot start new session" "Warning"
		exit 1
	fi

	print "Starting Screen session..."
	screen -S "$session" -t "$session Python Server" -d -m -f -L -l -U -s $(which bash) sudo -E python3 $PWD/app.py
	screen -wipe "$session" | grep "$session" | awk -F. '{print $1}' > "./${session}_screen.pid"
	if ! check_running;then
		print "Cannot start screen session, Error ocurred." "ERROR"
		print "============[ERROR MSG]============" "ERROR"
		log
		print "============[ERROR MSG]============" "ERROR"
		rm ./screenlog.0
		exit 1
	fi
	print "Started Screen session."
	print "You can view the log via [$script_name log]"
	exit 0
}

function stop(){
	if check_running;then
		print "Stop running screen session."
		screen -r $session -X quit
		pkill SCREEN
		sleep 1
		stop
	else
		print "Session Not running now."
	fi
}

function status(){
	status=$(check_running && echo '[NOW]' || echo '[NOT]')
	print "$session Screen Session is \e[1m$status\e[0m running."
}

if [[ $# -gt 4 || $# -eq 0 ]];then
	usages
else
	option=$1
	shift
	case $option in
		"start")
		func="START"
		un_expect $option $@
		start
		;;
		"stop")
		func="STOP"
		un_expect $option $@
		stop
		;;
		"restart")
		func="RESTART"
		un_expect $option $@
		stop
		start
		;;
		"status")
		func="STATUS"
		un_expect $option $@
		status
		;;
		"log")
		func="LOG"
		log $option $@
		;;
		*)
		usages
		;;
	esac
	exit 0
fi