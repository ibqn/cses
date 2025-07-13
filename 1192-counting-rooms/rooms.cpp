#include <iostream>
#include <vector>
#include <string>

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
    vector<bool> visited(n * m, false);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int idx = i * m + j;

            if (lines[i][j] == '#')
            {
                visited[idx] = true;
                continue;
            }

            if (i > 0 && lines[i - 1][j] == '.')
            {
                adj[idx].push_back(idx - m);
            }
            if (i < n - 1 && lines[i + 1][j] == '.')
            {
                adj[idx].push_back(idx + m);
            }
            if (j > 0 && lines[i][j - 1] == '.')
            {
                adj[idx].push_back(idx - 1);
            }
            if (j < m - 1 && lines[i][j + 1] == '.')
            {
                adj[idx].push_back(idx + 1);
            }
        }
    }

    int room_count = 0;

    for (int i = 0; i < n * m; ++i)
    {
        if (visited[i])
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
