#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PROCESSES 5
#define TIME_QUANTUM 2

struct Process
{
	int pid;	// Process ID 

	int arrival_time;	// Arrival time 

	int cpu_burst_time;	// CPU burst time 

	int remaining_time;	// Remaining CPU burst time 

	int waiting_time;	// Waiting time 

	int turnaround_time;	// Turnaround time 

};

int main()
{
	int total_waiting_time = 0, total_turnaround_time = 0;

	int i, j, t = 0, num_processes = 0;

	struct Process processes[MAX_PROCESSES];

	srand(time(NULL));	// Seed the random number generator 

	// Generate random processes 

	printf("Generating processes...\n");

	for (i = 0; i < MAX_PROCESSES; i++)
	{
		processes[i].pid = i + 1;

		processes[i].arrival_time = rand() % 5;

		processes[i].cpu_burst_time = rand() % 5 + 1;

		processes[i].remaining_time = processes[i].cpu_burst_time;

		processes[i].waiting_time = 0;

		processes[i].turnaround_time = 0;

		printf("Process %d - Arrival Time: %d, CPU Burst Time: %d\n",
			processes[i].pid, processes[i].arrival_time, processes[i].cpu_burst_time);
	}

	printf("\n");

	num_processes = MAX_PROCESSES;

	// Run the Round Robin scheduling algorithm 

	printf("Running Round Robin scheduling algorithm...\n");

	while (num_processes > 0)
	{
		for (i = 0; i < MAX_PROCESSES; i++)
		{
			if (processes[i].remaining_time > 0)
			{
			 	// Process has arrived 

				if (processes[i].arrival_time <= t)
				{
				 		// Process is running 

					printf("Time: %d - Running process %d (Remaining Time: %d)\n",
						t, processes[i].pid, processes[i].remaining_time);

					// Reduce remaining time by time quantum 

					if (processes[i].remaining_time <= TIME_QUANTUM)
					{
						t += processes[i].remaining_time;

						processes[i].remaining_time = 0;
					}
					else
					{
						t += TIME_QUANTUM;

						processes[i].remaining_time -= TIME_QUANTUM;
					}

					// Process has finished 

					if (processes[i].remaining_time == 0)
					{
						num_processes--;

						processes[i].turnaround_time = t - processes[i].arrival_time;

						processes[i].waiting_time = processes[i].turnaround_time - processes[i].cpu_burst_time;

						total_waiting_time += processes[i].waiting_time;

						total_turnaround_time += processes[i].turnaround_time;

						printf("Time: %d - Process %d has finished (Turnaround Time: %d, Waiting Time: %d)\n",
							t, processes[i].pid, processes[i].turnaround_time, processes[i].waiting_time);
					}
				}
			}
		}
	}

	// Print results 

	printf("\nAverage Waiting Time: %.2f\n", (float) total_waiting_time / MAX_PROCESSES);

	printf("Average Turnaround Time: %.2f\n", (float) total_turnaround_time / MAX_PROCESSES);

	return 0;

}