#include <stdio.h>
#include <stdlib.h>

void FCFS(int disk[], int n, int start) {
    int totalMovement = 0;
    int currentPosition = start;
    
    printf("\nDisk Access Order: ");
    // FCFS Disk Scheduling: Visit each request in the order it appears
    for (int i = 0; i < n; i++) {
        printf("%d ", disk[i]);
        totalMovement += abs(disk[i] - currentPosition); // Calculate total movement
        currentPosition = disk[i]; // Move disk head to the requested track
    }

    printf("\nTotal Disk Movement: %d\n", totalMovement);
}

int main() {
    int diskRequests[] = { 98, 183, 41, 122, 14, 124, 65, 67 };
    int n = sizeof(diskRequests) / sizeof(diskRequests[0]);
    int start = 53; // Initial position of the disk head

    // Call FCFS disk scheduling
    FCFS(diskRequests, n, start);

    return 0;
}
