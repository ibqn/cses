#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

namespace KnightTour
{
    const int N = 8;
    const int TOTAL = N * N;

    uint64_t visited = 0ULL;
    int tour[TOTAL];
    vector<int> moves[64];

    int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    inline bool isValid(int pos)
    {
        return !(visited & (1ULL << pos));
    }

    inline int degree(int pos)
    {
        int cnt = 0;
        for (int nxt : moves[pos])
        {
            if (isValid(nxt))
                cnt++;
        }
        return cnt;
    }

    vector<int> nextMoves(int pos, mt19937 &rng)
    {
        vector<int> cand;
        for (int nxt : moves[pos])
        {
            if (isValid(nxt))
                cand.push_back(nxt);
        }
        shuffle(cand.begin(), cand.end(), rng);
        sort(cand.begin(), cand.end(), [&](int a, int b)
             { return degree(a) < degree(b); });
        return cand;
    }

    bool dfs(int pos, int step, int start, mt19937 &rng)
    {
        if (step == TOTAL)
        {
            for (int nxt : moves[pos])
            {
                if (nxt == start)
                    return true; // closed tour found
            }
            return false;
        }

        auto cand = nextMoves(pos, rng);
        for (int nxt : cand)
        {
            visited |= (1ULL << nxt);
            tour[step] = nxt;
            if (dfs(nxt, step + 1, start, rng))
                return true;
            visited &= ~(1ULL << nxt); // backtrack
        }
        return false; // only after trying ALL moves
    }

    void runKnightTour()
    {
        // Precompute moves
        for (int x = 0; x < N; x++)
        {
            for (int y = 0; y < N; y++)
            {
                int idx = x * N + y;
                for (int k = 0; k < 8; k++)
                {
                    int nx = x + dx[k], ny = y + dy[k];
                    if (nx >= 0 && nx < N && ny >= 0 && ny < N)
                    {
                        moves[idx].push_back(nx * N + ny);
                    }
                }
            }
        }

        cout << "precomputed completed\n";

        mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

        int start = 0; // start at (0,0)
        visited = 0ULL;
        visited |= (1ULL << start);
        tour[0] = start;

        if (dfs(start, 1, start, rng))
        {
            vector<vector<int>> board(N, vector<int>(N, -1));
            for (int i = 0; i < TOTAL; i++)
            {
                int pos = tour[i];
                int x = pos / N, y = pos % N;
                board[x][y] = i;
            }
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    cout << setw(2) << board[i][j] << " ";
                }
                cout << "\n";
            }
        }
        else
        {
            cout << "No closed tour found!\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    KnightTour::runKnightTour();
    return 0;
}
