#!/bin/bash

valgrind  --leak-check=full ./pipex infile "ls -l" "wc -l" outfile
