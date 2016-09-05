#ifndef _NODE_H
#define _NODE_H

#include <stdint.h>

#include "problem.h"

struct node {
    uint8_t *state;
    struct node *parent;
    uint8_t action;
};

struct solution {
    uint8_t action;
    struct solution *next;
    struct solution *prev;
};

struct node *child_node(struct problem *problem, 
        struct node *parent, 
        uint8_t action);
void root_node(struct problem *problem, struct node *node);
struct solution *push_solution(uint8_t action, struct solution *solution);
void print_solution(struct solution *solution, uint8_t count);

#endif /* ifndef _NODE_H */
