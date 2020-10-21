# File: Makefile
# Author: Alex Sylvanus
# Description: Build Complex Number Project

# Define folders
INC=inc
ODIR_S=obj

# Define compiler
CC=gcc
# Get C files
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,%.o,$(SRC))
OBJ_S=$(patsubst %,$(ODIR_S)/%,$(OBJ))

# Define rules
main : main.o $(OBJ) libavector.dll
	gcc $(ODIR_S)/*.o -L. -lavector -o Test2

%.o : src/%.c
	if [ ! -d "$(ODIR_S)" ]; then mkdir $(ODIR_S); fi
	$(CC) -c $^ -o $(ODIR_S)/$@ -I$(INC)

main.o : main.c
	if [ ! -d "$(ODIR_S)" ]; then mkdir $(ODIR_S); fi
	$(CC) -c $^ -o $(ODIR_S)/$@ -I$(INC)

clean :
	rm -rf $(ODIR_S)
	rm Test2