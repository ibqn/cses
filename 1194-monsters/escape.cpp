#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

void draw(const vector<int> &dist, int n, int m)
{
    const int INF = 1e9;
    for (int i = 0; i < n * m; ++i)
    {
        int d = dist[i];

        if (d == INF)
        {
            cout << " I";
        }
        else
        {
            cout << setw(2) << d;
        }
        if ((i + 1) % m == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
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

    queue<int> a_queue;
    vector<int> a_dist(n * m, INF);
    vector<bool> a_visited(n * m, false);
    vector<int> a_parent(n * m, -1);

    a_queue.push(start);
    a_dist[start] = 0;
    a_visited[start] = true;

    while (!a_queue.empty())
    {
        int current = a_queue.front();
        a_queue.pop();

        for (int neighbor : adj[current])
        {
            if (!a_visited[neighbor])
            {
                a_queue.push(neighbor);
                a_dist[neighbor] = a_dist[current] + 1;
                a_parent[neighbor] = current;
                a_visited[neighbor] = true;
            }
        }
    }

    // draw(a_dist, n, m);

    queue<int> monster_queue;
    vector<int> monster_dist(n * m, INF);

    for (int mo : monster)
    {
        monster_queue.push(mo);
        monster_dist[mo] = 0;
    }

    while (!monster_queue.empty())
    {
        int current = monster_queue.front();
        monster_queue.pop();

        for (int neighbor : adj[current])
        {
            if (monster_dist[neighbor] > monster_dist[current] + 1)
            {
                monster_queue.push(neighbor);
                monster_dist[neighbor] = monster_dist[current] + 1;
            }
        }
    }

    // draw(monster_dist, n, m);

    for (int e : exit)
    {
        if (a_dist[e] != INF && monster_dist[e] > a_dist[e])
        {
            cout << "YES" << endl;

            vector<int> path;
            for (int v = e; v != -1; v = a_parent[v])
            {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());
            cout << path.size() - 1 << endl;
            for (size_t v = 1; v < path.size(); ++v)
            {
                char dir = '?';
                int diff = path[v] - path[v - 1];
                if (diff == -m)
                    dir = 'U';
                else if (diff == m)
                    dir = 'D';
                else if (diff == -1)
                    dir = 'L';
                else if (diff == 1)
                    dir = 'R';

                cout << dir;
            }
            cout << endl;
            return 0;
        }
    }

    cout << "NO" << endl;

    return 0;
}
