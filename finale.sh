#!/usr/bin/env bash

for i in *.c
do
	gcc -g -c $i
done

rm commandExec.o

gcc -g *.o -o terminalTest.x

rm *.o

clear

./terminalTest.x
