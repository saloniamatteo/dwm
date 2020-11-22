#!/bin/sh

pgrep -x dmenu && exit
mountable=$(lsblk -lp | grep "part $" | awk '{print $1, "(" $4 ")"}')
[[ "$mountable" = "" ]] && exit 1
chosen=$(echo "$mountable" | dmenu -i -p "Which drive to mount?" | awk '{print $1}')
[[ "$chosen" = "" ]] && exit 1
#sudo mount "$chosen" && exit 0
dirs=$(find /mnt /media /mount /home -type d -maxdepth 3 2>/dev/null)
mountpoint=$(echo "$dirs" | dmenu -i -p "Where to mount?")
[[ "$mountpoint" = "" ]] && exit 1
if [[ ! -d "$mountpoint" ]]; then
	mkdiryn=$(echo -e "No\nYes" | dmenu -i -p "$mountpoint does not exist. Create it?")
	[[ "$mkdiryn" = "Yes" ]] && sudo mkdir -p "$mountpoint"
fi

sudo mount $chosen $mountpoint && notify-send "DmenuMount" "$chosen mounted to $mountpoint."
