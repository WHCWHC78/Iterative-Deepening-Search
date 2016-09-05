#include <stdlib.h>
#include <stdio.h>

#include "ids.h"
#include "hash.h"

int main(int argc, char **argv)
{
    uint8_t depth;
    struct problem problem;
    struct node node;
    struct solution *solution = NULL;
    enum STATUS status = FAILURE;

    init_problem(&problem);

    for (depth = 0; depth < 100 && (status != SUCCESS); ++depth) {
        /** printf("iteration: %u\n", depth + 1); */
        root_node(&problem, &node);
        insert_hash(hash(node.state));
        status = depth_limited_search(&node, &problem, &solution, depth);
        clear_hash();
    }

    printf("status: %u\n", status);
    /** stest = push_solution(NOACT, stest); */
    /** print_solution(stest, 1); */
    print_solution(solution, 1);

    return 0;
}
