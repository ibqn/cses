#include <iostream>
#include <vector>
#include <tuple>
#include <stack>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, long long>> edges;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        edges.push_back({a, b, w});
        adj[a].push_back(b);
    }

    const long long INF = -1e18;
    vector<long long> score(n + 1, INF);
    vector<bool> loop(n + 1, false);
    score[1] = 0;

    for (int i = 1; i <= n; i++)
    {
        bool can_stop = true;
        for (const auto &e : edges)
        {
            int a, b;
            long long w;
            tie(a, b, w) = e;

            if (score[a] != INF && score[a] + w > score[b])
            {
                score[b] = score[a] + w;
                if (i == n)
                {
                    loop[b] = true;
                }

                can_stop = false;
            }
        }

        if (can_stop)
        {
            break;
        }
    }

    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        if (loop[i] && !visited[i])
        {
            stack<int> s;
            s.push(i);
            while (!s.empty())
            {
                int a = s.top();
                s.pop();
                visited[a] = true;

                for (int b : adj[a])
                {
                    if (!visited[b])
                    {
                        s.push(b);
                    }
                }
            }
        }
    }

    if (visited[n])
    {
        cout << -1 << endl;
        return 0;
    }

    cout << score[n] << endl;
    return 0;
}
