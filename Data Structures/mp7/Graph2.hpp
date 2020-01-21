#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {

    std::list <std::string> path;
    std::queue <std::string> q;

    // maintains the predecessors 
    std::unordered_map <std::string, std::string> pred;

    // visited maintains 2 things, if the vertex has been added to the queue
    // and if it has been visited. If it's false, then it's added.
    std::unordered_map <std::string, bool> visited;
    std::string curr;

    // initialize queue to start vertex
    q.push(start);

    while (!q.empty()) {

        // look at current vertex
        curr = q.front();
        q.pop();

        // if this is the end vertex, we're done
      	if (curr == end) {
          	break;
        }

        // find out if the vertex has been visited
        auto visitIt = visited.find(curr);
        if (visitIt != visited.end() && visitIt->second) {
            continue;
        }

        // mark vertex as visited
        visited[curr] = true;

        // gather all incident edges
        auto edges = incidentEdges(curr);

        // iterating through edges
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            // getting source and destination
          	auto dest = it->get().dest().key();
            auto source = it->get().source().key();

          	// add the end of the edge which is not the source, but only
          	// if it hasn't been added already
            if (dest != curr && visited.find(dest) == visited.end()) {
                q.push(dest);
                pred[dest] = curr;
                visited[dest] = false;
            } else if (source != curr && visited.find(source) == visited.end()) {
                q.push(source);
                pred[source] = curr;
                visited[dest] = false;
            }
        }
    }

  	// terminating if it is not the end
    if (curr != end) {
        return path;
    }

  	// iterating throught the shortest path and adding it to the path variable
    do {
        path.push_front(curr);
        curr = pred[curr];
    } while (curr != start);

    path.push_front(start);

    return path;
}

