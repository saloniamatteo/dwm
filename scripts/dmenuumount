#!/bin/sh

exclusionregex="\(/boot\|/boot/efi\|/home\|/\)$"
drives=$(lsblk -lp | grep "t /" | grep -v "$exclusionregex" | awk '{print $1, "(" $4 ")", "on", $7}')
[[ $drives = "" ]] && exit
chosen=$(echo "$drives" | dmenu -i -p "Select which drive to unmount" | awk '{print $1}')
[[ "$chosen" = "" ]] && exit
sudo umount $chosen && pgrep -x dunst && notify-send "DmenuUmount" "$chosen unmounted."
