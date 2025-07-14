#include <iostream>
#include <vector>

using namespace std;

void dfs(int current, vector<vector<int>> &adj, vector<bool> &visited, int &last_city)
{
    visited[current] = true;
    last_city = current;

    for (int neighbor : adj[current])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, adj, visited, last_city);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);
    visited[0] = true; // 0 is not used, but we keep it for 1-based indexing

    for (int i = 0; i < m; i++)
    {
        int c1, c2;
        cin >> c1 >> c2;
        adj[c1].push_back(c2);
        adj[c2].push_back(c1);
    }

    vector<pair<int, int>> roads;
    int last_city = 0;

    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            if (last_city != 0)
            {
                roads.push_back({last_city, i});
            }
            dfs(i, adj, visited, last_city);
        }
    }

    cout << roads.size() << endl;
    for (const auto &road : roads)
    {
        cout << road.first << " " << road.second << endl;
    }

    return 0;
}
