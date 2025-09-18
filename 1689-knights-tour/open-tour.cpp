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
    vector<vector<int>> board(N, vector<int>(N, -1));

    int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

    bool isValid(int x, int y)
    {
        return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
    }

    // Count onward moves
    int degree(int x, int y)
    {
        int cnt = 0;
        for (int k = 0; k < 8; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (isValid(nx, ny))
                cnt++;
        }
        return cnt;
    }

    // Generate candidate moves sorted by degree (Warnsdorff)
    vector<pair<int, int>> nextMoves(int x, int y)
    {
        vector<pair<int, int>> moves;
        for (int k = 0; k < 8; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (isValid(nx, ny))
            {
                moves.push_back({nx, ny});
            }
        }
        // Shuffle before sorting → randomize ties
        shuffle(moves.begin(), moves.end(), rng);
        sort(moves.begin(), moves.end(), [&](auto &a, auto &b)
             { return degree(a.first, a.second) < degree(b.first, b.second); });
        return moves;
    }

    bool dfs(int x, int y, int moveCount, int startX, int startY)
    {
        if (moveCount == N * N)
        {
            return true;
        }

        auto moves = nextMoves(x, y);
        for (auto [nx, ny] : moves)
        {
            board[nx][ny] = moveCount + 1;
            if (dfs(nx, ny, moveCount + 1, startX, startY))
                return true;
            board[nx][ny] = -1; // backtrack
        }
        return false;
    }

    void runKnightTour()
    {
        int startX, startY;
        cin >> startY >> startX;
        startX--;
        startY--;
        board[startX][startY] = 1;

        if (dfs(startX, startY, 1, startX, startY))
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    cout << board[i][j] << " ";
                }
                cout << "\n";
            }
        }
        else
        {
            cout << "No open tour found!\n";
        }
    }
}

int main()
{
    KnightTour::runKnightTour();
    return 0;
}
