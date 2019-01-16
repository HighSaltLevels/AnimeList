#!/bin/bash

echo "Checking to see if run with root priveleges..."
if [[ $EUID -ne 0 ]]; then
    echo "Permission Denied. This installer needs to be run as root!"
    exit 1
fi

echo "Creating directory for files..."
mkdir /usr/lib/animelist

echo "Placing files where they belong..."
mv icon.png /usr/lib/animelist
mv animelist /usr/bin

echo "Creating text files..."
touch /usr/lib/animelist/watched.txt
touch /usr/lib/animelist/unwatched.txt

echo "Giving permissions for files..."
chmod o+rw /usr/lib/animelist/watched.txt
chmod o+rw /usr/lib/animelist/unwatched.txt

echo "Installation complete. To run the program, simply type 'animelist'"

