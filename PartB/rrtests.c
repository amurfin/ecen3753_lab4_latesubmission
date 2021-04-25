#include <stdlib.h>
#include "ctest.h"
#include "rr.h"

// 2 test arrays
// test test_process #
// test exe, wait, turn
// test avg wait times
// test avg turn time


// rr1 {1, 2, 3}, quantum 2
// expected process_ids = {0, 1, 2}
// finish [0] in 1 (wait = 0, turn = 1)
// finish [1] in 2 (wait = 1, turn = 3)
// dec    [2] by 2
// finish [2] in 1 (wait = 3, turn = 6)
// avg wait = 4 / 3 = 1
// avg turn = 10 / 3 = 3

CTEST_DATA(rr1) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(rr1) {
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    int quantum = 2;

    init(data->task, execution, data->size);
    round_robin(data->task, quantum, data->size);
}

CTEST2(rr1, test_process_id) {
    for (int i = 0; i < data->size; i++) {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}

CTEST2(rr1, test_exe_time)
{
  ASSERT_EQUAL(1, (int)data->task[0].execution_time);
  ASSERT_EQUAL(2, (int)data->task[1].execution_time);
  ASSERT_EQUAL(3, (int)data->task[2].execution_time);
}

CTEST2(rr1, test_wait_time)
{
  ASSERT_EQUAL(0, (int)data->task[0].waiting_time);
  ASSERT_EQUAL(1, (int)data->task[1].waiting_time);
  ASSERT_EQUAL(3, (int)data->task[2].waiting_time);
}

CTEST2(rr1, test_turn_time)
{
  ASSERT_EQUAL(1, (int)data->task[0].turnaround_time);
  ASSERT_EQUAL(3, (int)data->task[1].turnaround_time);
  ASSERT_EQUAL(6, (int)data->task[2].turnaround_time);
}

CTEST2(rr1, test_avg_wait_time)
{
  ASSERT_EQUAL(1, calculate_average_wait_time(data->task, data->size));
}

CTEST2(rr1, test_avg_turn_time)
{
  ASSERT_EQUAL(3, calculate_average_turn_around_time(data->task, data->size));
}

// rr2 {4, 10, 5}, quantum 3
// expected process_ids = {0, 1, 2}
// dec    [0] by 3 (left = 1)
// dec    [1] by 3 (left = 7)
// dec    [2] by 3 (left = 2)
// finish [0] in 1 (wait = 6, turn = 10)
// dec    [1] by 3 (left = 4)
// finish [2] in 2 (wait = 10, turn = 15)
// dec    [1] by 3 (left = 1)
// finish [1] in 1 (wait = 9, turn = 19)
// avg wait = 25 / 3 = 8
// avg turn = 44 / 3 = 14

CTEST_DATA(rr2) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(rr2) {
    int execution[] = {4, 10, 5};
    data->size = sizeof(execution) / sizeof(execution[0]);
    int quantum = 3;

    init(data->task, execution, data->size);
    round_robin(data->task, quantum, data->size);
}

CTEST2(rr2, test_process_id) {
    for (int i = 0; i < data->size; i++) {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}

CTEST2(rr2, test_exe_time)
{
  ASSERT_EQUAL(4, (int)data->task[0].execution_time);
  ASSERT_EQUAL(10, (int)data->task[1].execution_time);
  ASSERT_EQUAL(5, (int)data->task[2].execution_time);
}

CTEST2(rr2, test_wait_time)
{
  ASSERT_EQUAL(6, (int)data->task[0].waiting_time);
  ASSERT_EQUAL(9, (int)data->task[1].waiting_time);
  ASSERT_EQUAL(10, (int)data->task[2].waiting_time);
}

CTEST2(rr2, test_turn_time)
{
  ASSERT_EQUAL(10, (int)data->task[0].turnaround_time);
  ASSERT_EQUAL(19, (int)data->task[1].turnaround_time);
  ASSERT_EQUAL(15, (int)data->task[2].turnaround_time);
}

CTEST2(rr2, test_avg_wait_time)
{
  ASSERT_EQUAL(8, calculate_average_wait_time(data->task, data->size));
}

CTEST2(rr2, test_avg_turn_time)
{
  ASSERT_EQUAL(14, calculate_average_turn_around_time(data->task, data->size));
}
