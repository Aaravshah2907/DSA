#ifndef PERSON_MERGE_H
#define PERSON_MERGE_H

struct person {
    int id;
    char name[256];
    int age;
    int height;
    int weight;
};

void merge(struct person arr[], int l, int m, int r);
void personMergeAuxIter(struct person arr[], int l, int m, int r);
void mergeSort(struct person arr[], int l, int r); // Add this line!

#endif