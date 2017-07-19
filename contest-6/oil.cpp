#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

typedef complex<int64> point;

int64 cross(point a, point b)
{
    return imag(conj(a) * b);
}

struct interval
{
    int64 xl, xh, y;
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<interval> I(n);

    for (auto &ii : I)
    {
        cin >> ii.xl >> ii.xh >> ii.y;
        if (ii.xl > ii.xh) swap(ii.xl, ii.xh);
    }

    int64 ans = 0;

    for (int i = 0; i < n; ++i)
    {
        vector<pair<point, int64>> events;

        for (int j = 0; j < n; ++j)
            if (I[i].y != I[j].y)
            {
                if (I[i].y < I[j].y)
                {
                    int64 v = I[j].xh - I[j].xl;
                    point a(I[j].xh - I[i].xl, I[j].y - I[i].y);
                    point b(I[j].xl - I[i].xl, I[j].y - I[i].y);
                    events.push_back({a, +v});
                    events.push_back({b, -v});
                }
                else
                {
                    int64 v = I[j].xh - I[j].xl;
                    point a(I[j].xh - I[i].xl, I[j].y - I[i].y);
                    point b(I[j].xl - I[i].xl, I[j].y - I[i].y);
                    a = a * point(-1, 0);
                    b = b * point(-1, 0);
                    events.push_back({b, +v});
                    events.push_back({a, -v});
                }
            }

        auto cmp2 = [](pair<point, int64> a, pair<point, int64> b)
        {
            if (cross(a.first, b.first) != 0)
                return cross(a.first, b.first) > 0;
            return a.second > b.second;
        };

        sort(events.begin(), events.end(), cmp2);

        int64 val = 0, mx = 0;

        for (auto &e : events)
            val += e.second, mx = max(mx, val);

        ans = max(ans, mx + I[i].xh - I[i].xl);
    }

    for (int i = 0; i < n; ++i)
    {
        vector<pair<point, int64>> events;

        for (int j = 0; j < n; ++j)
            if (I[i].y != I[j].y)
            {
                if (I[i].y < I[j].y)
                {
                    int64 v = I[j].xh - I[j].xl;
                    point a(I[j].xh - I[i].xh, I[j].y - I[i].y);
                    point b(I[j].xl - I[i].xh, I[j].y - I[i].y);
                    events.push_back({a, +v});
                    events.push_back({b, -v});
                }
                else
                {
                    int64 v = I[j].xh - I[j].xl;
                    point a(I[j].xh - I[i].xh, I[j].y - I[i].y);
                    point b(I[j].xl - I[i].xh, I[j].y - I[i].y);
                    a = a * point(-1, 0);
                    b = b * point(-1, 0);
                    events.push_back({b, +v});
                    events.push_back({a, -v});
                }
            }

        auto cmp2 = [](pair<point, int64> a, pair<point, int64> b)
        {
            if (cross(a.first, b.first) != 0)
                return cross(a.first, b.first) > 0;
            return a.second > b.second;
        };

        sort(events.begin(), events.end(), cmp2);

        int64 val = 0, mx = 0;

        for (auto &e : events)
            val += e.second, mx = max(mx, val);

        ans = max(ans, mx + I[i].xh - I[i].xl);
    }

    cout << ans << endl;

    return 0;
}