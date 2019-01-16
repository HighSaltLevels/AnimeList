#!/bin/bash

if [[$EUID -ne 0]]; then
    echo "Permission Denied. This installer needs to be run as root!"
    exit 1
fi

mkdir $HOME/.animelist
mkdir /usr/lib/animelist

mv icon.png /usr/lib/animelist
mv animelist /usr/bin

echo "Installation complete. To run the program, simply type 'ahinelist'"

