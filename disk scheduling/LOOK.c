#include <stdio.h>
#include <stdlib.h>

void LOOK(int disk[], int n, int start, int direction) {
    int totalMovement = 0;
    int currentPosition = start;
    int visited[n];
    
    // Mark all requests as unvisited
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // First, handle requests in the given direction
    printf("\nDisk Access Order: ");
    if (direction == 1) {  // Moving from left to right
        for (int i = 0; i < n; i++) {
            if (disk[i] >= currentPosition) {
                visited[i] = 1;
                printf("%d ", disk[i]);
                totalMovement += abs(disk[i] - currentPosition);
                currentPosition = disk[i];
            }
        }

        // Then, handle requests to the left of the starting position
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {
                printf("%d ", disk[i]);
                totalMovement += abs(disk[i] - currentPosition);
                currentPosition = disk[i];
            }
        }
    } else {  // Moving from right to left
        for (int i = n - 1; i >= 0; i--) {
            if (disk[i] <= currentPosition) {
                visited[i] = 1;
                printf("%d ", disk[i]);
                totalMovement += abs(disk[i] - currentPosition);
                currentPosition = disk[i];
            }
        }

        // Then, handle requests to the right of the starting position
        for (int i = n - 1; i >= 0; i--) {
            if (visited[i] == 0) {
                printf("%d ", disk[i]);
                totalMovement += abs(disk[i] - currentPosition);
                currentPosition = disk[i];
            }
        }
    }

    printf("\nTotal Disk Movement: %d\n", totalMovement);
}

int main() {
    int diskRequests[] = { 98, 183, 41, 122, 14, 124, 65, 67 };
    int n = sizeof(diskRequests) / sizeof(diskRequests[0]);
    int start = 53;  // Initial position of the disk head
    int direction = 1;  // 1 for left to right, -1 for right to left

    // Call LOOK disk scheduling
    LOOK(diskRequests, n, start, direction);

    return 0;
}
