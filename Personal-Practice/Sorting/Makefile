run_all: bubbleSort mergeSort selectionSort quickSort insertionSort
	echo "All sorting algorithms compiled successfully."
	echo "Bubble Sort"
	./bubbleSort
	echo "Merge Sort"
	./mergeSort
	echo "Selection Sort"
	./selectionSort
	echo "Quick Sort"
	./quickSort
	echo "Insertion Sort"
	./insertionSort

bubbleSort : bubbleSort.o
	gcc -o bubbleSort bubbleSort.o

bubbleSort.o : bubbleSort.c
	gcc -c bubbleSort.c

mergeSort : mergeSort.o
	gcc -o mergeSort mergeSort.o

mergeSort.o : mergeSort.c
	gcc -c mergeSort.c

selectionSort : selectionSort.o
	gcc -o selectionSort selectionSort.o

selectionSort.o : selectionSort.c
	gcc -c selectionSort.c

quickSort : quickSort.o
	gcc -o quickSort quickSort.o

quickSort.o : quickSort.c
	gcc -c quickSort.c

insertionSort : insertionSort.o
	gcc -o insertionSort insertionSort.o

insertionSort.o : insertionSort.c
	gcc -c insertionSort.c

clean :
	rm -f *.o bubbleSort mergeSort selectionSort quickSort insertionSort 