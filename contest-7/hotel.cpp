#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;

int t[maxn][maxn];

int main()
{
    int n; cin >> n;
    int x = 0, y = n - 1;
    for (int i = 1; i <= n * n; ++i){
        t[x][y] = i;
        ++x, ++y;
        if (x == n || y == n){
            y = y - x - 1;
            x = 0;
            if (y < 0){
                x -= y;
                y = 0;
            }
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cout << t[i][j] << " \n"[j + 1 == n];
}