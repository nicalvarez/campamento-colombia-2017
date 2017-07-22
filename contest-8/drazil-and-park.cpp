#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int64,int64> pii;
typedef vector<int64> vi;

const int64 oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct node{
    int64 a, b, c;
};

node merge(node A, node B){
    if (A.c < 0) return B;
    return {max(A.a, B.a), max(A.b, B.b), max({A.c, B.c, A.b + B.a})};
}

struct segment_tree{
    vector<node> st;

    segment_tree(int n){
        st = vector<node>(4 * n);
    }

    void build(int p, int b, int e, vi &H, vi &D){
        if (b + 1 == e){
            st[p] = {H[b] + D[b], H[b] - D[b], 0};
        }
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            build(l, b, m, H, D);
            build(r, m, e, H, D);

            st[p] = merge(st[l], st[r]);
        }
    }

    node query(int p, int b, int e, int x, int y){
        if (x <= b && e <= y) return st[p];
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;

            node answer = {0, 0, -1};

            if (x < m) answer = merge(answer, query(l, b, m, x, y));
            if (m < y) answer = merge(answer, query(r, m, e, x, y));

            return answer;
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    int N = 2 * n + 1;

    vi H(N), D(N);

    for (int i = 1; i <= n; ++i){
        cin >> D[i];
        D[i + n] = D[i];
    }

    for (int i = 0; i < n; ++i){
        cin >> H[i];
        H[i] = 2 * H[i];
        H[i + n] = H[i];
    }
    H[2 * n] = H[0];

    for (int i = 1; i <= 2 * n; ++i)
        D[i] += D[i - 1];


    segment_tree ST(N);

    ST.build(1, 0, N, H, D);

    while (m--){
        int a, b;
        cin >> a >> b;
        a--; b--;

        node answer;

        if (a <= b){
            answer = ST.query(1, 0, N, b + 1, a + n);
        }
        else{
            answer = ST.query(1, 0, N, b + 1, a);
        }

        cout << answer.c << endl;
    }


    return 0;
}