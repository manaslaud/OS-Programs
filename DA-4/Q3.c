#include <stdio.h>

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
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (findIndex(frame, frameCount, pages[i]) == -1) {
            frame[index] = pages[i];
            index = (index + 1) % frameCount;
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

        if (index == -1) {
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
        if (findIndex(frame, frameCount, pages[i]) == -1) {
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
    int pages[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3};
    int n = sizeof(pages) / sizeof(pages[0]);

    printf("3 Frames:\n");
    printf("FIFO: %d\n", fifo(pages, n, 3));
    printf("LRU: %d\n", lru(pages, n, 3));
    printf("Optimal: %d\n", optimal(pages, n, 3));

    printf("4 Frames:\n");
    printf("FIFO: %d\n", fifo(pages, n, 4));
    printf("LRU: %d\n", lru(pages, n, 4));
    printf("Optimal: %d\n", optimal(pages, n, 4));

    return 0;
}
