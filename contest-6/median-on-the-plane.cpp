#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef complex<int64> point;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

int64 cross(point a, point b){
    return imag(conj(a) * b);
}

bool compare(pair<point,int> a, pair<point,int> b){
    point pa = a.first, pb = b.first;
    return abs(pa) == 0 || cross(pa, pb) > 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
#endif

    int n; cin >> n;

    vector<pair<point,int>> V(n);

    int idx = 0;

    for (int i = 0; i < n; ++i){
        int64 x, y; cin >> x >> y;
        V[i] = {point(x, y), i + 1};

        if (y < V[idx].first.imag())
            idx = i;
    }

    point center = V[idx].first;

    for (int i = 0; i < n; ++i)
        V[i].first -= center;

    sort(V.begin(), V.end(), compare);

    cout << V[0].second << " " << V[n / 2].second << endl;

    return 0;
}