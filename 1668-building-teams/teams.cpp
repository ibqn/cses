#include <iostream>
#include <vector>

using namespace std;

bool dfs(int node, vector<vector<int>> &adj, vector<int> &team)
{
    for (int neighbor : adj[node])
    {
        if (team[neighbor] == 0)
        {
            team[neighbor] = team[node] % 2 + 1;
            if (!dfs(neighbor, adj, team))
            {
                return false;
            }
        }
        else if (team[neighbor] == team[node])
        {
            return false;
        }
    }
    return true;
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

    vector<int> team(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        if (team[i] == 0)
        {
            team[i] = 1;
            if (!dfs(i, adj, team))
            {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << team[i] << " ";
    }
    cout << endl;

    return 0;
}
