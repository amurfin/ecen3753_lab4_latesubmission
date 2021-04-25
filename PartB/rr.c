#include "rr.h"
#include "queue.h"
#include <stdio.h>

void init(struct task_t *task, int *execution, int size) {
  int x;
  // loop thru each element of task buffer, adding data
  for (x = 0; x < size; x++)
  {
    task[x].process_id = x;
    task[x].execution_time = execution[x];
    task[x].waiting_time = 0;
    task[x].turnaround_time = 0;
    task[x].left_to_execute = execution[x];
  }
}

void round_robin(struct task_t *task, int quantum, int size) {
  struct task_t * curr_node;
  int curr_total_time = 0;
  int actual_time_used;
    // Hints:
    // 1. Create Queue based on the task array
    // 2. Process each "task" in round robin fashion
    // 3. You can process by pushing and popping items from the queue

    // create Queue
    struct node_t * rr_Q = create_queue(task, size);

    // looping thru tasks..
    while (!is_empty(&rr_Q))
    {
      // peek to get top node
      curr_node = peek(&rr_Q);
      // pop node off (will decide if need to re-push or not)
      pop(&rr_Q);

      // decrement left to execute by quantum
      curr_node->left_to_execute -= quantum;

      // if this finished this task and more, find actual time used
      if (curr_node->left_to_execute < 0)
      {
        actual_time_used = (curr_node->left_to_execute + quantum);
        // actual_time_used = (curr_node->left_to_execute * -1) % quantum;
        curr_node->left_to_execute = 0;
      }
      // if this didn't finish the task or finished straight to zero, actual
      // time used was quantum
      else if (curr_node->left_to_execute >= 0)
        actual_time_used = quantum;
      // add time used to system wait time
      curr_total_time += actual_time_used;

      // if this task is finished, calculate wait and turn time, else re-push
      if (curr_node->left_to_execute == 0)
      {
        curr_node->turnaround_time = curr_total_time;
        curr_node->waiting_time = curr_total_time - curr_node->execution_time;
      }
      else
        if (is_empty(&rr_Q))
          rr_Q = create_queue(curr_node, 1);
        else
          push(&rr_Q, curr_node);
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
