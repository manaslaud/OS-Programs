#include <stdio.h>
#include <stdbool.h>

int findIndex(int frame[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frame[i] == page) {
            return i;
        }
    }
    return -1;
}

int fifo(int pages[], int n, int frameCount) {
    int frame[frameCount];
    int pageFaults = 0, index = 0;

    for (int i = 0; i < frameCount; i++) {
        frame[i] = -1;  // Initialize all frames to -1 (empty)
    }

    for (int i = 0; i < n; i++) {
        if (findIndex(frame, frameCount, pages[i]) == -1) {  // Page not found
            frame[index] = pages[i];
            index = (index + 1) % frameCount;  // FIFO replacement
            pageFaults++;
        }
    }
    return pageFaults;
}

int lru(int pages[], int n, int frameCount) {
    int frame[frameCount], lastUsed[frameCount];
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int index = findIndex(frame, frameCount, pages[i]);

        if (index == -1) {  // Page fault
            int lruIndex = 0;
            for (int j = 1; j < frameCount; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }
            frame[lruIndex] = pages[i];
            pageFaults++;
        }

        lastUsed[findIndex(frame, frameCount, pages[i])] = i;
    }
    return pageFaults;
}

int optimal(int pages[], int n, int frameCount) {
    int frame[frameCount];
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (findIndex(frame, frameCount, pages[i]) == -1) {  // Page fault
            if (findIndex(frame, frameCount, -1) != -1) {
                frame[findIndex(frame, frameCount, -1)] = pages[i];
            } else {
                int farthest = i, index = -1;
                for (int j = 0; j < frameCount; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                index = j;
                            }
                            break;
                        }
                    }
                    if (k == n) {
                        index = j;
                        break;
                    }
                }
                frame[index] = pages[i];
            }
            pageFaults++;
        }
    }
    return pageFaults;
}

int main() {
    int pages[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frameCount = 4;  // Assuming 4 frames

    int fifoFaults = fifo(pages, n, frameCount);
    int lruFaults = lru(pages, n, frameCount);
    int optimalFaults = optimal(pages, n, frameCount);

    printf("Number of page faults using FIFO: %d\n", fifoFaults);
    printf("Number of page faults using LRU: %d\n", lruFaults);
    printf("Number of page faults using Optimal: %d\n", optimalFaults);

    return 0;
}
