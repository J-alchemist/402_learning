#! /bin/bash


gcc serverMult_thread.c -o serverMT -pthread
gcc serverMult_process.c -o serverMP
