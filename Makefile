# build an executable named myprog from myprog.c
all: main.c 
		gcc -g -Wall -o license-generator main.c

clean: 
	$(RM) license-generator