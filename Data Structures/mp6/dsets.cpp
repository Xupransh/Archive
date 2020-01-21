/* Your code here! */
#include "dsets.h"
#include <stdlib.h>

void DisjointSets::addelements(int num)
{
    size_t size = disjoint_set.size();
    disjoint_set.resize(size + num);
    size = disjoint_set.size();
    for (size_t i = size - num; i < size; i++) {
        disjoint_set[i] = -1;
    }
}

int DisjointSets::find(int elem)
{
    if (disjoint_set[elem] < 0) {
        return elem;
    } else {
        disjoint_set[elem] = find(disjoint_set[elem]);
        return disjoint_set[elem];
    }
}

void DisjointSets::setunion(int a, int b)
{
    int root_a = find(a);
    int root_b = find(b);

    if (root_a == root_b) {
        return ;
    }

    int new_size = disjoint_set[root_a] + disjoint_set[root_b];

    if (disjoint_set[root_a] < disjoint_set[root_b]) {
        disjoint_set[root_b] = root_a;
        disjoint_set[root_a] = new_size;
    } else {
        disjoint_set[root_a] = root_b;
        disjoint_set[root_b] = new_size;
    }
}

int DisjointSets::size(int elem)
{
    return abs(disjoint_set[find(elem)]);
}

