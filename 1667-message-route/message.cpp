#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);

    for (int i = 0; i < m; i++)
    {
        int c1, c2;
        cin >> c1 >> c2;
        adj[c1].push_back(c2);
        adj[c2].push_back(c1);
    }

    vector<int> path(n + 1, -1);
    vector<int> distance(n + 1, -1);

    distance[1] = 1;
    queue<int> queue;
    queue.push(1);
    visited[1] = true;

    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop();

        if (current == n)
        {
            break;
        }

        for (int neighbor : adj[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
                path[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    if (distance[n] == -1)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<int> route;
    for (int at = n; at != -1; at = path[at])
    {
        route.push_back(at);
    }
    reverse(route.begin(), route.end());

    cout << route.size() << endl;
    for (int c : route)
    {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
