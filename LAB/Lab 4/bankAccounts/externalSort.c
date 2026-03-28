#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "personMerge.h" // Reusing your struct and mergeSort


#define CHUNK_SIZE 1000000

// Helper to write a person struct to a file
void writePerson(FILE *fp, struct person p) {
    fprintf(fp, "%d,%s,%d,%d,%d\n", p.id, p.name, p.age, p.height, p.weight);
}

// Helper to read one person from a file
int readPerson(FILE *fp, struct person *p) {
    char line[1024];
    if (fgets(line, sizeof(line), fp)) {
        return sscanf(line, "%d,%[^,],%d,%d,%d", 
                      &p->id, p->name, &p->age, &p->height, &p->weight) == 5;
    }
    return 0;
}

// Function to merge two sorted files into a third
void mergeFiles(char *file1, char *file2, char *outputFile) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    FILE *out = fopen(outputFile, "w");

    struct person p1, p2;
    int hasP1 = readPerson(f1, &p1);
    int hasP2 = readPerson(f2, &p2);

    while (hasP1 && hasP2) {
        if (p1.height <= p2.height) {
            writePerson(out, p1);
            hasP1 = readPerson(f1, &p1);
        } else {
            writePerson(out, p2);
            hasP2 = readPerson(f2, &p2);
        }
    }

    // Drain remaining records
    while (hasP1) { writePerson(out, p1); hasP1 = readPerson(f1, &p1); }
    while (hasP2) { writePerson(out, p2); hasP2 = readPerson(f2, &p2); }

    fclose(f1); fclose(f2); fclose(out);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_csv>\n", argv[0]);
        return 1;
    }

    // Start Timer
    clock_t start_total = clock();

    FILE *input = fopen(argv[1], "r");
    if (!input) return 1;

    struct person *buffer = malloc(CHUNK_SIZE * sizeof(struct person));
    int runCount = 0;

    printf("Starting Phase 1: Run Generation...\n");
    while (1) {
        int count = 0;
        while (count < CHUNK_SIZE && readPerson(input, &buffer[count])) {
            count++;
        }
        if (count == 0) break;

        mergeSort(buffer, 0, count - 1);

        char runName[64];
        sprintf(runName, "run_%d.csv", runCount);
        FILE *runFile = fopen(runName, "w");
        for (int i = 0; i < count; i++) {
            writePerson(runFile, buffer[i]);
        }
        fclose(runFile);
        runCount++;
    }
    fclose(input);
    free(buffer);

    printf("Starting Phase 2: Tournament Merge (%d initial runs)...\n", runCount);
    int current_runs = runCount;
    int pass = 0;
    char input1[64], input2[64], output[64];

    while (current_runs > 1) {
        int next_runs = 0;
        for (int i = 0; i < current_runs; i += 2) {
            if (i + 1 < current_runs) {
                if (pass == 0) {
                    sprintf(input1, "run_%d.csv", i);
                    sprintf(input2, "run_%d.csv", i + 1);
                } else {
                    sprintf(input1, "pass%d_run%d.csv", pass, i);
                    sprintf(input2, "pass%d_run%d.csv", pass, i + 1);
                }
                sprintf(output, "pass%d_run%d.csv", pass + 1, next_runs);
                
                mergeFiles(input1, input2, output);
                
                // Cleanup intermediate files to save disk space
                remove(input1);
                remove(input2);
                next_runs++;
            } else {
                if (pass == 0) sprintf(input1, "run_%d.csv", i);
                else sprintf(input1, "pass%d_run%d.csv", pass, i);
                
                sprintf(output, "pass%d_run%d.csv", pass + 1, next_runs);
                rename(input1, output);
                next_runs++;
            }
        }
        pass++;
        current_runs = next_runs;
    }

    // End Timer
    clock_t end_total = clock();
    double cpu_time_used = ((double) (end_total - start_total)) / CLOCKS_PER_SEC;

    printf("--------------------------------------------\n");
    printf("External Sort Complete.\n");
    printf("Final file: pass%d_run0.csv\n", pass);
    printf("Total CPU time taken: %f seconds\n", cpu_time_used);
    printf("--------------------------------------------\n");

    return 0;
}