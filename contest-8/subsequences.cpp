#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

int64 bit[12][100001];

int64 read(int idx, int k){
    int64 ans = 0;
    while (idx){
        ans += bit[k][idx];
        idx -= idx & -idx;
    }
    return ans;
}

void update(int idx, int k, int64 v){
    while (idx < 100001){
        bit[k][idx] += v;
        idx += idx & -idx;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k; cin >> n >> k; ++k;
    for (int i = 0; i < n; ++i){
        int v; cin >> v;
        update(v, 1, 1);
        for (int j = 2; j <= k; ++j)
            update(v, j, read(v - 1, j - 1));
    }

    cout << read(n, k) << endl;

    return 0;
}