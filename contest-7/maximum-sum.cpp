#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;

int n;
int t[maxn][maxn];

int subrect(int x1, int y1, int x2, int y2){
    x1--; y1--;
    return t[x2][y2] - (t[x2][y1] + t[x1][y2]) + t[x1][y1];
}

int solve(int x1, int x2){
    int best = subrect(x1, 1, x2, 1);
    int cur = 0;
    for (int i = 1; i <= n; ++i){
        if (cur < 0) cur = 0;
        cur += subrect(x1, i, x2, i);
        best = max(best, cur);
    }
    return best;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            int v; cin >> v;
            t[i][j] = t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1] + v;
        }
    }

    int ans = t[1][1];
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            ans = max(ans, solve(i, j));

    cout << ans << endl;
}