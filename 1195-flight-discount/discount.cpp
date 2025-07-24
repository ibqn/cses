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
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> min_pq;

    constexpr long long INF(1e18);

    vector<long long> dist_reg(n + 1, INF);
    vector<bool> visited_reg(n + 1, 0);
    vector<long long> discount_reg(n + 1, 0);

    dist_reg[1] = 0;
    discount_reg[1] = 0;

    min_pq.push({0, 1});

    while (!min_pq.empty())
    {
        int u = min_pq.top().second;
        min_pq.pop();

        if (visited_reg[u])
        {
            continue;
        }

        visited_reg[u] = true;

        for (auto &[v, c] : adj[u])
        {
            discount_reg[v] = max(discount_reg[u], c);

            if (dist_reg[u] + c < dist_reg[v])
            {
                dist_reg[v] = dist_reg[u] + c;
                min_pq.push({dist_reg[v], v});
            }
        }
    }

    vector<long long> dist(n + 1, INF);
    vector<bool> visited(n + 1, 0);
    vector<long long> discount_on(n + 1, 0);

    dist[1] = 0;
    discount_on[1] = 0;
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
            long long discount{c};
            if (discount_on[u] < c)
            {
                discount = c / 2 + discount_on[u] - discount_on[u] / 2;
            }

            if (dist[u] + discount < dist[v])
            {
                dist[v] = dist[u] + discount;

                discount_on[v] = max(discount_on[u], c);

                if (dist_reg[u] + c / 2 < dist[v])
                {
                    dist[v] = dist_reg[u] + c / 2;
                    discount_on[v] = c;
                }
                min_pq.push({dist[v], v});
            }
        }
    }

    cout << dist[n] << endl;

    return 0;
}
