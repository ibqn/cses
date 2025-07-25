#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> adj(2 * n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[u].push_back({v + n, w / 2});
        adj[u + n].push_back({v + n, w});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> min_pq;

    constexpr long long INF(1e18);

    vector<long long> dist(2 * n + 1, INF);
    vector<bool> visited(2 * n + 1, 0);

    dist[1] = 0;

    min_pq.push({0, 1});

    while (!min_pq.empty())
    {
        int u = min_pq.top().second;
        min_pq.pop();

        if (visited[u])
        {
            continue;
        }

        visited[u] = true;

        for (auto &[v, c] : adj[u])
        {
            if (dist[u] + c < dist[v])
            {
                dist[v] = dist[u] + c;
                min_pq.push({dist[v], v});
            }
        }
    }

    cout << dist[2 * n] << endl;

    return 0;
}
