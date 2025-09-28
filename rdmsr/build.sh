#!/usr/bin/env bash

echo "this will require sudo, and it will load kernel modules"

bat "$0"
echo -e "\n\n\n"
bat ./dump_msr.c

#!/bin/bash

read -r -p "Do you want to continue? [y/N] " answer
case "$answer" in
[Yy]*) echo "Continuing..." ;;
*)
	echo "Exiting."
	exit 1
	;;
esac

make
objdump -D -M intel dump_msr.ko >dump_msr.asm
# Disable linting. <leader>.w
sudo insmod dump_msr.ko # This will run it.
sudo dmesg | tail -n 20
sudo rmmod dump_msr
sudo dmesg | tail -n 20
