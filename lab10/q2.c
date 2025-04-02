#include <stdio.h>
#include <stdlib.h>

void lru(int *pages, int pageCount, int frameCount) {
    int *frames = (int *)calloc(frameCount, sizeof(int)); // Frames to store pages
    int *lastUsed = (int *)calloc(frameCount, sizeof(int)); // To track the last time a page was used
    int *frequency = (int *)calloc(frameCount, sizeof(int)); // To keep track of pages in memory
    int pageFaults = 0;

    // Initialize the frames with -1 (indicating empty slots)
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                // Update the last used time (current iteration) for the found page
                lastUsed[j] = i;
                break;
            }
        }

        // If the page is not found, a page fault occurs
        if (!found) {
            // Find the least recently used page
            int lruIndex = 0;
            for (int j = 1; j < frameCount; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }

            // Replace the least recently used page
            frames[lruIndex] = page;
            lastUsed[lruIndex] = i;
            pageFaults++;
        }

        // Print current state of frames
        printf("Page %d -> ", page);
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", pageFaults);

    // Free allocated memory
    free(frames);
    free(lastUsed);
    free(frequency);
}

int main() {
    int frameCount, pageCount;

    // Input number of frames and page reference string size
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter number of pages: ");
    scanf("%d", &pageCount);

    int *pages = (int *)malloc(pageCount * sizeof(int));

    // Input page reference string
    printf("Enter page reference string: ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    printf("\nLRU (Least Recently Used) Page Replacement:\n");
    lru(pages, pageCount, frameCount);

    // Free dynamically allocated memory
    free(pages);

    return 0;
}
