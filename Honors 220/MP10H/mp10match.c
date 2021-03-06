#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mp5.h"
#include "mp10.h"


//
// These variables hold the heads of two singly-linked lists of
// requests.
//
// The avaialble list consists of unpaired requests: partner
// should be NULL, and next is used to form the list.
//
// The shared list consists of groups with non-empty start and end
// vertex intersections.  Only one of the requests in the group is in
// the list.  The others are linked through the first's partner field
// and then through the next field of the others in the group.  The
// next field of the first request in a group is used to form the
// shared list.
//
// Note: for MP2, you should only build groups of two in the shared
// list.
//

static request_t* available = NULL;
static request_t* shared = NULL;

//delete a request from the available list given the previous node and the current node
void deleteAvailableRequest(request_t *curr, request_t *prev)
{
    //if prev is not null
    if(prev)
    {
        //delete the node by removing it's reference from the prev node
        prev->next = curr->next;
        curr->next = NULL;
        return;
    }
    //if prev is null, it means that there's only one element
    available = NULL;
}

//free some of the resources used
void
free_resources(vertex_set_t *vs_src, vertex_set_t *vs_dest, path_t *p)
{
    //free the source and destination vertex and the path
    free_vertex_set(vs_src);
    free_vertex_set(vs_dest);
    free_path(p);
}

//free the intersection vertices
void freeVS(vertex_set_t *v_int_dst,  vertex_set_t *v_int_src)
{
    //free the intersection vertices
    free_vertex_set(v_int_src);
    free_vertex_set(v_int_dst);
}

int32_t
setPath(graph_t *g, heap_t *h, path_t *p, request_t *r, request_t *curr, vertex_set_t *v_int_src,  vertex_set_t *v_int_dst)
{
    //free the source and destination vertices, replace them with their respective intersection vertices
    if(r->src_vs && r->dst_vs)
        freeVS(r->src_vs,r->dst_vs);
    if(curr->src_vs && curr->dst_vs)
        freeVS(curr->src_vs,curr->dst_vs);
    //build the minimaps
    build_vertex_set_minimap(g,v_int_dst);
    build_vertex_set_minimap(g,v_int_src);

    r->src_vs = v_int_src;
    r->dst_vs = v_int_dst;

    curr->src_vs = v_int_src;
    curr->dst_vs = v_int_dst;

    //if dijkstra fails, free everything and return
    if(!dijkstra(g,h,r->src_vs,r->dst_vs,r->path))
    {
        freeVS(v_int_dst,v_int_src);
        return 0;
    }
    //otherwise, build the path minimap
    build_path_minimap(g,r->path);
    return 1;
}

