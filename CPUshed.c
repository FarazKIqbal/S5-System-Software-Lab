#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int remaining_time; // Used for Round Robin
    int completed; // 0 for not completed, 1 for completed
};

void calculateWaitingTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void fcfs(struct Process proc[], int n) {
    int total_time = 0;

    // Sorting processes by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (total_time < proc[i].arrival_time)
            total_time = proc[i].arrival_time;

        proc[i].waiting_time = total_time - proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        total_time += proc[i].burst_time;
    }

    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);
}

void sjfNonPreemptive(struct Process proc[], int n) {
    int total_time = 0, completed = 0;

    // Sorting based on arrival time to ensure the earliest process is selected first
    while (completed != n) {
        int min_index = -1;
        int min_burst = 1e9;

        // Selecting the process with the shortest burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (proc[i].completed == 0 && proc[i].arrival_time <= total_time && proc[i].burst_time < min_burst) {
                min_burst = proc[i].burst_time;
                min_index = i;
            }
        }

        // If no process has arrived yet, increment time
        if (min_index == -1) {
            total_time++;
            continue;
        }

        // Process the selected shortest job
        proc[min_index].waiting_time = total_time - proc[min_index].arrival_time;
        proc[min_index].turnaround_time = proc[min_index].waiting_time + proc[min_index].burst_time;
        proc[min_index].completed = 1;
        completed++;
        total_time += proc[min_index].burst_time;
    }

    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);
}

void roundRobin(struct Process proc[], int n, int quantum) {
    int total_time = 0, completed = 0;

    while (completed != n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                done = 0;
                if (proc[i].remaining_time > quantum) {
                    total_time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    total_time += proc[i].remaining_time;
                    proc[i].waiting_time = total_time - proc[i].burst_time - proc[i].arrival_time;
                    proc[i].remaining_time = 0;
                    completed++;
                }
            }
        }
        if (done) break;
    }

    calculateTurnaroundTime(proc, n);
}

void priorityScheduling(struct Process proc[], int n) {
    int total_time = 0, completed = 0;

    while (completed != n) {
        int min_index = -1;
        int min_priority = 1e9;

        for (int i = 0; i < n; i++) {
            if (proc[i].completed == 0 && proc[i].arrival_time <= total_time && proc[i].priority < min_priority) {
                min_priority = proc[i].priority;
                min_index = i;
            }
        }

        if (min_index == -1) {
            total_time++;
            continue;
        }

        proc[min_index].waiting_time = total_time - proc[min_index].arrival_time;
        proc[min_index].turnaround_time = proc[min_index].waiting_time + proc[min_index].burst_time;
        proc[min_index].completed = 1;
        completed++;
        total_time += proc[min_index].burst_time;
    }

    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);
}

void printResults(struct Process proc[], int n) {
    printf("\nPID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].priority, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    int n, choice, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
        proc[i].pid = i + 1;
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].completed = 0;
    }

    printf("Choose the scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF (Non-Preemptive)\n");
    printf("3. Round Robin\n");
    printf("4. Priority Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(proc, n);
            break;
        case 2:
            sjfNonPreemptive(proc, n);
            break;
        case 3:
            printf("Enter the time quantum: ");
            scanf("%d", &quantum);
            roundRobin(proc, n, quantum);
            break;
        case 4:
            priorityScheduling(proc, n);
            break;
        default:
            printf("Invalid choice.\n");
            exit(0);
    }

    printResults(proc, n);
    return 0;
}
