#ifndef _IDS_H
#define _IDS_H

#include "problem.h"
#include "node.h"

enum STATUS { 
    SUCCESS = 0,
    FAILURE,
    CUTOFF
};

enum STATUS depth_limited_search(struct node *node, 
        struct problem *problem, 
        struct solution **solution, 
        uint8_t limit);

#endif /* ifndef _IDS_H */
