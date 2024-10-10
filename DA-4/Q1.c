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
        frame[i] = -1; // Initialize frame to -1
    }

    for (int i = 0; i < n; i++) {
        if (findIndex(frame, frameCount, pages[i]) == -1) { // Page not in frame
            frame[index] = pages[i];
            index = (index + 1) % frameCount; // FIFO replacement
            pageFaults++;
        }
    }
    return pageFaults;
}

int main() {
    int pages[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};
    int n = sizeof(pages) / sizeof(pages[0]);

    int frameCount;
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    int pageFaults = fifo(pages, n, frameCount);
    printf("Number of page faults: %d\n", pageFaults);

    return 0;
}
    