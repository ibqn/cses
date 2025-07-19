#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int u, const vector<vector<int>> &adj, vector<bool> &visited, stack<int> &resultStack)
{
    visited[u] = true;

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfs(v, adj, visited, resultStack);
        }
    }

    resultStack.push(u);
}

vector<int> topologicalSort(int numVertices, const vector<vector<int>> &adj)
{
    vector<bool> visited(numVertices, false);
    stack<int> resultStack;

    for (int i = 0; i < numVertices; ++i)
    {
        if (!visited[i])
        {
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

    vector<int> sortedOrder = topologicalSort(numVertices, adj);

    cout << "Topological Order: ";
    for (int vertex : sortedOrder)
    {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}
