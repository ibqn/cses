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
    vector<int> moves[64];        // raw knight moves
    vector<int> orderedMoves[64]; // shuffled + sorted for each run

    int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

    inline bool isValid(int pos)
    {
        return !(visited & (1ULL << pos));
    }

    bool dfs(int pos, int step, int start)
    {
        if (step == TOTAL)
        {
            // must close tour
            for (int nxt : moves[pos])
                if (nxt == start)
                    return true;
            return false;
        }

        for (int nxt : orderedMoves[pos])
        {
            if (!isValid(nxt))
                continue;
            visited |= (1ULL << nxt);
            tour[step] = nxt;
            if (dfs(nxt, step + 1, start))
                return true;
            visited &= ~(1ULL << nxt); // backtrack
        }
        return false;
    }

    void prepareOrderedMoves()
    {
        for (int i = 0; i < TOTAL; i++)
        {
            orderedMoves[i] = moves[i];
            shuffle(orderedMoves[i].begin(), orderedMoves[i].end(), rng);
            sort(orderedMoves[i].begin(), orderedMoves[i].end(), [&](int a, int b)
                 { return moves[a].size() < moves[b].size(); });
        }
    }

    void runKnightTour()
    {
        // build raw moves (only once)
        static bool initialized = false;
        if (!initialized)
        {
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
            initialized = true;
        }

        // shuffle + sort before each run
        prepareOrderedMoves();

        int start = 0; // starting at (0,0)
        visited = 0ULL;
        visited |= (1ULL << start);
        tour[0] = start;

        if (dfs(start, 1, start))
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
