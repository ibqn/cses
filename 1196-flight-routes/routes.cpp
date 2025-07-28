#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    unsigned int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, long long>>> adj(n + 1);

    for (unsigned int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> min_pq;

    vector<vector<long long>> dist(n + 1);

    min_pq.push({0, 1});
    while (!min_pq.empty())
    {
        auto [d, u] = min_pq.top();
        min_pq.pop();

        if (dist[u].size() >= k)
        {
            continue;
        }
        dist[u].push_back(d);

        for (auto [v, w] : adj[u])
        {
            if (dist[v].size() < k)
            {
                min_pq.push({d + w, v});
            }
        }
    }

    // sort(dist[n].begin(), dist[n].end());
    for (auto &d : dist[n])
    {
        cout << d << " ";
    }
    cout << endl;

    return 0;
}
