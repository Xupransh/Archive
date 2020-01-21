/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
    if (a<b)
        return a;
    else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
    g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

    // YOUR CODE HERE
    std::vector<Edge> edges = g_.getEdges();
    for (auto &e : edges) {
        residual_.insertEdge(e.source, e.dest);
        residual_.insertEdge(e.dest, e.source);
        residual_.setEdgeWeight(e.dest, e.source, 0);
        residual_.setEdgeWeight(e.source, e.dest, e.getWeight());
        flow_.insertEdge(e.source, e.dest);
        flow_.setEdgeWeight(e.source, e.dest, 0);
    }
    maxFlow_ = 0;
}

/**
 * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
 *  This version is the helper function.
 *
 * @@params: source -- The starting (current) vertex
 * @@params: sink   -- The destination vertex
 * @@params: path   -- The vertices in the path
 * @@params: visited -- A set of vertices we have visited
 */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
                                     std::vector<Vertex> &path, std::set<Vertex> &visited) {

    if (visited.count(source) != 0)
        return false;
    visited.insert(source);

    if (source == sink) {
        return true;
    }

    vector<Vertex> adjs = residual_.getAdjacent(source);
    for(auto it = adjs.begin(); it != adjs.end(); it++) {
        if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
            path.push_back(*it);
            if (findAugmentingPath(*it,sink,path,visited))
                return true;
            else {
                path.pop_back();
            }
        }
    }

    return false;
}

/**
 * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
 *  This version is the main function.  It initializes a set to keep track of visited vertices.
 *
 * @@params: source -- The starting (current) vertex
 * @@params: sink   -- The destination vertex
 * @@params: path   -- The vertices in the path
 */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
    std::set<Vertex> visited;
    path.clear();
    path.push_back(source);
    return findAugmentingPath(source,sink,path,visited);
}

/**
 * pathCapacity - Determine the capacity of a path in the residual graph.
 *
 * @@params: path   -- The vertices in the path
 */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
    // YOUR CODE HERE
    int min_weight = INT_MAX;
    int temp;
    Vertex curr, next;
    for (size_t i = 0; i < path.size()-1; i++) {
        curr = path[i];
        next = path[i+1];
        temp =  residual_.getEdgeWeight(curr, next);
        if (min_weight > temp) {
            min_weight = temp;
        }
    }
    return min_weight;
}

/**
 * calculuateFlow - Determine the capacity of a path in the residual graph.
 * Sets the member function `maxFlow_` to be the flow, and updates the
 * residual graph and flow graph according to the algorithm.
 *
 * @@outputs: The network flow graph.
 */

const Graph & NetworkFlow::calculateFlow() {
    // YOUR CODE HERE
    std::vector <Vertex> paths;
    int capacity;
    int weight;
    Vertex curr, next;
    while (findAugmentingPath(source_, sink_, paths)) {
        capacity = pathCapacity(paths);
        maxFlow_ += capacity;
        for (size_t i = 0; i < paths.size()-1; i++) {
            curr = paths[i];
            next = paths[i+1];
            if (flow_.edgeExists(curr, next)) {
                flow_.setEdgeWeight(curr, next, flow_.getEdgeWeight(curr, next) + capacity);
            } else {
                flow_.setEdgeWeight(next, curr, flow_.getEdgeWeight(next, curr) - capacity);
            }
            residual_.setEdgeWeight(curr, next, residual_.getEdgeWeight(curr, next) - capacity);
            residual_.setEdgeWeight(next, curr, residual_.getEdgeWeight(next, curr) + capacity);
        }
    }
    return flow_;
}

int NetworkFlow::getMaxFlow() const {
    return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
    return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
    return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
    return residual_;
}

