#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>


/**
 * @return The number of vertices in the Graph
 */
template <class V, class E>
unsigned int Graph<V,E>::size() const
{
    // number of vertices = size of vertexMap
    return vertexMap.size();
}


/**
 * @return Returns the degree of a given vertex.
 * @param v Given vertex to return degree.
 */
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const
{

    // go through edgeList, add all incoming/outgoing edges
    auto key = v.key();
    unsigned int result = 0;
    for (auto & e : edgeList) {
        auto edge = e.get();
        if (edge.source().key() == key || edge.dest().key() == key) {
            result++;
        }
    }
    return result;
}


/**
 * Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
 * @param key The key of the Vertex to insert
 * @return The inserted Vertex
 */
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key)
{
    // create new vertex in heap
    V & v = *(new V(key));

    // clear vertex if exists, insert new vertex into map
    removeVertex(key);
    vertexMap.emplace(key, v);

    // create fresh edge list, insert key and edgelist into adjlist
    adjList.emplace(key, std::list<edgeListIter>());
    return v;
}


/**
 * Removes a given Vertex
 * @param v The Vertex to remove
 */
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key)
{
    // find the vertex, return iterator to it 
    auto v = vertexMap.find(key);

    // if it exists, clear memory
    if (v != vertexMap.end()) {
        // delete &(v->second);
        vertexMap.erase(v);

        // remove all edges where it's a dest
        for (auto it = edgeList.begin(); it != edgeList.end(); ++it) {
            auto edge = it->get();
            if (edge.dest().key() == key) {
                removeEdge(edge.source().key(), key);
            }
        }

        //remove all it's edges, and remove from adjlist
        auto vList = adjList.find(key);
        for (auto it = vList->second.begin() ; it != vList->second.end(); ++it) {
            // delete &((*i)->get());
            removeEdge(*it);
        }
        adjList.erase(vList);
    }
}


/**
 * Inserts an Edge into the adjacency list
 * @param v1 The source Vertex
 * @param v2 The destination Vertex
 * @return The inserted Edge
 */
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2)
{
    //create new edge, insert it into the list of edges.
    E & e = *(new E(v1, v2));

    edgeList.emplace_front(e);

    // so that you don't call it again and again
    std::string key1 = v1.key();
    std::string key2 = v2.key();

    // find the vertices, if they don't exist, make them
    auto v1Iter = adjList.find(key1);
    auto v2Iter = adjList.find(key2);

    if (v1Iter == adjList.end()) {
        insertVertex(key1);
        v1Iter = adjList.find(key1);
    } if (v2Iter == adjList.end()) {
        insertVertex(key2);
    }

    // find the vertices, insert the iterator to the new edge into the list
    v1Iter->second.push_front(edgeList.begin());
    return e;
}


/**
 * Removes an Edge from the Graph
 * @param key1 The key of the ource Vertex
 * @param key2 The key of the destination Vertex
 */
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2)
{
    // find the start vertex
    auto v1Iter = adjList.find(key1);
    auto v2Iter = adjList.find(key2);

    // remove all the edge iterators from the list of its edges
    // that have key2 as the destination
    for (auto it = v1Iter->second.begin(); it != v1Iter->second.end(); ++it) {
        if ((*it)->get().dest().key() == key2) {
            // delete &((*i)->get());
            auto eListIt = *it;
            it = v1Iter->second.erase(it);
            removeEdge(eListIt);
        }
    }

    // if it's undirected, check both ways.
    if (!edgeList.begin()->get().directed()) {
        for (auto it = v2Iter->second.begin(); it != v2Iter->second.end(); ++it) {
            if ((*it)->get().dest().key() == key1) {
                // delete &((*i)->get());
                auto eListIt = *it;
                it = v1Iter->second.erase(it);
                removeEdge(eListIt);
            }
        }
    }
}

/**
 * Removes an Edge from the adjacency list at the location of the given iterator
 * @param it An iterator at the location of the Edge that
 * you would like to remove
 */
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it)
{
    // delete edgeListIter from edgelist
    edgeList.erase(it);
}


/**
 * @param key The key of an arbitrary Vertex "v"
 * @return The list edges (by reference) that are adjacent to "v"
 */
template <class V, class E>  
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const
{
    //create list to be returned
    std::list<std::reference_wrapper<E>> edges;

    // insert all edges incident to found vertex into list, return the list
    for (auto it = edgeList.begin(); it != edgeList.end(); ++it) {
        auto edge = it->get();
        if (edge.dest().key() == key || edge.source().key() == key) {
            edges.emplace_front(*it);
        }
    }
    return edges;
}


/**
 * Return whether the two vertices are adjacent to one another
 * @param key1 The key of the source Vertex
 * @param key2 The key of the destination Vertex
 * @return True if v1 is adjacent to v2, False otherwise
 */
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const
{

    // find given vertices
    auto v1Iter = adjList.find(key1);
    auto v2Iter = adjList.find(key2);
    std::list< edgeListIter > maxList;
    std::string search_key;

    // select the larger edge list
    if (v1Iter->second.size() > v2Iter->second.size()) {
        maxList = v1Iter->second;
        search_key = key2;
    } else {
        maxList = v2Iter->second;
        search_key = key1;
    }

    // for each edge, see if the dest is key2 if directed, or simply the search_key
    // if undirected
    for (auto & e : maxList) {
        auto edge = e->get();
        if (edge.dest().key() == search_key || edge.source().key() == search_key) {
            if (edge.directed()) {
                return edge.dest().key() == key2;
            }
            return true;
        }
    }

    // return false if no edge between the 2 was found
    return false;
}
