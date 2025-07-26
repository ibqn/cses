#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, long long>> edges(m);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        edges[i] = {u, v, w};
    }

    vector<long long> dist(n + 1, 0);
    vector<int> parent(n + 1, -1);
    vector<bool> cycle(n + 1, false);

    for (int i = 0; i <= n; i++)
    {
        bool updated = false;
        for (const auto &[u, v, w] : edges)
        {
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (i == n)
                {
                    cycle[v] = true;
                }
                updated = true;
            }
        }
        if (!updated)
        {
            break;
        }
    }

    int cycle_start = -1;
    for (int i = 1; i <= n; i++)
    {
        if (cycle[i])
        {
            cycle_start = i;
            break;
        }
    }

    if (cycle_start != -1)
    {
        cout << "YES" << endl;
        // Move to a node that's definitely in the cycle
        // by following parent pointers for n steps
        for (int i = 0; i < n; i++)
        {
            cycle_start = parent[cycle_start];
        }
        vector<int> cycle_path;
        cycle_path.push_back(cycle_start);
        for (int v = parent[cycle_start]; v != cycle_start; v = parent[v])
        {
            cycle_path.push_back(v);
        }
        cycle_path.push_back(cycle_start);
        for (auto it = cycle_path.rbegin(); it != cycle_path.rend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}
