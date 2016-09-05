#ifndef _PROBLEM_H
#define _PROBLEM_H 

#include <stdint.h>

#define NOACT   0b0000
#define LEFT    0b0001
#define UP      0b0010
#define RIGHT   0b0100
#define DOWN    0b1000

struct problem {
    uint8_t initial_state[9];
    uint8_t (*actions)(uint8_t blank_pos, uint8_t last_act); 
    uint8_t *(*result)(uint8_t *state, uint8_t action);
    uint8_t (*goal_test)(uint8_t *state);
};

void init_problem(struct problem *problem);

#endif /* ifndef _PROBLEM_H */
