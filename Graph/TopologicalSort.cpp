vector<string> topologicalSort(const unordered_map<string, vector<string>>& digraph)
{

    // construct an unordered map mapping nodes to their indegrees
    unordered_map<string, int> indegrees;
    for (auto node : digraph) {
        indegrees[node.first] = 0;
    }
    for (auto node : digraph) {
        for (auto neighbor : node.second) {
            indegrees[neighbor] += 1;
        }
    }

    // track nodes with no incoming edges
    vector<string> nodesWithNoIncomingEdges;
    for (auto node : digraph) {
        if (indegrees[node.first] == 0) {
            nodesWithNoIncomingEdges.push_back(node.first);
        }
    }

    // initially, no nodes in our ordering
    vector<string> topologicalOrdering;
                
    // as long as there are nodes with no incoming edges
    // that can be added to the ordering 
    while (nodesWithNoIncomingEdges.size() > 0) {

        // add one of those nodes to the ordering
        string node = nodesWithNoIncomingEdges.back();
        nodesWithNoIncomingEdges.pop_back();
        topologicalOrdering.push_back(node);
    
        // decrement the indegree of that node's neighbors
        for (auto neighbor : digraph.at(node)) {
            indegrees[neighbor] -= 1;
            if (indegrees[neighbor] == 0) {
                nodesWithNoIncomingEdges.push_back(neighbor);
            }
        }
    }

    // we've run out of nodes with no incoming edges
    // did we add all the nodes or find a cycle?
    if (topologicalOrdering.size() != digraph.size())
    {
        throw invalid_argument("Graph has a cycle! No topological ordering exists.");
    }

    return topologicalOrdering;  // got them all
}
