#include <stdio.h>
#include <stdlib.h>

void SSTF(int disk[], int n, int start) {
    int totalMovement = 0;
    int currentPosition = start;
    int visited[n];  // Array to track visited disk requests
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("\nDisk Access Order: ");
    for (int i = 0; i < n; i++) {
        int minDistance = __INT_MAX__;  // Initially set to a large number
        int closestRequest = -1;

        // Find the request with the shortest seek time
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {  // If request not yet visited
                int distance = abs(disk[j] - currentPosition);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestRequest = j;
                }
            }
        }

        // Mark the closest request as visited
        visited[closestRequest] = 1;
        printf("%d ", disk[closestRequest]);
        totalMovement += minDistance;
        currentPosition = disk[closestRequest];  // Move disk head to the closest request
    }

    printf("\nTotal Disk Movement: %d\n", totalMovement);
}

int main() {
    int diskRequests[] = { 98, 183, 41, 122, 14, 124, 65, 67 };
    int n = sizeof(diskRequests) / sizeof(diskRequests[0]);
    int start = 53;  // Initial position of the disk head

    // Call SSTF disk scheduling
    SSTF(diskRequests, n, start);

    return 0;
}
