#include <stdint.h>
#include <stdio.h>

#include "mp10.h"

//mark with graph index if #of vertices < 64
void
markWithIndex(graph_t *g)
{
    //for each vertex, set mm_bit to vertex index
    int32_t i;
    for(i = 0; i < g->n_vertices; i++)
      g->vertex[i].mm_bit = i;
}

//recursive method to find pyramid tree ancestors.
int32_t
findPyramidAncestor(vertex_t vs, pyr_tree_t *p, int32_t count, int32_t p_index)
{
    //count keeps track of pyramid level
    if(count == 4)
        return p_index;

    //if the vertex is in the 2nd or 3rd quadrant
    if(vs.x < p->node[p_index].x)
    {
        //if the vertex is in the 2nd quadrant
        if(vs.y < p->node[p_index].y_left)
            return findPyramidAncestor(vs,p,++count,4*p_index+1);
        else
            return findPyramidAncestor(vs,p,++count,4*p_index+3);
    }
    else
    {
        //if the vertex is in the 1st quadrant
        if(vs.y < p->node[p_index].y_right)
            return findPyramidAncestor(vs,p,++count,4*p_index+2);
        else
            return findPyramidAncestor(vs,p,++count,4*p_index+4);
    }
}

//mark vertex minimap bit
int32_t
mark_vertex_minimap (graph_t* g, pyr_tree_t* p)
{
    //if less than 64 vertices,
    if(g->n_vertices <= 64)
        markWithIndex(g);

    //count the level, index into the vertex array
    int32_t count, v_index = 0, p_index = 0;

    //for all vertices
    while(v_index < g->n_vertices)
    {
        //find ancestor, set mm_bit to ancestor index - 21
        count = 1;
        g->vertex[v_index].mm_bit = findPyramidAncestor(g->vertex[v_index], p, count, p_index) - 21;
        v_index++;
        p_index = 0;
    }
    return 1;
}


//use mmbits of each vertex to assign the minimap of the vertex set
void
build_vertex_set_minimap (graph_t* g, vertex_set_t* vs)
{
    //for each vertex in the vertex set
    int32_t i;
    uint64_t minimap = 0;
    uint64_t x = 1;
    //shift 1 by mm_bit and or it into a variable
    for(i = 0; i < vs->count; i++)
        minimap |= ((x)<<(g->vertex[vs->id[i]].mm_bit));

    //set the minimap variable for the vertex set
    vs->minimap = (unsigned long long)minimap;
}

//use mmbit of path vertices to form the minimap of the path
void
build_path_minimap (graph_t* g, path_t* p)
{
    //this functions is identical to the one above
    int32_t i;
    uint64_t minimap = 0;
    uint64_t x = 1;
    for(i = 0; i < p->n_vertices; i++)
        minimap |= ((x)<<(g->vertex[p->id[i]].mm_bit));

    p->minimap = (unsigned long long)minimap;
}

//form the intersection of two given vertex sets, size of vint is given by handle_request
int32_t
merge_vertex_sets (const vertex_set_t* v1, const vertex_set_t* v2,
		   vertex_set_t* vint)
{
    //if a vertex belongs to both sets, add it to the vint vertex set
    int32_t i = 0;
    int32_t j = 0;
    vint->count = 0;
    do
    {
        //if the vertices are equal
        if(v1->id[i] == v2->id[j])
        {
            //add it to the vint
            if(vint->count < vint->id_array_size)
                vint->id[vint->count++] = v1->id[i++];
        }
        //since the vertex sets are sorted, stop if the vertex id is more that the given id
        else if(v1->id[i] < v2->id[j])
        {
            i++;
            j=0;
        }
        else
            j++;
        //if we're out of vertices to check against, move to the next vertex
        if(j>=v2->count)
        {
           i++;
           j = 0;
        }
    }
    while(i<v1->count);

    //return true if the intersection is not null
    return (vint->count > 0);
}
