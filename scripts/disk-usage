#!/bin/sh
# monitor the usage of one or more disks

drives=$(lsblk -lp | grep "t /" | awk '{print $1, "(" $4 ")", "on", $7}')
[[ $drives = "" ]] && exit
chosen=$(echo "$drives" | dmenu -i -p "Select which drive to monitor" | awk '{print $1}')
[[ "$chosen" = "" ]] && exit
refreshtime=$(printf "10\n15\n20\n25\n30\n35\n40\n45\n50\n55\n60" | dmenu -i -p "Please enter the frequency of rechecks in seconds")
[[ "$refreshtime" = "" ]] && exit
echo "You can close this window by either pressing 'CTRL+C', 'CTRL+Z', 'ALT+F4' or your terminal-specific keybinding"
printf "Frequency of rechecks: $refreshtime seconds\n"
while true; do
	echo "$(date '+%A, %d %B %Y at %H:%M:%S'):"
	df -Th $chosen && printf "\n"
	sleep $refreshtime
done
