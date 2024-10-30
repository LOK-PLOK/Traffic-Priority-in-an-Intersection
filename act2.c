#include "header.h"

int main() {
    Traffic scenario1[8] = {
        {1, "main", "left", 30},
        {2, "div", "right", 45},
        {3, "main", "straight", 25},
        {4, "div", "pedestrian", 35},
        {5, "main", "right", 50},
        {6, "div", "left", 20},
        {7, "main", "pedestrian", 40},
        {8, "div", "straight", 15}
    };

    Traffic scenario2[8] = {
        {2, "main", "right", 40},
        {3, "div", "left", 35},
        {1, "main", "straight", 30},
        {5, "div", "pedestrian", 45},
        {4, "main", "left", 50},
        {6, "div", "right", 25},
        {8, "main", "pedestrian", 20},
        {7, "div", "straight", 15}
    };

    Traffic scenario3[8] = {
        {3, "main", "left", 35},
        {1, "div", "right", 30},
        {2, "main", "straight", 25},
        {6, "div", "pedestrian", 40},
        {4, "main", "right", 45},
        {5, "div", "left", 50},
        {7, "main", "pedestrian", 20},
        {8, "div", "straight", 15}
    };

    remove("traffic_result.dat");
    insertToCommaSeparatedFile(scenario1,8,"scenario1");
    insertToCommaSeparatedFile(scenario2,8,"scenario2");
    insertToCommaSeparatedFile(scenario3,8,"scenario3");

    return 0;
}