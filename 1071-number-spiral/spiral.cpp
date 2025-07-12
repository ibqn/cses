#include <iostream>
#include <cassert>

using namespace std;

void swap(long long &a, long long &b)
{
    long long temp = a;
    a = b;
    b = temp;
}

void test_case()
{
    long long row, col;
    cin >> row >> col;

    long long n = max(row, col);
    long long first = (n - 1) * (n - 1) + 1;
    long long last = n * n;

    if (n % 2 == 1)
    {
        swap(row, col);
    }

    long long ans;

    if (n == col)
    {
        ans = first + (row - 1);
    }
    else
    {
        assert(row == n);
        ans = last - (col - 1);
    }

    cout << ans << endl;
}

int main()
{
    int t;
    cin >> t;

    assert(t >= 1);

    while (t--)
    {
        test_case();
    }
}
