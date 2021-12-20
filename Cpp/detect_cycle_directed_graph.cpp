// A C++ Program to detect cycle in a graph  
#include <iostream>
#include <vector>
  
// A directed graph G is acyclic if and only if 
// a depth first search of G yields no back edges
class Graph
{
    using graph = std::vector<std::vector<int>>;
    int V;    // No. of vertices
    graph g; // two dimensional vector to represent the graph
    bool isCyclicUtil(int v, std::vector<bool>& visited, std::vector<bool>& rs);  // used by isCyclic()
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    bool isCyclic();    // returns true if there is a cycle in this graph
};
  
Graph::Graph(int V)
{
    this->V = V;
    g = std::move(graph(V,std::vector<int>()));
}
   
void Graph::addEdge(int v, int w)
{
    g[v].push_back(w);  // add  v and w to graph
}
  
bool Graph::isCyclicUtil(int v, std::vector<bool>& visited, std::vector<bool>& recStack)
{
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;
        // Recur for all the vertices adjacent to this vertex
        for(auto s : g[v])
        {
            if(visited[v] == false)
            {
                if (!visited[s] && isCyclicUtil(s, visited, recStack) )
                    return true;
            }
            else if (recStack[s])
                return true;
            
        }
    recStack[v] = false;  // remove the vertex from recursion stack
    return false;
}
  
// Returns true if the graph contains a cycle, else false.
bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    std::vector<bool> visited(V,false);
    std::vector<bool> recStack(V,false);  
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;
  
    return false;
}
  
int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
  
    if(g.isCyclic())
        std::cout << "Graph contains cycle";
    else
        std::cout << "Graph doesn't contain cycle";
    return 0;
}