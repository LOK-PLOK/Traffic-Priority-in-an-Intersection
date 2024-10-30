#include "header.h"

int main() {
    POT heap;
    init(&heap);

    Traffic data1 = {2, "main", "left", 45};
    Traffic data2 = {5, "div", "left", 50};
    Traffic data3 = {1, "main", "straight", 30};
    Traffic data4 = {8, "div", "pedestrian", 35};
    Traffic data5 = {3, "main", "right", 60};
    Traffic data6 = {4, "div", "straight", 15};
    Traffic data7 = {6, "div", "right", 25};
    Traffic data8 = {7, "main", "pedestrian", 40};
    Traffic data[8] = {data1, data2, data3, data4, data5, data6, data7, data8};

    insertToFile(data, sizeof(data) / sizeof(data[0]));
    insertToCommaSeparatedFile(data, sizeof(data) / sizeof(data[0])); //<-----------------------------ACTIVITY 2
    printf("%-20s%-20s%-20s%-20s\n", "Priority", "Lane", "Path", "Time(s)");
    readFromFile();

    printf("\n\n");

    insertToMinHeap(&heap);
    displayPOT(heap);

    int totalPriority = totalTime(&heap); // <-------------------------------------ACTIVITY 1 
    printf("\n\nTotal time to MAIN PEDESTRIAN: %-5d\n\n", totalPriority);
    return 0;
}