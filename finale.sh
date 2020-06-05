#!/usr/bin/env bash

for i in *.c
do
	gcc -g -c $i
done

gcc -g commandExec.o -o comando.x

rm commandExec.o

gcc -g *.o -o terminal.x

rm *.o

clear

./terminal.x
