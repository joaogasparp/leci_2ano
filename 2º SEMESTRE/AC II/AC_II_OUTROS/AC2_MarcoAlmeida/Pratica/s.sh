#!/bin/bash 
pcompile aula$1/$2.s && ldpic32 aula$1/$2.hex -p /dev/ttyS$3 && pterm -p /dev/ttyS$3
rm aula$1/*.hex
rm aula$1/*.o
rm aula$1/*.sym
rm aula$1/*.map
rm aula$1/*.elf

