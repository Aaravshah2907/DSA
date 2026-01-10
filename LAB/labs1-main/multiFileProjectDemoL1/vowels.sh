gcc -c countVowels.c
gcc -c master.c

gcc -o CountVowelsExe countVowels.o master.o
./CountVowelsExe

rm *.o
rm *Exe