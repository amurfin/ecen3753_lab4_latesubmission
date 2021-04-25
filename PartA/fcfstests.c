#include <stdlib.h>
#include <stdio.h>
#include "ctest.h"
#include "fcfs.h"

// 2 test arrays
// test test_process #
// test exe, wait, turn
// test avg wait times
// test avg turn time


// fcfs1 {1, 2, 3, 4, 5}
// expected process_ids {0, 1, 2, 3, 4}
// expected exetimes {1, 2, 3, 4, 5}
// expected waittimes {0, 1, 3, 6, 10}
// expected turn times {1, 3, 6, 10, 15}
// expeted avg wait time = 20 / 5 = 4
// expected avg turn times = 35 / 5 = 7
// Note: the name in the first parameter slot must match all tests in that group
CTEST_DATA(fcfs1) {
    struct task_t task[5];
    int size;
};

CTEST_SETUP(fcfs1) {
    int execution[] = {1, 2, 3, 4, 5};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    first_come_first_served(data->task, data->size);
}

CTEST2(fcfs1, test_process_id) {
  int x;
  // loop through each element of task buffer, confirm process id's as expected
  for (x = 0; x < data->size; x++)
  {
    ASSERT_EQUAL(x, (int)data->task[x].process_id);
  }
}

CTEST2(fcfs1, test_exe_time)
{
  int x;
  // since this execution time is 1,2,3,4,5 I can use a for loop
  for (x = 1; x < (data->size + 1); x++)
    ASSERT_EQUAL(x, (int)data->task[x - 1].execution_time);
}

CTEST2(fcfs1, test_wait_time)
{
  ASSERT_EQUAL(0, (int)data->task[0].waiting_time);
  ASSERT_EQUAL(1, (int)data->task[1].waiting_time);
  ASSERT_EQUAL(3, (int)data->task[2].waiting_time);
  ASSERT_EQUAL(6, (int)data->task[3].waiting_time);
  ASSERT_EQUAL(10, (int)data->task[4].waiting_time);
}

CTEST2(fcfs1, test_turn_time)
{
  ASSERT_EQUAL(1, (int)data->task[0].turnaround_time);
  ASSERT_EQUAL(3, (int)data->task[1].turnaround_time);
  ASSERT_EQUAL(6, (int)data->task[2].turnaround_time);
  ASSERT_EQUAL(10, (int)data->task[3].turnaround_time);
  ASSERT_EQUAL(15, (int)data->task[4].turnaround_time);
}

CTEST2(fcfs1, test_avg_wait_time)
{
  ASSERT_EQUAL(4, calculate_average_wait_time(data->task, data->size));
}

CTEST2(fcfs1, test_avg_turn_time)
{
  ASSERT_EQUAL(7, calculate_average_turn_around_time(data->task, data->size));
}

// fcfs2 {3, 10, 4, 1, 12}
// expected process_ids {0, 1, 2, 3, 4}
// expected exetimes {3, 10, 4, 1, 12}
// expected waittimes {0, 3, 13, 17, 18}
// expected turn times {3, 13, 17, 18, 30}
// expeted avg wait time = 51 / 5 = 10
// expected avg turn times = 81 / 5 = 16
// Note: the name in the first parameter slot must match all tests in that group
CTEST_DATA(fcfs2) {
    struct task_t task[5];
    int size;
};

CTEST_SETUP(fcfs2) {
    int execution[] = {3, 10, 4, 1, 12};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    first_come_first_served(data->task, data->size);
}

CTEST2(fcfs2, test_process_id) {
  int x;
  // loop through each element of task buffer, confirm process id's as expected
  for (x = 0; x < data->size; x++)
  {
    ASSERT_EQUAL(x, (int)data->task[x].process_id);
  }
}

CTEST2(fcfs2, test_exe_time)
{
  ASSERT_EQUAL(3, (int)data->task[0].execution_time);
  ASSERT_EQUAL(10, (int)data->task[1].execution_time);
  ASSERT_EQUAL(4, (int)data->task[2].execution_time);
  ASSERT_EQUAL(1, (int)data->task[3].execution_time);
  ASSERT_EQUAL(12, (int)data->task[4].execution_time);
}

CTEST2(fcfs2, test_wait_time)
{
  ASSERT_EQUAL(0, (int)data->task[0].waiting_time);
  ASSERT_EQUAL(3, (int)data->task[1].waiting_time);
  ASSERT_EQUAL(13, (int)data->task[2].waiting_time);
  ASSERT_EQUAL(17, (int)data->task[3].waiting_time);
  ASSERT_EQUAL(18, (int)data->task[4].waiting_time);
}

CTEST2(fcfs2, test_turn_time)
{
  ASSERT_EQUAL(3, (int)data->task[0].turnaround_time);
  ASSERT_EQUAL(13, (int)data->task[1].turnaround_time);
  ASSERT_EQUAL(17, (int)data->task[2].turnaround_time);
  ASSERT_EQUAL(18, (int)data->task[3].turnaround_time);
  ASSERT_EQUAL(30, (int)data->task[4].turnaround_time);
}

CTEST2(fcfs2, test_avg_wait_time)
{
  ASSERT_EQUAL(10, calculate_average_wait_time(data->task, data->size));
}

CTEST2(fcfs2, test_avg_turn_time)
{
  ASSERT_EQUAL(16, calculate_average_turn_around_time(data->task, data->size));
}
