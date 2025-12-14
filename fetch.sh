#!/bin/bash

: '
This script fetches the challenge and creates a folder. 
Usage: sh fetch.sh {day}
Copyright (c) 2025 Koh Mingyang. All Rights Reserved.
'

source ./.env

# Check if day argument is valid
day=$1
if ((day <= 0)) || ((day > 12))
then 
    echo "Invalid day argument"
    exit 1
fi

# Create directory for day if directory does not exist
mkdir -p day_$day
cd day_$day

# Retrieve and save the input if not exists
if [ ! -f "day_$day.txt" ];
then
    echo "Input file does not exist, pulling input file"
    curl "https://adventofcode.com/2025/day/$day/input" --compressed  -H "Cookie: session=$SESSION_KEY" >> day_$day.txt
else
    echo "Input file exist"
fi

# Generate template and open with VS code
template="with open('day_$day.txt', 'r') as f:"

if [ ! -f "day$day\_1.py" ];
then
    echo $template > day$day\_1.py
fi

if [ ! -f "day$day\_2.py" ];
then
    echo $template > day$day\_2.py
fi
code .. # open parent directory

# Windows
# start "https://adventofcode.com/2025/day/$day"
# MacOS/Linux
open "https://adventofcode.com/2025/day/$day"