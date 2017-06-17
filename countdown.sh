#!/bin/bash
# init-

clear

cd /sys/class/gpio/
if echo 60 > export; then
	:
else
	echo 60 > unexport
	echo 30 > unexport
	exit 1
fi
if echo 30 > export; then
	:
else
	echo 60 > unexport
	echo 30 > unexport
	exit 1
fi
cd /sys/class/gpio/gpio60
echo out > direction
echo 0 > value 
cd /sys/class/gpio/gpio30
echo out > direction
echo 0 > value 

lauchCode="Fly you Fools!"
valveOpenTime=2
ignitionKeeponTime=10s

echo Ready to launch!
echo To cancel: press \'Control\' and \'C\' simultaneously.
echo To start countdown: Enter the phrase: \'Fly you Fools!\' and press enter.
read enteredCode

if [ "$enteredCode" = "$lauchCode" ]; then
	echo
	echo Launch initiated! 
	echo Clear all personal from launch zone! 
	echo

	echo Launch In:
	countdown=15

	while [ "$countdown" -gt $valveOpenTime ]
	do
		echo $countdown
		sleep 1s
		let "countdown--"
	done

	echo Opening Valve!
	cd /sys/class/gpio/gpio30
	echo 1 > value

	while [ "$countdown" -gt 0 ]
	do
		echo $countdown
		sleep 1s
		let "countdown--"
	done


	echo Igniting!

	echo
	echo +------------------------+
	echo \|Nuclear launch detected!\|
	echo +------------------------+
	echo

	cd /sys/class/gpio/gpio60
	echo 1 > value
	sleep $ignitionKeeponTime


	echo Launch Complete!

	cd /sys/class/gpio/gpio60
	echo 0 > value
	cd /sys/class/gpio/gpio30
	echo 0 > value

else
	echo The launch phrase did not match! Aborting!
	cd /sys/class/gpio/gpio60
	echo 0 > value
	echo in > direction
	cd /sys/class/gpio/gpio30
	echo 0 > value
	echo in > direction
fi
echo in > direction
echo in > direction

cd /sys/class/gpio/
echo 60 > unexport
echo 30 > unexport
