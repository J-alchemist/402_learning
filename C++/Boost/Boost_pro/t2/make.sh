#! /bin/bash

g++ thread1.cpp -o thread1 -std=c++11  -I /usr/local/include -L /usr/local/lib -lboost_system -lboost_thread
