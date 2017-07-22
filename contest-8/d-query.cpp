#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout<<#x<<"="<<x<<endl;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;
const int MAXA = (int)1e6 + 10;
const int MAXQ = (int)2e5 + 10;

int BIT[MAXN];
int LAST[MAXA];
int V[MAXN], ANS[MAXQ];
pair<pii,int> Q[MAXQ];

void update(int idx, int val){
    while (idx < MAXN){
        BIT[idx] += val;
        idx += idx&-idx;
    }
}

int read(int idx){
    int ans = 0;
    while (idx){
        ans += BIT[idx];
        idx -= idx&-idx;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> V[i];
    }

    int q; cin >> q;
    for (int i = 0; i < q; ++i){
        int b, e; cin >> b >> e;
        --b;
        Q[i] = MP( MP(e, b), i);
    }
    sort(Q, Q + q);
    int p = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (LAST[V[i]])
            update(LAST[V[i]], -1);

        LAST[V[i]] = i;
        update(i, 1);

        for (; p < q && Q[p].first.first == i; ++p){
            auto cur = Q[p];
            ANS[cur.second] = read(Q[p].first.first) - read(Q[p].first.second);
        }
    }

    for (int i = 0; i < q; ++i)
        cout << ANS[i] << endl;

    return 0;
}