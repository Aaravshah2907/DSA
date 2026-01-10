counter: countExe
	./countExe
vowel: countVowelExe
	./countVowelExe
consonant: countConsonantExe
	./countConsonantExe
countVowel: countVowels.o master.o
	gcc -o countVowelExe countVowels.o master.o
countConsonant : countConsonants.o master.o
	gcc -o countConsonantExe countConsonants.o master.o
countExe: countVowels.o countConsonants.o master.o
	gcc -o countExe countConsonants.o countVowels.o master.o
countConsonants.o : countConsonants.c
	gcc -c countConsonants.c
countVowels.0 : countVowels.c
	gcc -c countVowels.c
master.o : master.c
	gcc -c master.c
clean: 
	rm -rf *.o
	rm *Exe