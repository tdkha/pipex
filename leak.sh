#!/bin/bash

valgrind ./pipex infile "ls -l" "wc -l" outfile
