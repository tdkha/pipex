#!/bin/bash

cd libft
make 

cd ..

cc test_split.c libft/libft.a

./a.out infile 'sed "s/And/But/"' 'awk "{count++} END {printf \"count: %i\" , count}"' outfile

rm -rf a.out
