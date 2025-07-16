#include <iostream>
#include <vector>

using namespace std;

int dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &parent)
{
    for (int neighbor : adj[node])
    {
        if (!visited[neighbor])
        {
            visited[neighbor] = true;
            parent[neighbor] = node;

            int node = dfs(neighbor, adj, visited, parent);
            if (node)
            {
                return node;
            }
        }
        else
        {
            if (parent[node] != neighbor)
            {
                parent[neighbor] = node;
                return neighbor;
            }
        }
    }
    return 0;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> parent(n + 1, -1);
    vector<bool> visited(n + 1, false);

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;

            int node = dfs(i, adj, visited, parent);
            if (node)
            {
                vector<int> path;
                path.push_back(node);
                for (int at = parent[node]; at != node; at = parent[at])
                {
                    path.push_back(at);
                }
                path.push_back(node);

                cout << path.size() << endl;
                for (int i : path)
                {
                    cout << i << " ";
                }
                cout << endl;
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE" << endl;
    return 0;
}
