#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

double test(double x, double y, double d){
    double hx = sqrt(x * x - d * d);
    double hy = sqrt(y * y - d * d);

    // y: y = hy / d * x
    // x: y = -hx / d * x + hx
    //    hy * x = -hx * x + hx * d
    //    (hy + hx) * x = hx * d
    //    x = (hx * d) / (hy + hx)
    //    y = hx * hy / (hx + hy)

    double c = hx * hy / (hx + hy);
    return c;
}

void solve(){
    double x, y, c;
    cin >> x >> y >> c;

    double l = 0, h = min(x, y);

    for (int i = 0; i < 100; ++i){
        double m = (l + h) / 2;

        if (test(x, y, m) < c) h = m;
        else l = m;
    }

    cout.precision(17);
    cout << (l + h) / 2 << endl;
}

int main()
{
#ifdef MARX
    freopen("data.in", "r", stdin);
#endif

    int t; cin >> t;

    for (int tc = 1; tc <= t; ++tc){
        cout << "Case " << tc << ": ";
        solve();
    }

    return 0;
}