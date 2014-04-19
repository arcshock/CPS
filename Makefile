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
TEST = ./testing/*.cpp

# LFLAGS
# LIBS

#CATCH = ./test/*.cpp

#- Possible make targes.
#-

#- all: default target prints the makefile targets.
all:
	@grep '#-' Makefile | grep -v 'grep'


#- build: compiles the project.
build:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)  -o ./build/debug/cps-build.out


#- run: runs the program executable.
run:
	./build/debug/cps-build.out

#- test: runs testing suit
test:
	$(CC) $(CFLAGS) $(INCLUDE) $(TEST) -o ./build/debug/cps-test.out
	./build/debug/cps-test.out

#- exe: compiles and runs project.
exe: mkbuild
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)  -o ./build/debug/cps-build.out
	@./build/debug/cps-build.out


#- debug compiles project with debugging symbols.
debug: mkbuild
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(INCLUDE) $(SRC) -o ./build/debug/cps-debug.out


#- mkbuild: creates the build directory structure.
.PHONY: mkbuild
mkbuild:
	@mkdir -p ./build/debug 
	@mkdir -p ./build/release


#- clean: removes all the files from within the build directories.
.PHONY: clean
clean:
	@rm -rf ./build/debug/*.*
	@rm -rf ./build/release/*.*
	@rm -rf ./include/*.gch


#- clean-all: removes the build directory structure.
.PHONY: clean-all
clean-all:
	@rm -rf ./build/
