#!/bin/bash

led=$1
state=$2
val=$3

i2cset -y 1 0x70 0x09 0x0f

if [ "$led" = "flash" ]; then

i2cset -y 1 0x70 0x00 0x00
i2cset -y 1 0x70 0x02 0x32
i2cset -y 1 0x70 0x04 0x32
i2cset -y 1 0x70 0x05 0x32
i2cset -y 1 0x70 0x07 0x32

i2cset -y 1 0x70 0x00 0x5a
i2cset -y 1 0x70 0x00 0x00
fi

if [ "$led" = "white" ]; then
	if [ "$state" = "on" ]; then
		echo "white leds are on"
		i2cset -y 1 0x70 0x00 0x5a
	elif [ "$state" = "off" ]; then
	        echo "leds off"	
		i2cset -y 1 0x70 0x00 0x00
	elif [ "$state" = "br" ]; then
		if [ "$val" -ge 0 ] && [ "$val" -le 100 ]; then
			realval="$(($val*32/100))"
			#echo $realval
			i2cset -y 1 0x70 0x02 0x$realval
			i2cset -y 1 0x70 0x04 0x$realval
			i2cset -y 1 0x70 0x05 0x$realval
			i2cset -y 1 0x70 0x07 0x$realval
		else
			echo "brightness should be between 0 and 100"
		fi
	fi
elif [ "$led" = "ir" ]; then 
	if [ "$state" = "on" ]; then
		echo "ir leds are on"
		i2cset -y 1 0x70 0x00 0xa5
	elif [ "$state" = "off" ]; then
	      	echo "leds off"	
		i2cset -y 1 0x70 0x00 0x00
	elif [ "$state" = "br" ]; then
		if [ "$val" -ge 0 ] && [ "$val" -le 100 ]; then
			realval="$(($val*32/100))"
			#echo $realval
			i2cset -y 1 0x70 0x01 0x$realval
			i2cset -y 1 0x70 0x03 0x$realval
			i2cset -y 1 0x70 0x06 0x$realval
			i2cset -y 1 0x70 0x08 0x$realval
		else
			echo "brightness should be between 0 and 100"
		fi	
	fi
fi
