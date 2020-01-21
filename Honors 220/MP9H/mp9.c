#include <stdint.h>
#include <stdio.h>

#include "mp5.h"
#include "mp9.h"

#define MY_INFINITY   1000000000

/*
MP9.c implements the following functtions -
find_nodes - Finds all the vertices in the given locale using a pyramid tree
and stores them in a vertex set
trim_nodes - Removes all the vertices not in a given locale from a vertex set
dijkstra - Finds the shortest path between a set of source vertices and destination
Uses a min heap that is in order wrt the source destination of each vertex.
vertices. Stores the result in an array.
Heap functions -
Swap - Swaps elements of child and parent indices in a heap.
heapify - heapifies a heap from a given index onward
add to heap - adds element to the heap
pop from heap - pops the minimum element from the heap
decrease key - decreases key for an existing element in the heap
*/


/*
Swaps elements of child and parent indices in a heap. Input parameters are the addresses of
the indices to be swapped, and pointers to the graph and heap. Also changes the child_index
to the parent index. (doesn't swap the indices completely)
*/
void
swap(graph_t *g, heap_t *h, int32_t *child_index, int32_t *parent_index)
{
    //store element at child index in a temp variable
    int32_t temp = h->elt[*child_index];
    //swap elements
    h->elt[*child_index] = h->elt[*parent_index];
    h->elt[*parent_index] = temp;
    //change the heap ids accordingly
    g->vertex[h->elt[*child_index]].heap_id = *parent_index;
    g->vertex[h->elt[*parent_index]].heap_id = *child_index;
    //make the child index the parent index
    *child_index = *parent_index;
}

/*
Takes in a heap that follows the heap order up to the heap_index and heapifies it completely
Takes in graph and heap pointers, and the heap index that is out of order
*/
void
heapify(graph_t *g, heap_t *h, int32_t heap_index)
{
    int32_t parent_index, parent_vertex_dist, dist = g->vertex[h->elt[heap_index]].from_src;

    while (heap_index >= 0)
    {
        //already min element
        if(heap_index == 0)
            break;

        //bubble vertex up the heap, first find the parent
        parent_index = (heap_index%2==0)?((heap_index-2)/2):((heap_index-1)/2);

        //if valid index, set the parent vertex distance from source
        if(parent_index >= 0)
            parent_vertex_dist = g->vertex[h->elt[parent_index]].from_src;
        else
            break;

        //if child distance is greater, swap, else, heap order is maintained
        if(parent_vertex_dist > dist)
            swap(g, h, &heap_index, &parent_index);
        else
            break;
    }
}

/*
Adds an element to the end of the heap, gives the vertex the distance
from the source and the previous vertex then calls heapify to maintain heap order.
*/
void
addToHeap(graph_t *g, heap_t *h, int32_t vertex_index, int32_t dist, int32_t predecessor_id)
{
    //heap has space for all n_vertices, (from main)
    //add vertex to heap, give it the pred, dist, etc.
    h->elt[h->n_elts++] = vertex_index;
    g->vertex[vertex_index].from_src = dist;
    g->vertex[vertex_index].pred = predecessor_id;
    //call heapify to maintain heap order
    heapify(g,h,((h->n_elts)-1));
}

/*
Changes the vertex the distance from the source and the previous
vertex then calls heapify to maintain heap order.
*/
void
decreaseKey(graph_t *g, heap_t *h, int32_t vertex_index, int32_t dist, int32_t predecessor_id)
{
    //set new values for vertex
    g->vertex[vertex_index].from_src = dist;
    g->vertex[vertex_index].pred = predecessor_id;
    int32_t heap_index = g->vertex[vertex_index].heap_id;
    //call heapify to maintain heap order
    heapify(g,h,heap_index);
}

