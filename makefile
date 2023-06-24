# Authors: Chandu Kathi
# Lab10 makefile

lab10: lab10.o ParseCmd.o ProcessExtCmd.o Redirect.o RunExtCmd.o
	gcc -o lab10 lab10.o ParseCmd.o ProcessExtCmd.o Redirect.o RunExtCmd.o -Wall

lab10.o: lab10.c lab9_10.h
	gcc -c lab10.c -Wall

ParseCmd.o: ParseCmd.c lab9_10.h
	gcc -c ParseCmd.c -Wall

ProcessExtCmd.o: ProcessExtCmd.c lab9_10.h
	gcc -c ProcessExtCmd.c -Wall

Redirect.o: Redirect.c lab9_10.h
	gcc -c Redirect.c -Wall

RunExtCmd.o: RunExtCmd.c lab9_10.h
	gcc -c RunExtCmd.c -Wall
