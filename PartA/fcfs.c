#include "fcfs.h"
#include "queue.h"
#include <stdio.h>

void init(struct task_t *task, int *execution, int size) {
  int x;
  // init task array
  // initialize each element in "size" number of tasks
  for (x = 0; x < size; x++)
  {
    task[x].process_id = x;
    task[x].execution_time = execution[x];
    task[x].turnaround_time = 0;
    task[x].waiting_time = 0;
  }
}

void first_come_first_served(struct task_t *task, int size) {
  struct task_t * curr_node;
  // variable to hold previous node's turn time (current nodes wait time)
  int curr_total_wait_time = 0;

  // create Queue
  struct node_t * fcfs_Q = create_queue(task, size);

  // go through each node of queue, processing and filling wait & turn times
  // based on execution times
  while (!is_empty(&fcfs_Q))
  {
    // peek data in to "curr_node"
    curr_node = peek(&fcfs_Q);
    curr_node->waiting_time = curr_total_wait_time;
    curr_node->turnaround_time = curr_total_wait_time + curr_node->execution_time;
    // add this node's exe time to total wait time
    curr_total_wait_time += curr_node->execution_time;
    // pop this node off
    pop(&fcfs_Q);
  }
}

float calculate_average_wait_time(struct task_t *task, int size) {
  int x;
  float sum = 0;

  // sum wait times
  for (x = 0; x < size; x++)
    sum += task[x].waiting_time;

  return sum / (float)size;
}

float calculate_average_turn_around_time(struct task_t *task, int size) {
  int x;
  float sum = 0;

  // sum turn times
  for (x = 0; x < size; x++)
    sum += task[x].turnaround_time;

  return sum / (float)size;
}
