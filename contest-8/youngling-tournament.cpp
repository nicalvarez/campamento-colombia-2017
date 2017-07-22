#include <bits/stdc++.h>

using namespace std;

#define endl '\n';

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct node
{
    int64 val, sum;
    int prio, size;
    node *l, *r;

    node(int64 val) : val(val), sum(val), prio(rand()),
                                size(1), l(0), r(0) {}
};

int size(node *u)
{
    return u ? u->size : 0;
}

int64 sum(node *u)
{
    return u ? u->sum : 0;
}

node *update(node *u)
{
    if (u)
    {
        u->sum = u->val + sum(u->l) + sum(u->r);
        u->size = 1 + size(u->l) + size(u->r);
    }

    return u;
}

node *merge(node *u, node *v)
{
    if (!u || !v) return u ? u : v;

    if (u->prio > v->prio)
    {
        u->r = merge(u->r, v);
        return update(u);
    }
    else
    {
        v->l = merge(u, v->l);
        return update(v);
    }
}

pair<node*, node*> split(node *u, int k)
{
    if (!u) return make_pair(nullptr, nullptr);

    if (size(u->l) >= k)
    {
        auto p = split(u->l, k);
        u->l = p.second;
        return make_pair(p.first, update(u));
    }
    else
    {
        auto p = split(u->r, k - size(u->l) - 1);
        u->r = p.first;
        return make_pair(update(u), p.second);
    }
}

int find_pos(node *u, int64 val){
    if (!u) return 0;
    if (u->val >= val) return find_pos(u->l, val);
    return size(u->l) + 1 + find_pos(u->r, val);
}

int64 F[maxn];
int64 G[maxn];

int solve(node *root, int n){
    int answer = 1;
    auto A = split(root, 2);
    int64 value = sum(A.first);
    auto B = split(A.first, 1);

    if (sum(B.second) >= sum(B.first))
        answer++;

    root = merge(B.first, B.second);
    root = merge(root, A.second);

    while (true){
        int k = find_pos(root, value);
        if (k == n) break;

        A = split(root, k);
        B = split(A.second, 1);

        if (sum(B.first) >= sum(A.first))
            answer++;

        value = sum(A.first) + sum(B.first);
        root = merge(B.first, B.second);
        root = merge(A.first, root);
    }

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 0; i < n; ++i){
        cin >> F[i];
        G[i] = F[i];
    }

    sort(G, G + n);

    int m; cin >> m;

    if (n == 1){
        for (int i = 0; i < m; ++i)
            cout << 1 << endl;
        exit(0);
    }

    node *root = new node(G[0]);

    for (int i = 1; i < n; ++i){
        node *u = new node(G[i]);
        root = merge(root, u);
    }

    cout << solve(root, n) << endl;

    while (m--){
        int k;
        int64 v;
        cin >> k >> v;
        k--;

        int tless = find_pos(root, F[k]);
        auto A = split(root, tless);
        auto B = split(A.second, 1);

        root = merge(A.first, B.second);

        F[k] = v;

        tless = find_pos(root, F[k]);
        A = split(root, tless);
        node *u = new node(F[k]);

        root = merge(A.first, u);
        root = merge(root, A.second);

        cout << solve(root, n) << endl;
    }

    return 0;
}