# Authors: Erik Talvi
# 	   Paul Gentemann
# 	   Bucky Frost
#
# File: Makefile
# Purpose: Makefile for CS 372 CPS Project


CC = g++
CFLAGS =  -std=c++11 
CFLAGS_DEBUG = -g -Wall

INCLUDE = -I ./include/
SRC = ./src/*.cpp

# LFLAGS
# LIBS

#TEST = ./src/testSuites/*

#CATCH = ./test/*.cpp


all:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)  -o ./build/debug/cps-build.out
run:
	./build/debug/cps-build.out

debug:
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(INCLUDE) $(SRC) -o ./build/debug/cps-debug.out

# TODO: Define the tests for the project. Maybe have a number of different levels?
#test:

mkbuild:
	mkdir ./build/debug -p
	mkdir ./build/release -p
clean:
	rm -rf ./build/debug/*.*
	rm -rf ./build/release/*.*
	rm -rf ./include/*.gch

clean-all:
	rm -rf ./build/
