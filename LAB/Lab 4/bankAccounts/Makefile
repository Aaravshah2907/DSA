# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -O3

# Targets
TARGET_INT = ms_int_iter
TARGET_PERSON = ms_person_iter

# Build all versions
all: $(TARGET_INT) $(TARGET_PERSON)

# --- Person-based Merge Sort (Task 3) ---
$(TARGET_PERSON): personMergeSort.o personMerge.o personMergeAuxIter.o
	$(CC) $(CFLAGS) -o $(TARGET_PERSON) personMergeSort.o personMerge.o personMergeAuxIter.o

personMergeSort.o: personMergeSort.c personMerge.h
	$(CC) $(CFLAGS) -c personMergeSort.c

personMerge.o: personMerge.c personMerge.h
	$(CC) $(CFLAGS) -c personMerge.c

personMergeAuxIter.o: personMergeAuxIter.c personMerge.h
	$(CC) $(CFLAGS) -c personMergeAuxIter.c

ms_external: externalSort.o personMerge.o personMergeAuxIter.o
	$(CC) $(CFLAGS) -o ms_external externalSort.o personMerge.o personMergeAuxIter.o

externalSort.o: externalSort.c personMerge.h
	$(CC) $(CFLAGS) -c externalSort.c

# --- Integer-based Merge Sort (Task 2 - For comparison) ---
$(TARGET_INT): intMergeSort.o intMerge.o intMergeAuxIter.o
	$(CC) $(CFLAGS) -o $(TARGET_INT) intMergeSort.o intMerge.o intMergeAuxIter.o

intMergeSort.o: intMergeSort.c intMerge.h
	$(CC) $(CFLAGS) -c intMergeSort.c

intMerge.o: intMerge.c intMerge.h intMergeAux.h
	$(CC) $(CFLAGS) -c intMerge.c

intMergeAuxIter.o: intMergeAuxIter.c intMergeAux.h
	$(CC) $(CFLAGS) -c intMergeAuxIter.c

# Clean up build files
clean:
	rm -f *.o $(TARGET_INT) $(TARGET_PERSON) mergesort_benchmarks.dat benchmarks.dat