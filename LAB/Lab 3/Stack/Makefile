runStackWithArray: stackDriver.o stack_II.o
	gcc -o runFile stackDriver.o stack_II.o
	./runFile

stackDriver.o: stackDriver.c stack.h linked_list.h
	gcc -c stackDriver.c

stack_II.o: stack_II.c stack.h linked_list.h
	gcc -c stack_II.c

clean:
	rm -rf *.o runFile