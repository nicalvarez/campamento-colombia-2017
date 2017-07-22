#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl << flush;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = 60;
const int MAXE = MAXN * MAXN;

int head[MAXN], to[MAXE], nxt[MAXE], ec = 1;
int res[MAXE], cnt = 0;
bool mk[MAXN];

void add(int x, int y){
    ++ec;
    to[ec] = y;
    nxt[ec] = head[x];
    head[x] = ec;
}

void dfs(int s){
    mk[s] = true;
    for (int e = head[s]; e; e = nxt[e]){
        int y = to[e];

        if (res[e >> 1] == 0) res[e >> 1] = ++cnt;
        if (!mk[y]) dfs(y);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i){
        int u, v; cin >> u >> v;
        u--; v--;
        add(u, v);
        add(v, u);
    }

    dfs(0);
    cout << "YES" << endl;
    for (int i = 0; i < m; ++i)
        cout << res[i + 1] << " \n"[i + 1 == m];

    return 0;
}
