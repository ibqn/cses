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
        int a, b;
        long long w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }
    const long long INF = 1e18;
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        bool updated = false;
        for (auto &[a, b, w] : edges)
        {
            if (dist[b] > dist[a] + w)
            {
                dist[b] = dist[a] + w;
                updated = true;
            }
        }
        if (!updated)
        {
            break;
        }
    }

    for (int d = 1; d <= n; d++)
    {
        cout << dist[d] << " ";
    }
    cout << endl;
    return 0;
}
