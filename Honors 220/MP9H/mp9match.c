#include <stdint.h>
#include <stdio.h>

#include "mp5.h"
#include "mp9.h"


/*
Driver code for MP9.c, the driver code for this is mp9main.c
Printf statements were used for checking values
*/
int32_t
match_requests (graph_t* g, pyr_tree_t* p, heap_t* h,
		request_t* r1, request_t* r2,
		vertex_set_t* src_vs, vertex_set_t* dst_vs, path_t* path)
{
		//set vertex set counts to 0, give locales easy names
		src_vs->count = 0;
		dst_vs->count = 0;
		locale_t *r1_from = &(r1->from);
		locale_t *r1_to = &(r1->to);
		locale_t *r2_from = &(r2->from);
		locale_t *r2_to = &(r2->to);

		//build source vertex set
		if(r1_from->range < r2_from ->range)
		{
				find_nodes(r1_from, src_vs, p, 0);
				trim_nodes(g,src_vs,r2_from);
		}
		else
		{
				find_nodes(r2_from, src_vs, p, 0);
				trim_nodes(g,src_vs,r1_from);
		}

		//printf("%d calls to find_nodes for the source vertex set\n", called);

		if(src_vs->count > 0)
		{
				//build dest vertex set
				if(r1_to->range < r2_to ->range)
				{
						find_nodes(r1_to, dst_vs, p, 0);
						if(dst_vs->count > MAX_IN_VERTEX_SET)
						{
								trim_nodes(g,dst_vs,r2_to);
						}

				}
				else
				{
						find_nodes(r2_to, dst_vs, p, 0);
						trim_nodes(g,dst_vs,r1_to);
				}
				//printf("%d source vertices found\n", src_vs->count);
				//printf("%d calls to find_nodes for the destination vertex set\n", called);
		}
		else
		{
				//printf("No Source nodes retained!!\n");
				return 0;
		}
		if(dst_vs->count == 0)
		{
				//printf("No Destination nodes retained!!\n");
				return 0;
		}
		//printf("%d destination vertices found\n", dst_vs->count);
		//call Dijkstra and return it's value
		return dijkstra(g,h,src_vs,dst_vs,path);

}
