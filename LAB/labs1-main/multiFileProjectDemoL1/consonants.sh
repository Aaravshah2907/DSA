gcc -c countConsonants.c
gcc -c master.c

gcc -o CountConstsExe countConsonants.o master.o
./CountConstsExe

rm *.o
rm *Exe