/*
swap last element of array with 0, decrease the size by one (delete last element)
bubble it down, chose min(h[child],h[child+1]) to replace as parent
*/
void
popFromHeap(graph_t *g ,heap_t *h)
{
    int32_t parent_index = 0, child_index, next_min_index;

    //if empty heap, return
    if(h->n_elts == 0)
      return;

    //set last element as first element, decrease heap size
    h->elt[parent_index] = h->elt[--h->n_elts];

    //while the parent index is valid
    while(parent_index < h->n_elts)
    {
        //the children are at child_index and child_index+1
        child_index = 2*parent_index+1;

        //depending on the number of children, set min element
        if(child_index >= h->n_elts)
            break;
        else if(child_index+1 >= h->n_elts)
            next_min_index = child_index;
        else
            next_min_index = (g->vertex[h->elt[child_index]].from_src > g->vertex[h->elt[child_index+1]].from_src) ?
            (child_index+1) : (child_index);

        //if the parent distance is larger, swap
        if(g->vertex[h->elt[parent_index]].from_src > g->vertex[h->elt[next_min_index]].from_src)
        {
            //we need the parent_index to become the child_index, so swap with the arguments reversed
            swap(g,h,&parent_index,&next_min_index);
        }
        else
            break;
    }
}

/*
Function that stores the path information in path. First counts the
number of elements, then if no. of vertices is less than a given number,
fills the path array in reverse. Else returns -1.
*/
int32_t
storePathInfo(graph_t *g, heap_t *h, path_t *path, int32_t dest_index)
{
    int32_t curr_vertex_index = dest_index, n_vertices = 0, tot_dist = g->vertex[dest_index].from_src;

    //count the number of vertices till you reach the source (pred of source is -1)
    do
    {
        n_vertices++;
        curr_vertex_index = g->vertex[curr_vertex_index].pred;
    }
    while(curr_vertex_index != -1);

    curr_vertex_index = dest_index;

    //return 0 if path is bigger than MAX_PATH_LENGTH
    if(n_vertices >= MAX_PATH_LENGTH)
        return 0;

    //else set the properties and fill in the array in reverse
    path->n_vertices = n_vertices;
    path->tot_dist = tot_dist;

    //fill in the array in reverse
    while(n_vertices >= 0 && curr_vertex_index > 0)
    {
        path->id[--n_vertices] = curr_vertex_index;
        curr_vertex_index = g->vertex[curr_vertex_index].pred;
    }

    //return 1 if path was filled
    return 1;
}

/*
initialize all the vertices with the correct properties, initally set all distances to infinite,
predecessor to -1 (sources always have pred = -1), and heap_id to -1 (which would also indicated)
that the vertex is unvisited
*/
void
initializeVertices(graph_t *g)
{
      int32_t index;
      //go through all vertices and set properties
      for(index = 0; index < g->n_vertices; index++)
      {
          g->vertex[index].from_src = MY_INFINITY;
          g->vertex[index].pred = -1;
          g->vertex[index].heap_id = -1;
      }
}

/*
Add all of the source vertices to the heap
*/
void
heapSrc(graph_t *g, heap_t *h, vertex_set_t* src)
{
    int32_t count = 0, curr_src = 0;
    //start from 0 elements in the heap
    h->n_elts = 0;
    //for all elements in the source vertex set
    while(count < src->count)
    {
        //add it to the heap
        curr_src = src->id[count++];
        h->elt[h->n_elts++] = curr_src;
        //and set the vertex properties
        (g->vertex[curr_src]).from_src = 0;
        (g->vertex[curr_src]).heap_id = h->n_elts-1;
    }
}

/*
Returns 1 if a given vertex is in the destination vertex set
takes in vertex id of the current index
*/
int32_t
foundADest(graph_t *g, int32_t index_curr, vertex_set_t *dest)
{
    int32_t i, destX, destY;
    //for each vertex in the destintion vertex set
    for(i = 0; i < dest->count; i++)
    {
        destX = g->vertex[dest->id[i]].x;
        destY = g->vertex[dest->id[i]].y;
        //if this is a target destination, return 1;
        if((g->vertex[index_curr].x == destX) && (g->vertex[index_curr].y == destY))
            return 1;
    }
    return 0;
}

/*
Adds leaf node to the vertex set if it is in range of a given locale
*/
void
isLeafInRange(locale_t *loc, pyr_tree_t *p, vertex_set_t *vs, int32_t nnum)
{
    //check if it's in range, if it is, add it to the vertex set.
    if(in_range(loc, (p->node[nnum]).x, (p->node[nnum]).y_left))
    {
        vs->id[vs->count] = p->node[nnum].id;
        vs->count += 1;
    }
}

