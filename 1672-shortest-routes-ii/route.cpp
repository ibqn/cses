#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

using namespace std;

void draw(const vector<vector<long long>> &dist, int n)
{
    const long long INF = 1e18;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << setw(2);
            if (dist[i][j] == INF)
            {
                cout << "I";
            }
            else
            {
                cout << dist[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<long long>> distance(n, vector<long long>(n));
    const long long INF = 1e18;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            distance[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        --u;
        --v;
        distance[u][v] = distance[v][u] = min(distance[u][v], c);
    }

    // draw(distance, n);

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; j++)
            {
                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }

    // draw(distance, n);

    for (int i = 0; i < q; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        cout << (distance[u][v] == INF ? -1 : distance[u][v]) << endl;
    }

    return 0;
}
