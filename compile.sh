#!/bin/bash

make fclean

make

rm -rf outfile
# touch infile

# echo "-------------------------------"
# ./pipex infile "ls -a" "wc -l" outfile
# cat outfile

# rm -rf outfile test

# < infile ls -a | wc -l > test
# cat test

# rm -rf outfile test

# echo "-------------------------------"

# echo "-------------------------------"
# ./pipex infile "/bin/ls " "wc -l" outfile
# cat outfile

# rm -rf outfile

# < infile /bin/ls | wc -l > test
# cat test

# rm -rf outfile test

# echo "-------------------------------"


echo "-------------------------------"
./pipex infile 'sed    "s/And/But/"' 'grep But' outfile
cat outfile

rm -rf outfile

< infile sed "s/And/But/" | grep But > test
cat test

rm -rf outfile test

echo "-------------------------------"


make fclean
