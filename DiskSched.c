#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

int rnum, head, dir, MAX_TRACKS;

int FCFS(int request[MAX_REQUESTS]) {
    int totalTime = 0;

    printf("FCFS Sequence:\n");
    for (int i = 0; i < rnum; i++) {
        printf("%d -> ", request[i]);
        totalTime += abs(head - request[i]);
        head = request[i];
    }
    printf("\n");

    return totalTime;
}

int SCAN(int request[MAX_REQUESTS]) {
    int totalTime = 0;
    int index = 0;

    for (int i = 0; i < rnum; i++) {
        for (int j = 0; j < rnum - i - 1; j++) {
            if (request[j] > request[j + 1]) {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < rnum; i++) {
        if (request[i] >= head) {
            index = i;
            break;
        }
    }

    if (dir == 1) {
        printf("SCAN Sequence:\n");
        for (int i = index; i < rnum; i++) {
            printf("%d -> ", request[i]);
            totalTime += abs(head - request[i]);
            head = request[i];
        }

        if (index != 0) {
            totalTime += abs(MAX_TRACKS - request[rnum - 1] - 1); // Checks for the furthest tracks and calculates the distance
            head = MAX_TRACKS - 1;
            printf("%d -> ", head);
            for (int i = index - 1; i >= 0; i--) {
                printf("%d -> ", request[i]);
                totalTime += abs(head - request[i]);
                head = request[i];
            }
        }
    } else {
        printf("SCAN Sequence:\n");
        for (int i = index - 1; i >= 0; i--) {
            printf("%d -> ", request[i]);
            totalTime += abs(head - request[i]);
            head = request[i];
        }

        if (index != rnum - 1) {
            totalTime += abs(request[0] - 0);
            head = 0;
            printf("%d -> ", head);
            for (int i = index + 1; i < rnum; i++) {
                printf("%d -> ", request[i]);
                totalTime += abs(head - request[i]);
                head = request[i];
            }
        }
    }

    printf("\n");

    return totalTime;
}

int CSCAN(int request[MAX_REQUESTS]) {
    int totalTime = 0;
    int index = 0;

    for (int i = 0; i < rnum; i++) {
        for (int j = 0; j < rnum - i - 1; j++) {
            if (request[j] > request[j + 1]) {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < rnum; i++) {
        if (request[i] >= head) {
            index = i;
            break;
        }
    }

    if (dir == 1) {
        printf("C-SCAN Sequence:\n");
        for (int i = index; i < rnum; i++) {
            printf("%d -> ", request[i]);
            totalTime += abs(head - request[i]);
            head = request[i];
        }

        if (index != 0) {
            totalTime += abs(MAX_TRACKS - request[rnum - 1] - 1); // Checks for the furthest tracks and calculates the distance
            head = 0;
            printf("%d -> ", head);
            totalTime += abs(MAX_TRACKS - 1);
            printf("%d -> ", head);
            for (int i = 0; i < index; i++) {
                printf("%d -> ", request[i]);
                totalTime += abs(head - request[i]);
                head = request[i];
            }
        }
    } else {
        printf("C-SCAN Sequence:\n");
        for (int i = index - 1; i >= 0; i--) {
            printf("%d -> ", request[i]);
            totalTime += abs(head - request[i]);
            head = request[i];
        }

        if (index != rnum - 1) {
            totalTime += abs(head - 0);
            head = MAX_TRACKS - 1;
            printf("%d -> ", head);
            totalTime += abs(MAX_TRACKS - 1 - 0);
            printf("%d -> ", head);
        }

        for (int i = rnum - 1; i >= index; i--) {
            printf("%d -> ", request[i]);
            totalTime += abs(head - request[i]);
            head = request[i];
        }
    }

    printf("\n");

    return totalTime;
}

int main() {
    printf("\nEnter The Maximum Number Of Tracks: ");
    scanf("%d", &MAX_TRACKS);

    printf("\nEnter The Number Of Requests: ");
    scanf("%d", &rnum);

    int requests[rnum];
    for (int i = 0; i < rnum; i++) {
        printf("Enter The Disk Number - %d: ", (i + 1));
        scanf("%d", &requests[i]);
    }

    printf("\nPosition of Head: ");
    scanf("%d", &head);

    printf("\nEnter The Direction (0/1): ");
    scanf("%d", &dir);

    while (1) {
        printf("\nChoose a disk scheduling algorithm:\n");
        printf("1. FCFS\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nTotal Time (FCFS)= %d ms", FCFS(requests));
                break;
            case 2:
                printf("\nTotal Time (SCAN)= %d ms", SCAN(requests));
                break;
            case 3:
                printf("\nTotal Time (C-SCAN)= %d ms", CSCAN(requests));
                break;
            case 4:
                exit(0);
            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
