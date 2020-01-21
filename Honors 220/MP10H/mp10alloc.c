#include <stdint.h>
#include <stdlib.h>

#include "mp10.h"


//Creates a new vertex set, complete with a id array initialized to a size of 100 (somewhat arbitrarily)
vertex_set_t*
new_vertex_set ()
{
    //initial size is 100
    int initial_id_size = 100;
    //create vs
    vertex_set_t *vs = malloc(sizeof(*vs));
    //if malloc fails, return null
    if(!vs)
    {
        free(vs);
        return NULL;
    }
    //create the id array, if anything goes wrong, return null
    int32_t *id_copy = calloc(initial_id_size,sizeof(*id_copy));
    if(!(id_copy))
    {
        free_vertex_set(vs);
        return NULL;
    }
    //give vs it's respective properties and return the pointer
    vs->id = id_copy;
    vs->id_array_size = initial_id_size;
    vs->count = 0;
    return vs;

}

//frees up a vertex set
void
free_vertex_set (vertex_set_t* vs)
{
    if(vs->id)
        free(vs->id);
    if(vs)
        free(vs);
}

//creates a new path and path array
path_t*
new_path ()
{
    path_t *path = malloc(sizeof(*path));
    if(!path)
    {
        free(path);
        return NULL;
    }
    path->n_vertices = 0;
    path->id = NULL;
    return path;
}

//free the path array and struct
void
free_path (path_t* path)
{
    if(path->id)
        free(path->id);
    if(path)
        free(path);
}
