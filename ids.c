#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "ids.h"

enum STATUS depth_limited_search(struct node *node, 
        struct problem *problem, 
        struct solution **solution, 
        uint8_t limit)
{
    /** printf("limit: %u\n", limit); */
    /** printf("pos: %u\n", node->state[0]); */
    /** usleep(1000 * 1000); */
    enum STATUS status = FAILURE;

    if (problem->goal_test(node->state)) {
        (*solution) = push_solution(node->action, NULL);
        status = SUCCESS;
    }
    else if (limit == 0)
        status = CUTOFF;
    else {
        uint8_t count;

        for (count = 4; (status != SUCCESS) && count; --count) {
            if (((problem->actions(node->state[0], node->action)) >> 
                        (count - 1)) & 1) {
                struct node *child = 
                    child_node(problem, node, 1 << (count - 1));
                status = 
                    depth_limited_search(child, problem, solution, limit - 1);
            }
        }

        if (status == SUCCESS) {
            (*solution) = push_solution(node->action, *solution);
            status = SUCCESS;

        }
        else
            status = CUTOFF;
    }

    free(node->state);

    if (node->parent != NULL)
        free(node);

    return status;
}

