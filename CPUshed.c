#include <stdio.h>
#include <stdlib.h>

struct P {
    int pid, at, bt, pr, wt, tat, rt, comp;
};

void calcWT(struct P p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void calcTAT(struct P p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
    }
}

void fcfs(struct P p[], int n) {
    int tt = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct P temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (tt < p[i].at)
            tt = p[i].at;
        p[i].wt = tt - p[i].at;
        p[i].tat = p[i].wt + p[i].bt;
        tt += p[i].bt;
    }

    calcWT(p, n);
    calcTAT(p, n);
}

void sjfNP(struct P p[], int n) {
    int tt = 0, comp = 0;

    while (comp != n) {
        int minIdx = -1, minBt = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].comp == 0 && p[i].at <= tt && p[i].bt < minBt) {
                minBt = p[i].bt;
                minIdx = i;
            }
        }

        if (minIdx == -1) {
            tt++;
            continue;
        }

        p[minIdx].wt = tt - p[minIdx].at;
        p[minIdx].tat = p[minIdx].wt + p[minIdx].bt;
        p[minIdx].comp = 1;
        comp++;
        tt += p[minIdx].bt;
    }

    calcWT(p, n);
    calcTAT(p, n);
}

void rr(struct P p[], int n, int q) {
    int tt = 0, comp = 0;

    while (comp != n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                done = 0;
                if (p[i].rt > q) {
                    tt += q;
                    p[i].rt -= q;
                } else {
                    tt += p[i].rt;
                    p[i].wt = tt - p[i].bt - p[i].at;
                    p[i].rt = 0;
                    comp++;
                }
            }
        }
        if (done) break;
    }

    calcTAT(p, n);
}

void priority(struct P p[], int n) {
    int tt = 0, comp = 0;

    while (comp != n) {
        int minIdx = -1, minPr = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].comp == 0 && p[i].at <= tt && p[i].pr < minPr) {
                minPr = p[i].pr;
                minIdx = i;
            }
        }

        if (minIdx == -1) {
            tt++;
            continue;
        }

        p[minIdx].wt = tt - p[minIdx].at;
        p[minIdx].tat = p[minIdx].wt + p[minIdx].bt;
        p[minIdx].comp = 1;
        comp++;
        tt += p[minIdx].bt;
    }

    calcWT(p, n);
    calcTAT(p, n);
}

void printRes(struct P p[], int n) {
    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].wt, p[i].tat);
    }
}

int main() {
    int n, ch, q;
    printf("Enter # of processes: ");
    scanf("%d", &n);

    struct P p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter AT, BT, PR for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].pid = i + 1;
        p[i].rt = p[i].bt;
        p[i].comp = 0;
    }

    printf("Choose algorithm:\n1. FCFS\n2. SJF (NP)\n3. RR\n4. Priority\nEnter choice: ");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            fcfs(p, n);
            break;
        case 2:
            sjfNP(p, n);
            break;
        case 3:
            printf("Enter quantum: ");
            scanf("%d", &q);
            rr(p, n, q);
            break;
        case 4:
            priority(p, n);
            break;
        default:
            printf("Invalid choice.\n");
            exit(0);
    }

    printRes(p, n);
    return 0;
}
