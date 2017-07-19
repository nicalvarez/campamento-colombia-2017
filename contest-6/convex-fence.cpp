/*
        Convex Hull
        Light OJ 1239
 */

#include <bits/stdc++.h>

using namespace std;

#define DB(x) cout << #x << "=" << x << endl
#define MP make_pair

typedef long long int64;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int MAXN = (int)1e5 + 10;
const int MOD = (int)1e9 + 7;
const double EPS = 1e-7;
const int oo = 1 << 30;

struct point{
    double x, y;
    point(){
        x = y = 0;
    }
    point(double X, double Y)
    {
        x = X, y = Y;
    }
    point operator -(const point &other) const
    {
        return point(x - other.x, y - other.y);
    }
};

bool cmp_points_y(const point &p1,const point &p2)
{
    if (p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
}

double cross(const point &a, const point &b)
{
    complex<double> A(a.x, a.y);
    complex<double> B(b.x, b.y);
    return imag(conj(A) * B);
}

vector<point> convex_hull(vector<point>& P)
{
    int n = P.size(), k = 0;
    vector<point> hull(2 * n);

    sort( P.begin(), P.end(),cmp_points_y);
    // lower-hull
    for (int i = 0; i < n; hull[ k++ ] = P[ i++ ])
        while (k >= 2 &&
            cross( hull[k - 2]-P[i], hull[k - 1]-P[i]) < EPS)
            --k;
    // upper-hull
    for (int i = n - 2, t = k + 1; i >= 0; hull[ k++ ] = P[ i-- ])
            while (k >= t &&
                cross( hull[k - 2]-P[i], hull[k - 1]-P[i]) < EPS)
                --k;

    hull.resize(k - 1);
    return hull;
}

double sqr(double a){
    return a * a;
}

double dist(point &a, point &b)
{
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    int T; cin >> T;
    int tc = 1;

    while (T--)
    {
        int N;
        double D;
        cin >> N >> D;
        vector<point> V;
        double ans = 2 * M_PI * D;

        for (int i = 0; i < N; ++i){
            double x, y; cin >> x >> y;
            V.push_back( point(x, y) );
        }

        cout << "Case " << tc++ << ": ";

        if (N == 1)
        {
            cout.precision(9);
            cout << fixed << ans << endl;
        }
        else
        {
            vector<point> CH = convex_hull(V);
            for (int i = 0; i < (int)CH.size(); ++i){
                ans += dist(CH[i], CH[(i + 1) % (int)CH.size()]);
            }
            cout.precision(9);
            cout << fixed << ans << endl;
        }
    }

    return 0;
}
