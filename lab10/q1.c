#include <stdio.h>
#include <stdlib.h>

void fifo(int *pages, int pageCount, int frameCount) {
    int *frames = (int *)calloc(frameCount, sizeof(int));
    int *frequency = (int *)calloc(frameCount, sizeof(int));
    int pageFaults = 0, currentFrame = 0;

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in one of the frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If page is not found, a page fault occurs
        if (!found) {
            frames[currentFrame] = page;
            currentFrame = (currentFrame + 1) % frameCount;
            pageFaults++;
        }

        // Print frames
        printf("Page %d -> ", page);
        for (int j = 0; j < frameCount; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", pageFaults);

    // Free allocated memory
    free(frames);
    free(frequency);
}

void optimal(int *pages, int pageCount, int frameCount) {
    int *frames = (int *)calloc(frameCount, sizeof(int));
    int pageFaults = 0;

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in one of the frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If page is not found, a page fault occurs
        if (!found) {
            int farthest = -1, indexToReplace = -1;

            // Find the page to replace (the one that won't be used for the longest time in the future)
            for (int j = 0; j < frameCount; j++) {
                int nextUse = -1;
                for (int k = i + 1; k < pageCount; k++) {
                    if (pages[k] == frames[j]) {
                        nextUse = k;
                        break;
                    }
                }
                // If the page is not used again, it's the optimal one to replace
                if (nextUse == -1) {
                    indexToReplace = j;
                    break;
                }
                // If the page will be used later, track the farthest usage
                if (nextUse > farthest) {
                    farthest = nextUse;
                    indexToReplace = j;
                }
            }

            // Replace the page
            frames[indexToReplace] = page;
            pageFaults++;
        }

        // Print frames
        printf("Page %d -> ", page);
        for (int j = 0; j < frameCount; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", pageFaults);

    // Free allocated memory
    free(frames);
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

    int choice;
    printf("\nSelect Page Replacement Algorithm:\n");
    printf("1. FIFO (First In, First Out)\n");
    printf("2. Optimal\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nFIFO Page Replacement:\n");
            fifo(pages, pageCount, frameCount);
            break;
        case 2:
            printf("\nOptimal Page Replacement:\n");
            optimal(pages, pageCount, frameCount);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    // Free dynamically allocated memory
    free(pages);

    return 0;
}
