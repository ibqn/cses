#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<string> lines;

    for (int i = 0; i < n; ++i)
    {
        string line;
        cin >> line;
        lines.push_back(line);
    }

    vector<vector<int>> adj(n * m);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (lines[i][j] == '#')
            {
                continue;
            }

            int idx = i * m + j;

            if (i > 0 && lines[i - 1][j] == '.')
            {
                adj[idx].push_back((i - 1) * m + j);
            }
            if (i < n - 1 && lines[i + 1][j] == '.')
            {
                adj[idx].push_back((i + 1) * m + j);
            }
            if (j > 0 && lines[i][j - 1] == '.')
            {
                adj[idx].push_back(i * m + (j - 1));
            }
            if (j < m - 1 && lines[i][j + 1] == '.')
            {
                adj[idx].push_back(i * m + (j + 1));
            }
        }
    }

    vector<bool> visited(n * m, false);
    int room_count = 0;

    for (int i = 0; i < n * m; ++i)
    {
        if (lines[i / m][i % m] == '#' || visited[i])
        {
            continue;
        }

        room_count++;

        visited[i] = true;
        vector<int> stack = {i};

        while (!stack.empty())
        {
            int current = stack.back();
            stack.pop_back();

            for (int neighbor : adj[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    stack.push_back(neighbor);
                }
            }
        }
    }

    cout << room_count << endl;

    return 0;
}
