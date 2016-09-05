#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "problem.h"

// state[tile] = position
// -------------
// | 0 | 1 | 2 |
// -------------
// | 3 | 4 | 5 |
// -------------
// | 6 | 7 | 8 |
// -------------
//
// -----------------------
// | Actions  | Position |
// -----------------------
// |  LEFT    |    -1    |
// |  UP      |    -3    |
// |  RIGHT   |    +1    |
// |  DOWN    |    +3    |
// -----------------------

// param[out]   initial_state: the initial state of the problem
// return void
static void random_initial_state(uint8_t *initial_state)
{
    // random position
    /** uint8_t pos_space[] = {0, 1, 2, 3, 4, 5, 6, 7, 8}; */
    /** uint8_t count, r; */

    /** for (count = 9; count; --count) { */
    /**     do { */
    /**         r = rand() % 9; */
    /**         [> printf("random number: %u\n", r); <] */
    /**     } */
    /**     while (pos_space[r] == 9); */

    /**     printf("tile: %u -> %u\n", count - 1, r); */
    /**     initial_state[count - 1] = pos_space[r]; */
    /**     pos_space[r] = 9; */
    /** } */

    // from the book
    initial_state[0] = 4;
    initial_state[1] = 8;
    initial_state[2] = 1;
    initial_state[3] = 7;
    initial_state[4] = 2;
    initial_state[5] = 3;
    initial_state[6] = 5;
    initial_state[7] = 0;
    initial_state[8] = 6;

    // from http://w01fe.com/blog/2009/01/the-hardest-eight-puzzle-instances-take-31-moves-to-solve/
    // the first hardest 8-puzzle instance
    /** initial_state[0] = 7; */
    /** initial_state[1] = 8; */
    /** initial_state[2] = 3; */
    /** initial_state[3] = 6; */
    /** initial_state[4] = 5; */
    /** initial_state[5] = 4; */
    /** initial_state[6] = 1; */
    /** initial_state[7] = 2; */
    /** initial_state[8] = 0; */

    // the second hardest 8-puzzle instance
    /** initial_state[0] = 5; */
    /** initial_state[1] = 8; */
    /** initial_state[2] = 7; */
    /** initial_state[3] = 6; */
    /** initial_state[4] = 1; */
    /** initial_state[5] = 4; */
    /** initial_state[6] = 0; */
    /** initial_state[7] = 2; */
    /** initial_state[8] = 3; */

    // from https://www.cs.utexas.edu/users/novak/asg-8p.html
    // the hard 8-puzzle instance
    /** initial_state[0] = 6; */
    /** initial_state[1] = 2; */
    /** initial_state[2] = 0; */
    /** initial_state[3] = 5; */
    /** initial_state[4] = 3; */
    /** initial_state[5] = 8; */
    /** initial_state[6] = 4; */
    /** initial_state[7] = 7; */
    /** initial_state[8] = 1; */

    // the worst 8-puzzle instance
    /** initial_state[0] = 4; */
    /** initial_state[1] = 8; */
    /** initial_state[2] = 7; */
    /** initial_state[3] = 6; */
    /** initial_state[4] = 3; */
    /** initial_state[5] = 0; */
    /** initial_state[6] = 1; */
    /** initial_state[7] = 2; */
    /** initial_state[8] = 5; */
}

// param[in]    state: current state
// return possible actions
static uint8_t actions(uint8_t blank_pos)
{
    uint8_t acts = 0;

    switch (blank_pos) {
        case 0:
            acts = RIGHT | DOWN;
            break;
        case 1:
            acts = LEFT | RIGHT | DOWN;
            break;
        case 2:
            acts = LEFT | DOWN;
            break;
        case 3:
            acts = UP | RIGHT | DOWN;
            break;
        case 4:
            acts = LEFT | UP | RIGHT | DOWN;
            break;
        case 5:
            acts = LEFT | UP | DOWN;
            break;
        case 6:
            acts = UP | RIGHT;
            break;
        case 7:
            acts = LEFT | UP | RIGHT;
            break;
        case 8:
            acts = LEFT | UP;
            break;
        default:
            break;
    }

    return acts;
}

// param[in]    state: current state
// param[in]    pos: desirable position
// return the tile at the desirable position
static uint8_t search_tile(uint8_t *state, uint8_t pos)
{
    uint8_t count;
    uint8_t tile = 9; // invalid case (no tile number nine)

    for (count = 9; count; --count) {
        if (state[count - 1] == pos) {
            tile = count - 1;
            break;
        }
    }

    return tile;
}

// param[in-n-out]  state: current state
// param[in]        action: performing action
// return next state
static uint8_t *result(uint8_t *state, uint8_t action)
{
    uint8_t tile;
    uint8_t *new_state = (uint8_t *)malloc(sizeof(uint8_t) * 9);

    memcpy(new_state, state, 9);

    switch (action) {
        case LEFT:
            tile = search_tile(new_state, new_state[0] - 1);
            new_state[0] -= 1;
            new_state[tile] += 1;
            break;
        case UP:
            tile = search_tile(new_state, new_state[0] - 3);
            new_state[0] -= 3;
            new_state[tile] += 3;
            break;
        case RIGHT:
            tile = search_tile(new_state, new_state[0] + 1);
            new_state[0] += 1;
            new_state[tile] -= 1;
            break;
        case DOWN:
            tile = search_tile(new_state, new_state[0] + 3);
            new_state[0] += 3;
            new_state[tile] -= 3;
            break;
        default:
            break; // do nothing
    }

    return new_state;
}

// param[in]    state: current state
// return true if the current state is a goal
static uint8_t goal_test(uint8_t *state)
{
    uint8_t count;

    // from the book
    /** for (count = 9; count; --count) { */
    /**     if (state[count - 1] != (count - 1)) */
    /**         break; */
    /** } */

    // traditional one
    for (count = 8; count; --count) {
        if (state[count] != (count - 1))
            break;
    }

    if (state[0] != 8)
        ++count;

    /** printf("goal test done\n"); */

    return (count ? 0 : 1);
}

// param[in]    problem: our problem (8-puzzle)
// return void
void init_problem(struct problem *problem)
{
    srand(time(NULL));

    random_initial_state(problem->initial_state);
    problem->actions = actions;
    problem->result = result;
    problem->goal_test = goal_test;
}
