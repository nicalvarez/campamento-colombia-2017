#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int64,int64> pii;
typedef vector<int> vi;
typedef complex<double> point;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

inline int64 sqr(int64 v) { return v * v; }

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    point w = polar(1.0, 2.0);

    int t; cin >> t;

    while (t--){
        int n; cin >> n;

        vector<pii> R(n);
        vector<pair<double,int>> L(n);
        vector<int64> A(n);

        for (int i = 0; i < n; ++i){
            cin >> R[i].first >> R[i].second;

            point p(R[i].first, R[i].second);
            point v = p * w;
            L[i] = {real(v), i};
        }

        sort(L.begin(), L.end());

        auto dist = [&](int u, int v){
            return sqr(R[u].first - R[v].first) + sqr(R[u].second - R[v].second);
        };

        for (int i = 0; i < n; ++i){
            queue<pair<int,int>> q;

            int64 best = dist( L[i].second, L[(i + 1) % n].second );
            double sbest;

            if (i){ q.push({i - 1, -1}); best = min(best, dist(L[i].second, L[i - 1].second) ); }
            if (i + 1 < n) q.push({i + 1, +1});

            sbest = sqrt(best);

            while (!q.empty()){
                auto cur = q.front(); q.pop();
                int nxt = cur.first + cur.second;

                if (nxt == -1 || nxt == n) continue;
                if ( abs(L[i].first - L[nxt].first) > sbest ) continue;

                q.push({nxt, cur.second});

                int64 tmp = dist(L[i].second, L[nxt].second);

                if (tmp < best){
                    best = tmp;
                    sbest = sqrt(best);
                }
            }

            A[ L[i].second ] = best;
        }

        for (int i = 0; i < n; ++i)
            cout << A[i] << endl;
    }

    return 0;
}