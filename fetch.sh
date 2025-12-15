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
if [ ! -f "input.txt" ];
then
    echo "Input file does not exist, pulling input file"
    curl "https://adventofcode.com/2025/day/$day/input" --compressed  -H "Cookie: session=$SESSION_KEY" >> input.txt
else
    echo "Input file exist"
fi

# Generate template and open with VS code
if [ ! -f "challenge_1.cpp" ];
then
    sed "s/day_X/day_$day/g" ../template.cpp > challenge_1.cpp
fi

if [ ! -f "challenge_2.cpp" ];
then
    sed "s/day_X/day_$day/g" ../template.cpp > challenge_2.cpp
fi
code .. # open parent directory

# Windows
# start "https://adventofcode.com/2025/day/$day"
# MacOS/Linux
open "https://adventofcode.com/2025/day/$day"