//the main function that handles a single request using linked lists
int32_t
handle_request (graph_t* g, pyr_tree_t* pyr, heap_t* h, request_t* r)
{
    //create the required resources
    vertex_set_t *src_vs = new_vertex_set();
    vertex_set_t *dst_vs = new_vertex_set();
    path_t *p = new_path();

    //if any one of them fails, free everything and return 0
    if((src_vs == NULL) || (dst_vs == NULL) || (p == NULL))
    {
        free_resources(src_vs, dst_vs, p);
        return 0;
    }

    //build source vertex set
  	find_nodes(&(r->from), src_vs, pyr, 0);
  	find_nodes(&(r->to), dst_vs, pyr, 0);

    //if the vertex sets are null, free everything and return
	  if(dst_vs->count == 0 || src_vs->count == 0)
	  {
        free_resources(src_vs, dst_vs, p);
        return 0;
    }

    //build the vertex set minimaps (is this needed?)
    build_vertex_set_minimap(g,src_vs);
    build_vertex_set_minimap(g,dst_vs);

    //set the attributes for the request
    r->src_vs = src_vs;
    r->dst_vs = dst_vs;
    r->path = p;

    //if available is null, make the next element the request
    if(!available)
    {
        available = r;
        r->next = NULL;
        r->partner = NULL;
        return 1;
    }

    //else, use a place holder and go through the list trying to match
    request_t *curr = available;
    request_t *prev = NULL;
    int32_t max_src = 0, max_dst = 0;
    while(curr)
    {
        max_src = (r->src_vs->count > curr->src_vs->count)? (r->src_vs->count) : (curr->src_vs->count);
        max_dst = (r->dst_vs->count > curr->dst_vs->count)? (r->dst_vs->count) : (curr->dst_vs->count);
        //create the intersection vertex sets
        vertex_set_t *v_int_src = malloc(sizeof(*v_int_src));
        vertex_set_t *v_int_dst = malloc(sizeof(*v_int_dst));

        //if the allocation fails, free everything
        if(!(v_int_src) || !(v_int_dst))
        {
            free_resources(src_vs, dst_vs, p);
            freeVS(v_int_dst, v_int_src);
            return 0;
        }

        v_int_src->id = calloc(max_src, sizeof(*v_int_src));
        v_int_dst->id = calloc(max_dst, sizeof(*v_int_dst));

        //if the allocation fails, free everything
        if(!(v_int_src->id) || !(v_int_dst->id))
        {
            free_resources(src_vs, dst_vs, p);
            freeVS(v_int_dst, v_int_src);
            return 0;
        }

        v_int_dst->id_array_size = max_dst;
        v_int_src->id_array_size = max_src;

        //if the intersection is null, free the intersection vertex sets and try the next request in the list
        if(!merge_vertex_sets(r->src_vs, curr->src_vs, v_int_src)|| (!merge_vertex_sets(r->dst_vs, curr->dst_vs, v_int_dst)))
        {
              freeVS(v_int_dst, v_int_src);
              prev = curr;
              curr = curr->next;
              continue;
        }


        //if the path setting fails, free everything and return 0
        if(!setPath(g,h,p,r,curr,v_int_src,v_int_dst))
        {
            free_resources(src_vs, dst_vs, p);
            freeVS(v_int_dst,v_int_src);
            return 0;
        }
        else
        {
            r->partner = curr;
            r->next = NULL;
            //if shared is not null, add the request to the list
            if(shared)
            {
                //add the 2 requests to the shared list
                r->next = shared;
                shared = r;
            }
            else
            {
                shared = r;
            }

            //delete the request from the available list, free vints, and return 1
            deleteAvailableRequest(curr,prev);
            return 1;
        }
        freeVS(v_int_dst,v_int_src);
    }
    r->next = available;
    available = r;
    r->partner = NULL;
    return 1;

}


void
print_results ()
{
    request_t* r;
    request_t* prt;

    printf ("Matched requests:\n");
    for (r = shared; NULL != r; r = r->next) {
        printf ("%5d", r->uid);
	for (prt = r->partner; NULL != prt; prt = prt->next) {
	    printf (" %5d", prt->uid);
	}
	printf (" src=%016lX dst=%016lX path=%016lX\n", r->src_vs->minimap,
		r->dst_vs->minimap, r->path->minimap);
    }

    printf ("\nUnmatched requests:\n");
    for (r = available; NULL != r; r = r->next) {
        printf ("%5d src=%016lX dst=%016lX\n", r->uid, r->src_vs->minimap,
		r->dst_vs->minimap);
    }
}


int32_t
show_results_for (graph_t* g, int32_t which)
{
    request_t* r;
    request_t* prt;

    // Can only illustrate one partner.
    for (r = shared; NULL != r; r = r->next) {
	if (which == r->uid) {
	    return show_find_results (g, r, r->partner);
	}
	for (prt = r->partner; NULL != prt; prt = prt->next) {
	    if (which == prt->uid) {
		return show_find_results (g, prt, r);
	    }
	}
    }

    for (r = available; NULL != r; r = r->next) {
        if (which == r->uid) {
	    return show_find_results (g, r, r);
	}
    }
    return 0;
}


static void
free_request (request_t* r)
{
    free_vertex_set (r->src_vs);
    free_vertex_set (r->dst_vs);
    if (NULL != r->path) {
	free_path (r->path);
    }
    free (r);
}

void
free_all_data ()
{
    request_t* r;
    request_t* prt;
    request_t* next;

    // All requests in a group share source and destination vertex sets
    // as well as a path, so we need free those elements only once.
    for (r = shared; NULL != r; r = next) {
	for (prt = r->partner; NULL != prt; prt = next) {
	    next = prt->next;
	    free (prt);
	}
	next = r->next;
	free_request (r);
    }

    for (r = available; NULL != r; r = next) {
	next = r->next;
	free_request (r);
    }
}
