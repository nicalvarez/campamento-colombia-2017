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
const int MAXN = (int)1e6 + 10;

int n, q, l;
int V[MAXN], W[MAXN];

int tot_nodes;
int ST[MAXN * 8];
int LT[MAXN * 8];
int RT[MAXN * 8];
int ROOT[MAXN];

int getid(int x){
    return lower_bound(W, W + l, x) - W;
}

int new_node(){
    assert(tot_nodes < 8 * MAXN);
    return tot_nodes++;
}

int clone(int x)
{
    int cur = new_node();
    ST[cur] = ST[x];
    LT[cur] = LT[x];
    RT[cur] = RT[x];
    return cur;
}

int build(int b, int e){
    if (b == e) return new_node();
    else{
        int cur = new_node();
        int mid = (b + e) >> 1;
        LT[cur] = build(b, mid);
        RT[cur] = build(mid + 1, e);
        return cur;
    }
}

int update(int node, int b, int e, int x)
{
    node = clone(node);
    ST[node]++;
    if (b != e){
        int mid = (b + e) >> 1;
        if (x <= mid) LT[node] = update(LT[node], b, mid, x);
        else RT[node] = update(RT[node], mid + 1, e, x);
    }
    return node;
}

int get_kth(int b, int e, int node1, int node2, int kth)
{
    if (b == e) return b;

    int mid = (b + e) >> 1;
    int tot_left = ST[ LT[node2] ] - ST[ LT[node1] ];

    if (tot_left >= kth)
        return get_kth(b, mid, LT[node1], LT[node2], kth);
    else
        return get_kth(mid + 1, e, RT[node1], RT[node2], kth - tot_left);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;
    for (int i = 0; i < n; ++i)
    {
        cin >> V[i];
        W[i] = V[i];
    }

    sort(W, W + n);
    l = unique(W, W + n) - W;

    ROOT[0] = build(0, l - 1);

    for (int i = 0; i < n; ++i){
        ROOT[i + 1] = update(ROOT[i], 0, l - 1, getid(V[i]));
    }

    while (q--)
    {
        int b, e, k;
        cin >> b >> e >> k;
        b--;
        cout << W[get_kth(0, l - 1, ROOT[b], ROOT[e], k)] << endl;
    }


    return 0;
}