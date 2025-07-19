#include <iostream> // For input/output operations (e.g., cout)
#include <vector>   // For using std::vector to represent the graph and visited array
#include <stack>    // For using std::stack to store the topological order

// Using the standard namespace to avoid prefixing std:: to every standard library element.
using namespace std;

// Function to perform Depth First Search (DFS) for topological sorting
// Parameters:
//   u: The current vertex being visited
//   adj: The adjacency list representation of the graph
//   visited: A boolean vector to keep track of visited vertices
//   resultStack: A stack to store the vertices in topological order
void dfs(int u, const vector<vector<int>> &adj, vector<bool> &visited, stack<int> &resultStack)
{
    // Mark the current vertex as visited
    visited[u] = true;

    // Recur for all the vertices adjacent to this vertex
    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfs(v, adj, visited, resultStack);
        }
    }

    // After all descendants of u have been visited and pushed to the stack,
    // push u itself onto the stack. This ensures that u comes before its
    // dependencies in the final reversed order.
    resultStack.push(u);
}

// Function to perform topological sort on a Directed Acyclic Graph (DAG)
// Parameters:
//   numVertices: The total number of vertices in the graph
//   adj: The adjacency list representation of the graph
// Returns:
//   A vector containing the vertices in topological order.
//   Returns an empty vector if the graph contains a cycle (though this
//   implementation assumes a DAG for simplicity and won't explicitly detect cycles).
vector<int> topologicalSort(int numVertices, const vector<vector<int>> &adj)
{
    // Initialize a boolean vector to keep track of visited vertices.
    // All vertices are initially unvisited.
    vector<bool> visited(numVertices, false);

    // Use a stack to store the topological order.
    // Vertices will be pushed onto the stack after all their dependent
    // vertices have been processed.
    stack<int> resultStack;

    // Iterate through all vertices. This ensures that all components
    // of a disconnected graph are also processed.
    for (int i = 0; i < numVertices; ++i)
    {
        if (!visited[i])
        {
            // If the vertex has not been visited, start a DFS from it.
            dfs(i, adj, visited, resultStack);
        }
    }

    // Transfer elements from the stack to a vector to get the final
    // topological order. The stack contains elements in reverse order.
    vector<int> topologicalOrder;
    while (!resultStack.empty())
    {
        topologicalOrder.push_back(resultStack.top());
        resultStack.pop();
    }

    return topologicalOrder;
}

int main()
{
    // Example Directed Acyclic Graph (DAG)
    // Vertices are 0, 1, 2, 3, 4, 5
    // Edges:
    // 5 -> 2
    // 5 -> 0
    // 4 -> 0
    // 4 -> 1
    // 2 -> 3
    // 3 -> 1

    int numVertices = 6;
    vector<vector<int>> adj(numVertices);

    // Add edges
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    cout << "Graph Edges (Adjacency List):" << endl;
    for (int i = 0; i < numVertices; ++i)
    {
        cout << i << " -> ";
        for (int neighbor : adj[i])
        {
            cout << neighbor << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Perform topological sort
    vector<int> sortedOrder = topologicalSort(numVertices, adj);

    // Print the topological order
    cout << "Topological Order: ";
    for (int vertex : sortedOrder)
    {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}
