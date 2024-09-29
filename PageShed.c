#include <stdio.h>
#include <stdlib.h>

int hitCount = 0, missCount = 0;
int MAX_FRAMES;
int frames[100];
int counter[100];

void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }
}

void displayFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

// Function to find the least frequently used frame
int findLFU() {
    int min = counter[0];
    int lfu_frame = 0;

    for (int i = 1; i < MAX_FRAMES; i++) {
        if (counter[i] < min) {
            min = counter[i];
            lfu_frame = i;
        }
    }

    return lfu_frame;
}

// Function to find the least recently used frame
int findLRU() {
    int max = counter[0];
    int lru_frame = 0;

    for (int i = 1; i < MAX_FRAMES; i++) {
        if (counter[i] > max) {
            max = counter[i];
            lru_frame = i;
        }
    }

    return lru_frame;
}

void FIFO(int pages[], int n) {
    int page_faults = 0;
    int front = -1, rear = -1;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page already exists in frames
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                hitCount++;
                printf("Page %d is already in memory\n", page);
                break;
            }
        }

        if (!found) {
            if ((rear + 1) % MAX_FRAMES != front) {
                rear = (rear + 1) % MAX_FRAMES;
                frames[rear] = page;
            } else {
                front++;
                frames[front] = page;
            }
            page_faults++;
            missCount++;
            printf("Page %d is loaded in frame %d\n", page, rear);
        }

        displayFrames();
    }

    printf("Total Page Faults: %d\n", page_faults);
    printf("Hit Count: %d\n", hitCount);
    printf("Miss Count: %d\n", missCount);
    printf("\nHit Ratio = %f", (float)hitCount / (float)(hitCount + missCount));
    printf("\nMiss Ratio = %f", (float)missCount / (float)(hitCount + missCount));
}

void LFU(int pages[], int n) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page already exists in frames
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                counter[j]++;
                hitCount++;
                printf("Page %d is already in memory\n", page);
                break;
            }
        }

        if (!found) {
            int lfu_frame = findLFU();
            frames[lfu_frame] = page;
            counter[lfu_frame] = 1;
            page_faults++;
            missCount++;
            printf("Page %d is loaded in frame %d\n", page, lfu_frame);
        }

        displayFrames();
    }

    printf("Total Page Faults: %d\n", page_faults);
    printf("Hit Count: %d\n", hitCount);
    printf("Miss Count: %d\n", missCount);
    printf("\nHit Ratio = %f", (float)hitCount / (float)(hitCount + missCount));
    printf("\nMiss Ratio = %f", (float)missCount / (float)(hitCount + missCount));
}

void LRU(int pages[], int n) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page already exists in frames
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                hitCount++;
                printf("Page %d is Already Inserted \n", page);
                break;
            }
        }

        if (!found) {
            int lru_frame = findLRU();
            frames[lru_frame] = page;
            counter[lru_frame] = 0;
            page_faults++;
            missCount++;
            printf("Page %d is Loaded in Frame %d\n", page, lru_frame);
        }

        // Increment counter for all frames
        for (int j = 0; j < MAX_FRAMES; j++) {
            counter[j]++;
        }

        // Reset counter for the used frame
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                counter[j] = 0;
                break;
            }
        }

        displayFrames();
    }

    printf("Hit Count: %d\n", hitCount);
    printf("Miss Count: %d\n", missCount);
    printf("\nHit Ratio = %f", (float)hitCount / (float)(hitCount + missCount));
    printf("\nMiss Ratio = %f", (float)missCount / (float)(hitCount + missCount));
}

int main() {
    int n, choice;

    printf("Enter The Number of Pages: ");
    scanf("%d", &n);
    int pages[n];

    printf("Enter The Page Reference Sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter The Number of Frames: ");
    scanf("%d", &MAX_FRAMES);

    initialize();

    while (1) {
        printf("\nChoose a page replacement algorithm:\n");
        printf("1. FIFO\n");
        printf("2. LFU\n");
        printf("3. LRU\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                FIFO(pages, n);
                break;
            case 2:
                LFU(pages, n);
                break;
            case 3:
                LRU(pages, n);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
