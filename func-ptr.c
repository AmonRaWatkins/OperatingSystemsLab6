#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Process { 
    int pid; // Process ID 
    int bt;  // Burst Time 
    int art; // Arrival Time 
    int wt;  // Waiting time
    int tat; // Turnaround time
    int pri; // Priority
} ProcessType;

// Function pointer type for comparing processes
typedef int (*Comparer)(const void *a, const void *b);

// Function to compare two processes based on arrival time, priority, and PID
int my_comparer(const void *this, const void *that) {
    const ProcessType *process1 = (const ProcessType *)this;
    const ProcessType *process2 = (const ProcessType *)that;

    // Compare by arrival time first
    if (process1->art != process2->art) {
        return process1->art - process2->art; // Ascending order
    }

    // If arrival times are the same, compare by priority
    if (process1->pri != process2->pri) {
        return process1->pri - process2->pri; // Ascending order (lower number = higher priority)
    }

    // If both arrival times and priorities are the same, compare by PID
    return process1->pid - process2->pid; // Ascending order
}

// Function to parse the input file and initialize process list
ProcessType* parse_file(FILE *file, int *n) {
    ProcessType *processes = malloc(100 * sizeof(ProcessType)); // Adjust size as necessary
    if (!processes) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    *n = 0;

    while (fscanf(file, "%d %d %d %d", 
                  &processes[*n].pid,
                  &processes[*n].bt,
                  &processes[*n].art,
                  &processes[*n].pri) == 4) {
        printf("Read Process: PID=%d, BT=%d, AT=%d, PRI=%d\n", 
               processes[*n].pid, processes[*n].bt, processes[*n].art, processes[*n].pri);
        (*n)++;
        if (*n >= 100) break; // Prevent overflow
    }

    return processes;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./func-ptr <input-file-path>\n");
        return 1;
    }

    // Open the input file
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Invalid filepath\n");
        return 1;
    }

    // Parse the file
    int num_processes = 0;
    ProcessType *processes = parse_file(input_file, &num_processes);

    // Sort the input using qsort and your custom comparator
    Comparer process_comparer = &my_comparer;
    qsort(processes, num_processes, sizeof(ProcessType), process_comparer);

    // Print sorted data
    printf("Sorted Processes:\n");
    printf("PID | Priority | Arrival Time\n");
    
    for (int i = 0; i < num_processes; i++) {
        printf("%d | %d | %d\n", processes[i].pid, processes[i].pri, processes[i].art);
    }

    // Clean up
    free(processes);
    fclose(input_file);
    
    return 0;
}