#Makefile for the serie1
#course of coucurrent and event-driven programming

SRC = $(wildcard *.c)
EXE = $(SRC:%.c=%)

all : $(EXE)

$(EXE): % : %.o
	gcc bin/$^ -o exe/$@

%.o: %.c
	gcc -c $^ -o bin/$@

.PHONY : clean
clean : 
	rm -f bin/*.o
	rm -f exe/*
	
