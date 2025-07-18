#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int &start, const vector<vector<int>> &adj, vector<bool> &visited, vector<int> &dist, vector<int> &parent)
{
    queue<int> queue;
    queue.push(start);
    dist[start] = 0;
    visited[start] = true;

    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop();

        for (int neighbor : adj[current])
        {
            if (!visited[neighbor])
            {
                queue.push(neighbor);
                dist[neighbor] = dist[current] + 1;
                parent[neighbor] = current;
                visited[neighbor] = true;
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<string> lines(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> lines[i];
    }

    vector<vector<int>> adj(n * m);
    vector<int> exit;
    vector<int> monster;
    int start = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int idx = i * m + j;

            if (lines[i][j] == '#')
            {
                continue;
            }

            if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
            {
                if (lines[i][j] != '#' && lines[i][j] != 'M')
                {
                    exit.push_back(idx);
                }
            }

            if (lines[i][j] == 'M')
            {
                monster.push_back(idx);
            }

            if (lines[i][j] == 'A')
            {
                start = idx;
            }

            if (i > 0 && lines[i - 1][j] != '#')
            {
                adj[idx].push_back(idx - m);
            }
            if (i < n - 1 && lines[i + 1][j] != '#')
            {
                adj[idx].push_back(idx + m);
            }
            if (j > 0 && lines[i][j - 1] != '#')
            {
                adj[idx].push_back(idx - 1);
            }
            if (j < m - 1 && lines[i][j + 1] != '#')
            {
                adj[idx].push_back(idx + 1);
            }
        }
    }

    const int INF = 1e9;

    for (int e : exit)
    {
        vector<bool> visited(n * m, false);
        vector<int> dist(n * m, INF);
        vector<int> parent(n * m, -1);

        bfs(e, adj, visited, dist, parent);

        int min_dist = INF;
        for (int mo : monster)
        {
            min_dist = min(min_dist, dist[mo]);
        }

        if (dist[start] != INF && min_dist > dist[start])
        {
            cout << "YES" << endl;

            vector<int> path;
            for (int v = start; v != -1; v = parent[v])
            {
                path.push_back(v);
            }

            cout << dist[start] << endl;
            for (size_t v = 1; v < path.size(); ++v)
            {
                char dir = '?';
                int diff = path[v] - path[v - 1];
                if (diff == -m)
                {
                    dir = 'U';
                }
                else if (diff == m)
                {
                    dir = 'D';
                }
                else if (diff == -1)
                {
                    dir = 'L';
                }
                else if (diff == 1)
                {
                    dir = 'R';
                }

                cout << dir;
            }
            cout << endl;
            return 0;
        }
    }

    cout << "NO" << endl;

    return 0;
}
