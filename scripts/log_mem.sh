#!/usr/local/bin/bash
valgrind --leak-check=full -v ./inte &> log/valgrind/valgrind_`uname -s`_`uname -p`_`uname -r`.log
echo "Valgrinded on: " `date` >> log/valgrind/valgrind_`uname -s`_`uname -p`_`uname -r`.log
