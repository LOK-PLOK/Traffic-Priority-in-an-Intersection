#ifndef TRAFFIC_HEADER
#define TRAFFIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 15

typedef struct {
    int priority;
    char Lane[MAX];
    char Path[MAX];
    int time;
} Traffic;

typedef struct {
    Traffic tree[MAX];
    int lastNdx;
} POT;

/**
 * Priority magnitude
 * 1 - Lane: main, Path: straight
 * 2 - Lane: main, Path: left
 * 3 - Lane: main, Path: right
 * 4 - Lane: div, Path: stright
 * 5 - Lane: div, Path: left
 * 6 - Lane: div, Path: right
 * 7 - Lane: main, Path: pedestrian
 * 8 - Lane: div, Path: pedestrian
 */

/**
 * Formulas to remember
 * Parent index = (child-1)/2
 * LeftChild index = parent*2 + 1
 * RightChild index = parent*2 + 2
 */

// Function declarations
void init(POT* heap);
Traffic create(int priority, char* lane, char* path, int time);
void populate(POT* heap, Traffic data[], int size);
void insertToPOT(POT* heap, Traffic data);
void display(Traffic data);
void displayPOT(POT heap);
Traffic deleteMin(POT* heap);
void heapify(POT* heap, int parent);
int totalTime(POT* heap);//<-----------------------------------------------ACTIVITY 1

// File handling
void insertToFile(Traffic data[], int size);
void insertToCommaSeparatedFile(Traffic data[], int size); //<------------------------ACTIVITY 2
void readFromFile();
void insertToMinHeap(POT* heap);

// Function definitions
int totalTime(POT* heap) {//<--------------------------------ACTIVITY 1
    int totalPriority = 0;
    while (heap->lastNdx != -1 && (strcmp(heap->tree[0].Lane, "main")) != 0 || (strcmp(heap->tree[0].Path, "pedestrian") != 0)) {
        totalPriority += heap->tree[0].time;
        deleteMin(heap);
    }

    return totalPriority;
}

void init(POT* heap) {
    heap->lastNdx = -1;
}

Traffic create(int priority, char* lane, char* path, int time) {
    Traffic temp;
    temp.priority = priority;
    strcpy(temp.Lane, lane);
    strcpy(temp.Path, path);
    temp.time = time;

    return temp;
}

void populate(POT* heap, Traffic data[], int size) {
    for (int i = 0; i < size; i++) {
        insertToPOT(heap, data[i]);
    }
}

void insertToPOT(POT* heap, Traffic data) {
    heap->tree[++heap->lastNdx] = data;
    int idx;
    for (idx = heap->lastNdx; idx > 0 && heap->tree[(idx - 1) / 2].priority > heap->tree[idx].priority; idx = (idx - 1) / 2) {
        Traffic temp = heap->tree[idx];
        heap->tree[idx] = heap->tree[(idx - 1) / 2];
        heap->tree[(idx - 1) / 2] = temp;
    }
}

void displayPOT(POT heap) {
    printf("%-20s%-20s%-20s%-20s\n", "Priority", "Lane", "Path", "Time(s)");
    for (int i = 0; i <= heap.lastNdx; i++) {
        printf("%-20d", heap.tree[i].priority);
        printf("%-20s", heap.tree[i].Lane);
        printf("%-20s", heap.tree[i].Path);
        printf("%-20d", heap.tree[i].time);
        printf("\n");
    }
}

void display(Traffic data) {
    printf("%-20d", data.priority);
    printf("%-20s", data.Lane);
    printf("%-20s", data.Path);
    printf("%-20d", data.time);
    printf("\n");
}

Traffic deleteMin(POT* heap) {
    Traffic min = heap->tree[0];
    heap->tree[0] = heap->tree[heap->lastNdx];
    heap->tree[heap->lastNdx] = min;

    heap->lastNdx--;

    heapify(heap, 0);

    return min;
}

void heapify(POT* heap, int parent) {
    int small = parent;
    int Lchild = parent * 2 + 1;
    int Rchild = parent * 2 + 2;

    if (Lchild <= heap->lastNdx && heap->tree[Lchild].priority < heap->tree[small].priority) {
        small = Lchild;
    }

    if (Rchild <= heap->lastNdx && heap->tree[Rchild].priority < heap->tree[small].priority) {
        small = Rchild;
    }

    if (small != parent) {
        Traffic temp = heap->tree[parent];
        heap->tree[parent] = heap->tree[small];
        heap->tree[small] = temp;
        heapify(heap, small);
    }
}

void insertToFile(Traffic data[], int size) {
    FILE* fp = fopen("traffic.dat", "wb+");
    if (fp != NULL) {
        fwrite(data, sizeof(Traffic), size, fp);
    }

    fclose(fp);
}

void insertToCommaSeparatedFile(Traffic data[], int size) { //<--------------------------------ACTIVITY 2
    FILE* fp = fopen("traffic_result.dat", "w");

    if (fp != NULL) {
        for (int i = 0; i < size; i++) {
            fprintf(fp, "%d,%s,%s,%d\n", data[i].priority, data[i].Lane, data[i].Path, data[i].time);
        }

        fclose(fp);
        printf("Results saved to file successfully.\n");
    }
}

void readFromFile() {
    FILE* fp = fopen("traffic.dat", "rb+");
    if (fp != NULL) {
        Traffic temp;
        while (fread(&temp, sizeof(Traffic), 1, fp)) {
            display(temp);
        }
    }
}

void insertToMinHeap(POT* heap) {
    FILE* fp = fopen("traffic.dat", "rb+");
    if (fp != NULL) {
        Traffic temp;
        while (fread(&temp, sizeof(Traffic), 1, fp)) {
            insertToPOT(heap, temp);
        }
    }
}

#endif