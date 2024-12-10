#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include "util.h"
#include "process.h"

/**
 * Returns an array of process that are parsed from
 * the input file descriptor passed as argument
 * CAUTION: You need to free up the space that is allocated
 * by this function
 */
Process *parse_file(FILE *f, int *num_processes) {
    size_t s = 0;
    char *headers = NULL;
    size_t line_len = 0;

    // Ignore the headers if present
    line_len = getline(&headers, &line_len, f);
    free(headers);  // Free header after reading

    // Allocate process array on heap
    Process *pptr = (Process *)malloc(P_SIZE * sizeof(Process));

    // Read each line of the file and populate the process structure
    while (fscanf(f, "%d,%d,%d\n", &pptr[s].pid, &pptr[s].arrival_time, &pptr[s].priority) == 3) {
        s++;
    }

    // Set the number of processes read
    *num_processes = s;

    return pptr;
}
