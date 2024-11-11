#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PROCESSES 100

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void calculate_times(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void print_results(struct Process processes[], int n)
{
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\ tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Aierage Turnaround Time: %.2f\n", avg_turnaround_time);
}

void fcfs(struct Process processes[], int n)
{
    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (current_time < processes[i].arrival_time)
            current_time = processes[i].arrival_time;
        processes[i].completion_time = current_time + processes[i].burst_time;
        current_time = processes[i].completion_time;
    }

    calculate_times(processes, n);
    print_results(processes, n);
}

void sjf_preemptive(struct Process processes[], int n)
{
    struct Process temp[MAX_PROCESSES];
    int current_time = 0, completed = 0;

    for (int i = 0; i < n; i++)
    {
        temp[i] = processes[i];
        temp[i].remaining_time = processes[i].burst_time;
    }

    while (completed != n)
    {
        int shortest = -1, min_burst = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (temp[i].arrival_time <= current_time && temp[i].remaining_time < min_burst && temp[i].remaining_time > 0)
            {
                shortest = i;
                min_burst = temp[i].remaining_time;
            }
        }

        if (shortest == -1)
        {
            current_time++;
        }
        else
        {
            temp[shortest].remaining_time--;
            current_time++;

            if (temp[shortest].remaining_time == 0)
            {
                completed++;
                temp[shortest].completion_time = current_time;
            }
        }
    }

    calculate_times(temp, n);
    print_results(temp, n);
}

void sjf_non_preemptive(struct Process processes[], int n)
{
    struct Process temp[MAX_PROCESSES];
    int current_time = 0, completed = 0;

    for (int i = 0; i < n; i++)
        temp[i] = processes[i];
    while (completed != n)
    {
        int shortest = -1, min_burst = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (temp[i].arrival_time <= current_time && temp[i].burst_time < min_burst && temp[i].remaining_time > 0)
            {
                shortest = i;
                min_burst = temp[i].burst_time;
            }
        }

        if (shortest == -1)
        {
            current_time++;
        }
        else
        {
            temp[shortest].completion_time = current_time + temp[shortest].burst_time;
            current_time = temp[shortest].completion_time;
            temp[shortest].remaining_time = 0;
            completed++;
        }
    }

    calculate_times(temp, n);
    print_results(temp, n);
}

void priority_scheduling(struct Process processes[], int n)
{
    struct Process temp[MAX_PROCESSES];
    int current_time = 0, completed = 0;

    for (int i = 0; i < n; i++)
        temp[i] = processes[i];
    while (completed != n)
    {
        int highest_priority = -1, min_priority = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (temp[i].arrival_time <= current_time && temp[i].priority < min_priority && temp[i].remaining_time > 0)
            {
                highest_priority = i;
                min_priority = temp[i].priority;
            }
        }

        if (highest_priority == -1)
        {
            current_time++;
        }
        else
        {
            temp[highest_priority].completion_time = current_time + temp[highest_priority].burst_time;
            current_time = temp[highest_priority].completion_time;
            temp[highest_priority].remaining_time = 0;
            completed++;
        }
    }

    calculate_times(temp, n);
    print_results(temp, n);
}

void round_robin(struct Process processes[], int n, int time_slice)
{
    struct Process temp[MAX_PROCESSES];
    int current_time = 0, completed = 0;
    int queue[MAX_PROCESSES], front = 0, rear = 0;
    for (int i = 0; i < n; i++)
    {
        temp[i] = processes[i];
        temp[i].remaining_time = processes[i].burst_time;
    }

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (temp[i].arrival_time == current_time)
            {
                queue[rear] = i;
                rear = (rear + 1) % MAX_PROCESSES;
            }
        }

        if (front == rear)
        {
            current_time++;
            continue;
        }

        int index = queue[front];
        front = (front + 1) % MAX_PROCESSES;

        if (temp[index].remaining_time <= time_slice)
        {
            current_time += temp[index].remaining_time;
            temp[index].completion_time = current_time;
            temp[index].remaining_time = 0;
            completed++;
        }
        else
        {
            current_time += time_slice;
            temp[index].remaining_time -= time_slice;
            queue[rear] = index;
            rear = (rear + 1) % MAX_PROCESSES;
        }
    }

    calculate_times(temp, n);
    print_results(temp, n);
}

int main()
{
    struct Process processes[] = {
        {1, 0, 20, 2, 20},
        {2, 4, 10, 1, 10},
        {3, 6, 15, 1, 15},
        {4, 10, 5, 2, 5}};
    int n = sizeof(processes) / sizeof(processes[0]);

    int choice;
    do
    {
        printf("\nCPU Scheduling Algorithms:\n");
        printf("1. FCFS Scheduling\n");
        printf("2. Preemptive SJF Scheduling\n");
        printf("3. Non-Preemptive SJF Scheduling\n");
        printf("4. Priority Scheduling\n");
        printf("5. Round Robin Schedling\n");
        printf("6. Exit\n");
        printf("Enter your choice (processes-6): ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nFCFS Scheduling:\n");
            fcfs(processes, n);
            break;
        case 2:
            printf("\nPreemptive SJF Scheduling:\n");
            sjf_preemptive(processes, n);
            break;
        case 3:
            printf("\nNon-Preemptive SJF Scheduling:\n");
            sjf_non_preemptive(processes, n);
            break;
        case 4:
            printf("\nPriority Scheduling:\n");
            priority_scheduling(processes, n);
            break;
        case 5:
            printf("\nRound Robin Scheduling (Time Slice = 2):\n");
            round_robin(processes, n, 2);
            break;
        case 6:
            printf("Exiting program…\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}