#!/bin/bash

make fclean

make

rm -rf infile outfile
touch infile

echo "-------------------------------"
./pipex infile "ls -a" "wc -l" outfile
echo "-------------------------------"

make fclean