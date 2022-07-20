#!/bin/bash

build:
	g++ access_status.cpp -lfcgi -l sqlite3 -o main

start:
	spawn-fcgi -p 9000 -n main


up: build start
