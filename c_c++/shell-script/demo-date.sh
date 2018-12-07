#!/bin/bash
# Purpose: Demo date command and menus 
# Author: nixCraft <www.cyberciti.biz> under GPL v2.x+
# see:http://www.cyberciti.biz/faq/how-to-read-time-in-shell-script/
# ------------------------------------------------------
 
# Display text at given row and column 
show(){
        local x=$1
        local y=$2
        local txt="$3"
        # Set cursor position on screen
        tput cup $x $y
        echo "$txt"
}
while [ : ]
do
        clear
        # Get the system time
        now="$(date +"%r")"
        # Show main - menu, server name and time
        show 10 10 "MAIN MENU for $HOSTNAME - $now"
        show 11 10 "1. System info"
        show 12 10 "2. Apache server stats"
        show 13 10 "3. MySQL server stats"
        show 14 10 "4. Firewall stats"
        show 15 10 "5. Exit"
        tput cup 16 10; read -t 2 -p "Choice [1-5] ? " usrch
        # do something
        case $usrch in
                1) read -t 2 -p "Showing system info, wait..." fakeinput;;
                2) read -t 2 -p "Showing apache info, wait..." fakeinput;;
                3) read -t 2 -p "Showing mysqld info, wait..." fakeinput;;
                4) read -t 2 -p "Showing firewall info, wait..." fakeinput;;
                5) echo "Bye."; exit 0;;
        esac
done