/*
     Author:    MarX
     School:    UH
 */

#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define DB(x) cout << #x << "=" << x << endl
#define PB push_back

typedef unsigned long long int64;
typedef vector<int> vi;
typedef pair<int,int> pii;

const int oo = 1 << 30;
const double EPS = 1e-7;
const int MAXN = 1e5 + 10;
const int MAXV = 3*((int)1e4) + 10;

bool compare(const pii &a, const pii &b)
{
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
}

int ST[MAXV << 2];
pii T[MAXN];

void update(int p, int b, int e, int x, int v)
{
    if (b == e)
    {
        ST[p] = max(v,ST[p]);
        return;
    }

    int mid = (b + e) >> 1;
    int left = p << 1;
    int right = left | 1;
    if (x <= mid)
        update(left,b,mid,x,v);
    else
        update(right,mid + 1,e,x,v);
    ST[p] = max(ST[left],ST[right]);
}

int query(int p, int b, int e, int x)
{
    if (e <= x)
        return ST[p];

    int mid = (b + e) >> 1;
    int left = p << 1;
    int right = left | 1;
    if (x <= mid)
        return query(left,b,mid,x);
    else
        return max(ST[left],query(right,mid + 1,e,x));
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        cin >> T[i].first >> T[i].second;
        T[i].first++;
        T[i].second++;
    }

    sort(T,T + N);

    int ans = 0;

    for (int i = 0; i < N; ++i)
    {
        int v = query(1,0,MAXV - 1,T[i].first - 1) + 1;
        ans = max(v,ans);
        update(1,0,MAXV - 1,T[i].second,v);
    }
    cout << ans << endl;

    return 0;
}
