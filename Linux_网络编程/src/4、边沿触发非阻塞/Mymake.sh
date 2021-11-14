#! /bin/bash


gcc epollpipe.c -o epollpoipe -pthread
gcc serverNoblock.c -o serverNoblock
