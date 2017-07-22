#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

int64 dp[510][510];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 0; i <= n; ++i){
        for (int j = 0; j <= n; ++j){
            if (j == 0) dp[i][j] = i ? 0 : 1;
            else if (j > i) dp[i][j] = dp[i][i];
            else dp[i][j] = dp[i - j][j - 1] + dp[i][j - 1];
        }
    }

    cout << dp[n][n] - 1 << endl;

    return 0;
}