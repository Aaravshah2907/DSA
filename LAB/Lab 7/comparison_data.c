#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>

int extractNumberFromFilename(const char *filename) {
    const char *p = filename;

    // Move pointer to the first digit
    while (*p && !isdigit(*p)) p++;

    if (!*p) return -1; // No number found

    return (int)strtol(p, NULL, 10);
}

struct person {
    int id;
    char name[256];
    int age;
    int height;
    int weight;
};

void countingSort(struct person *arr, int n) {
    if (n <= 0) return;

    // Find max height
    int max = INT_MIN;
    for (int i = 0; i < n; i++)
        if (arr[i].height > max) max = arr[i].height;

    int *count = calloc(max + 1, sizeof(int));

    // Count occurrences
    for (int i = 0; i < n; i++)
        count[arr[i].height]++;

    // Cumulative count
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    struct person *output = malloc(n * sizeof(struct person));

    // Build output array (stable)
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i].height] - 1] = arr[i];
        count[arr[i].height]--;
    }

    // Copy back
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(count);
    free(output);
}

// ---------- Radix Sort (height) ----------
void countingSortForRadix(struct person *arr, int n, int place) {
    struct person *output = malloc(n * sizeof(struct person));
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (arr[i].height / place) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i].height / place) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

void radixSort(struct person *arr, int n) {
    int max = INT_MIN;
    for (int i = 0; i < n; i++)
        if (arr[i].height > max) max = arr[i].height;

    for (int place = 1; max / place > 0; place *= 10)
        countingSortForRadix(arr, n, place);
}

// ---------- Radix Exchange Sort ----------
void radixExchangeSort(struct person *arr, int left, int right, int bit) {
    if (left >= right || bit < 0) return;

    int i = left, j = right;
    while (i <= j) {
        while (i <= j && (arr[i].height & (1 << bit)) == 0) i++;
        while (i <= j && (arr[j].height & (1 << bit)) != 0) j--;
        if (i < j) {
            struct person temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++; j--;
        }
    }

    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

// ---------- Bucket Sort (height) ----------
typedef struct Node {
    struct person p;
    struct Node *next;
} Node;

Node* insertNode(Node* head, struct person p) {
    Node* n = malloc(sizeof(Node));
    n->p = p;
    n->next = head;
    return n;
}

void insertionSortBucket(struct person *arr, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        struct person key = arr[i];
        int j = i - 1;
        while (j >= start && arr[j].height > key.height) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(struct person *arr, int n) {
    if (n <= 0) return;

    int max = INT_MIN;
    for (int i = 0; i < n; i++)
        if (arr[i].height > max) max = arr[i].height;

    int numBuckets = n;
    Node** buckets = calloc(numBuckets, sizeof(Node*));

    for (int i = 0; i < n; i++) {
        int idx = (arr[i].height * numBuckets) / (max + 1);
        if (idx >= numBuckets) idx = numBuckets - 1;
        buckets[idx] = insertNode(buckets[idx], arr[i]);
    }

    int pos = 0;
    for (int i = 0; i < numBuckets; i++) {
        Node* temp = buckets[i];
        int start = pos;
        while (temp) {
            arr[pos++] = temp->p;
            Node* old = temp;
            temp = temp->next;
            free(old);
        }
        int end = pos - 1;
        if (end > start) insertionSortBucket(arr, start, end);
    }

    free(buckets);
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    FILE *fp = fopen(argv[1], "r");
    if (!fp) return 1;

    int capacity = 100;
    struct person *students = malloc(capacity * sizeof(struct person));
    int count = 0;
    char line[1024];

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) < 5) continue;

        if (count >= capacity) {
            capacity *= 2;
            students = realloc(students, capacity * sizeof(struct person));
        }

        if (sscanf(line, "%d,%[^,],%d,%d,%d",
            &students[count].id, students[count].name,
            &students[count].age, &students[count].height,
            &students[count].weight) == 5) {
            count++;
        }
    }
    fclose(fp);

    int num = extractNumberFromFilename(argv[1]);

    FILE *out = fopen("sorting_times.dat", "a");
    if (!out) { printf("Cannot create output file.\n"); return 1; }

    fseek(out, 0, SEEK_END);  // Go to end of file
    long size = ftell(out);   // Get file size

    if (size == 0) {
        fprintf(out, "#Algorithm File_Size Time_sec\n"); // Only write if file is empty
    }

    clock_t start, end;
    struct person *copy = malloc(count * sizeof(struct person));

    // Counting Sort
    memcpy(copy, students, count * sizeof(struct person));
    start = clock();
    countingSort(copy, count);
    end = clock();
    fprintf(out, "CountingSort %d %.6f\n", num, (double)(end - start) / CLOCKS_PER_SEC);

    // Radix Sort
    memcpy(copy, students, count * sizeof(int));
    start = clock();
    radixSort(copy, count);
    end = clock();
    fprintf(out, "RadixSort %d %.6f\n", num, (double)(end - start) / CLOCKS_PER_SEC);

    // Radix Exchange Sort
    int maxHeight = INT_MIN;
    for (int i = 0; i < count; i++)
        if (students[i].height > maxHeight) maxHeight = students[i].height;
    int bits = 0;
    while ((1 << bits) <= maxHeight) bits++;
    memcpy(copy, students, count * sizeof(struct person));
    start = clock();
    radixExchangeSort(copy, 0, count - 1, bits - 1);
    end = clock();
    fprintf(out, "RadixExchangeSort %d %.6f\n", num, (double)(end - start) / CLOCKS_PER_SEC);

    // Bucket Sort
    memcpy(copy, students, count * sizeof(int));
    start = clock();
    bucketSort(copy, count);
    end = clock();
    fprintf(out, "BucketSort %d %.6f\n", num, (double)(end - start) / CLOCKS_PER_SEC);

    fclose(out);
    free(copy);
    free(students);

    printf("Timing results exported to sorting_times.dat (plot with gnuplot)\n");
    return 0;
}

