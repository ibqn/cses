#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

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
    vector<int> parent(n * m, -1);
    vector<int> distance(n * m, -1);
    int source = -1;
    int destination = -1;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (lines[i][j] == '#')
            {
                continue;
            }

            int idx = i * m + j;

            if (lines[i][j] == 'A')
            {
                source = idx;
            }
            else if (lines[i][j] == 'B')
            {
                destination = idx;
            }

            if (i > 0 && lines[i - 1][j] != '#')
            {
                adj[idx].push_back((i - 1) * m + j);
            }
            if (i < n - 1 && lines[i + 1][j] != '#')
            {
                adj[idx].push_back((i + 1) * m + j);
            }
            if (j > 0 && lines[i][j - 1] != '#')
            {
                adj[idx].push_back(i * m + (j - 1));
            }
            if (j < m - 1 && lines[i][j + 1] != '#')
            {
                adj[idx].push_back(i * m + (j + 1));
            }
        }
    }

    vector<bool> visited(n * m, false);
    queue<int> queue;

    queue.push(source);
    visited[source] = true;
    distance[source] = 0;

    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop();

        if (current == destination)
        {
            break;
        }

        for (int neighbor : adj[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = current;
                distance[neighbor] = distance[current] + 1;
                queue.push(neighbor);
            }
        }
    }

    if (distance[destination] == -1)
    {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    cout << distance[destination] << endl;

    vector<int> path;
    for (int at = destination; at != -1; at = parent[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    for (size_t i = 1; i < path.size(); ++i)
    {
        int from = path[i - 1];
        int to = path[i];

        char direction = '?';
        if (to - from == 1)
        {
            direction = 'R'; // Right: same row, col + 1
        }
        else if (to - from == -1)
        {
            direction = 'L'; // Left: same row, col - 1
        }
        else if (to - from == m)
        {
            direction = 'D'; // Down: row + 1, same col
        }
        else if (to - from == -m)
        {
            direction = 'U'; // Up: row - 1, same col
        }
        else
        {
            cerr << "Unexpected path direction!" << endl;
            return 1; // Error handling
        }

        cout << direction;
    }
    cout << endl;

    return 0;
}
