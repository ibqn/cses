#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
    }

    const long long INF = 1e18;
    vector<bool> visited(n + 1, false);
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, 1});

    while (!pq.empty())
    {
        int a = pq.top().second;
        pq.pop();

        if (visited[a])
        {
            continue;
        }
        visited[a] = true;

        for (auto &[b, w] : adj[a])
        {
            if (dist[a] + w < dist[b])
            {
                dist[b] = dist[a] + w;
                pq.push({dist[b], b});
            }
        }
    }

    for (int d = 1; d <= n; d++)
    {
        cout << dist[d] << " ";
    }
    cout << endl;
    return 0;
}