/*
Finds all the given locale based on a given pyramid tree
*/
void
find_nodes (locale_t* loc, vertex_set_t* vs, pyr_tree_t* p, int32_t nnum)
{
    // Do not modify the following line nor add anything above in the function.
    record_fn_call ();

    //index out of range, return
    if(nnum >= p->n_nodes || vs->count >= MAX_IN_VERTEX_SET)
      return;

    //if part of loc lies in the 1st and 3rd quadrant
    if(loc->x - loc->range <= p->node[nnum].x)
    {
        //if part of loc lies above y_left, explore 3rd quadrant of the pyramid
        if(loc->y + loc->range >= p->node[nnum].y_left)
        {
            //but if it's a leaf node, avoid calling find_nodes entirely
            if(4*nnum+3 >= p->n_nodes)
                isLeafInRange(loc, p, vs, nnum);
            else
                find_nodes(loc, vs, p, 4*nnum+3);
        }

        //if part of loc lies below y_left, explore 1st quadrant of the pyramid
        if(loc->y - loc->range <= p->node[nnum].y_left)
        {
            if(4*nnum+1 >= p->n_nodes)
                isLeafInRange(loc, p, vs, nnum);
            else
                find_nodes(loc, vs, p, 4*nnum+1);
        }
    }
    //if part of loc lies in the 2nd and 4th quadrant
    if(loc->x + loc->range >= p->node[nnum].x)
    {
        //if part of loc lies above y_right, explore 4th quadrant of the pyramid
        if(loc->y + loc->range  >= p->node[nnum].y_right)
        {
            if(4*nnum+4 >= p->n_nodes)
                isLeafInRange(loc, p, vs, nnum);
            else
                find_nodes(loc, vs, p, 4*nnum+4);
        }

        //if part of loc lies below y_right, explore 2nd quadrant of the pyramid
        if(loc->y - loc->range <= p->node[nnum].y_right)
        {
            if(4*nnum+2 >= p->n_nodes)
                isLeafInRange(loc, p, vs, nnum);
            else
                find_nodes(loc, vs, p, 4*nnum+2);
        }
    }

}

/*
Trims nodes that are not in a given locale
*/
void
trim_nodes (graph_t* g, vertex_set_t* vs, locale_t* loc)
{
    int32_t count = 0, index = 0;
    while(count < vs->count && vs->count > 0)
    {
        if(!in_range(loc, (g->vertex[vs->id[count]]).x, (g->vertex[vs->id[count]]).y))
        {
            vs->count--;
            for(index = count; index < vs->count; index++)
                vs->id[index] = vs->id[index+1];
        }
        else
          count++;
    }
}

/*
Dijkstra's shortest path algorithm. Takes in a set of source vertices and destination vertices
and returns the shortest path (if possible) inside the path vaiable in order. Else returns 0.
*/
int32_t
dijkstra (graph_t* g, heap_t* h, vertex_set_t* src, vertex_set_t* dest,
          path_t* path)
{
    int32_t index = 0, index_curr = 0, neighbor_index, dist = 0;

    //initialize vertices with infinite distance, form heap out of source vertices
    initializeVertices(g);
    heapSrc(g,h,src);

    //while the heap isn't empty
    while(h->n_elts > 0)
    {
        //change curent index to min element of the heap
        index_curr = h->elt[0];

        //if this index is a destination, break.
        if(foundADest(g,index_curr,dest))
        {
          if(storePathInfo(g, h, path, index_curr))
              return 1;
          else
              break;
        }

        //for each neighbor node of given vertex
        for(index = 0; index < g->vertex[index_curr].n_neighbors; index++)
        {
            //if previously unseen, add element to the heap
            if(g->vertex[g->vertex[index_curr].neighbor[index]].heap_id == -1)
            {
                dist = g->vertex[index_curr].distance[index] + g->vertex[index_curr].from_src;
                neighbor_index = (g->vertex[index_curr].neighbor[index]);
                addToHeap(g, h, neighbor_index, dist, index_curr);
            }

            //else if in heap, but with a higher distance, decrease it's distance
            else if(g->vertex[g->vertex[index_curr].neighbor[index]].from_src
              > g->vertex[index_curr].distance[index] + g->vertex[index_curr].from_src)
            {
                dist = g->vertex[index_curr].distance[index] + g->vertex[index_curr].from_src;
                neighbor_index = g->vertex[index_curr].neighbor[index];
                decreaseKey(g, h, neighbor_index, dist, index_curr);
            }
        }

        //pop top element from heap
        popFromHeap(g,h);
    }

    return 0;
}
