#!/bin/bash

	COLOR=$(whiptail --inputbox "Choose color" 6 48\
		Blue --title "Color Chooser"\
		3>&1 1>&2 2>&3
	)

	if [ $? == 0 ]; then
		echo "Choice was " $COLOR
	else
		echo "Cancelled"
	fi

exit 0

