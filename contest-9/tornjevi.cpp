#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct satisfiability_twosat
{
    int n;
    vector<vector<int>> imp;

    satisfiability_twosat(int n) : n(n), imp(2 * n) {}

    void add_edge(int u, int v)
    {
        imp[u].push_back(v);
    }

    int neg(int u) { return (n << 1) - u - 1; }

    void implication(int u, int v)
    {
        add_edge(u, v);
        add_edge(neg(v), neg(u));
    }

    void iff(int u, int v){
        implication(u, v);
        implication(v, u);
    }

    void force(int u){
        implication(neg(u), u);
    }

    void add_or(int u, int v){
        implication(neg(u), v);
    }

    vector<bool> solve()
    {
        int size = 2 * n;
        vector<int> S, B, I(size);

        function<void(int)> dfs = [&](int u)
        {
            B.push_back(I[u] = S.size());
            S.push_back(u);

            for (int v : imp[u])
                if (!I[v]) dfs(v);
                else while (I[v] < B.back()) B.pop_back();

            if (I[u] == B.back())
                for (B.pop_back(), ++size; I[u] < S.size(); S.pop_back())
                    I[S.back()] = size;
        };

        for (int u = 0; u < 2 * n; ++u)
            if (!I[u]) dfs(u);

        vector<bool> values(n);

        for (int u = 0; u < n; ++u)
            if (I[u] == I[neg(u)]) return {};
            else values[u] = I[u] < I[neg(u)];

        return values;
    }
};

char M[101][101];
int ID[101][101];
int T[101][101][4];

// direction  L  U  R  D
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int n, m, tower;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; ++i){
        cin >> M[i];

        for (int j = 0; j < m; ++j){
            if (M[i][j] == 'n'){
                for (int d = 0; d < 4; ++d)
                    T[i][j][d] = -1;
            }
            else if (M[i][j] == 'T'){
                ID[i][j] = tower;
                tower += 4;
            }
        }
    }

    satisfiability_twosat sat(tower);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (M[i][j] != 'T') continue;

            sat.iff(ID[i][j],     sat.neg(ID[i][j] + 2));
            sat.iff(ID[i][j] + 1, sat.neg(ID[i][j] + 3));

            for (int d = 0; d < 4; ++d){
                int x = i + dx[d], y = j + dy[d];
                bool bad = false;

                while (0 <= x && x < n && 0 <= y && y < m && !bad && M[x][y] != '#'){
                    if (M[x][y] == 'T') bad = true;
                    if (M[x][y] == 'n') T[x][y][d] = ID[i][j] + d;
                    x += dx[d], y += dy[d];
                }

                if (bad) sat.force( sat.neg( ID[i][j] + d ) );
            }
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j){
            if (M[i][j] != 'n') continue;

            if (T[i][j][0] > -1 && T[i][j][2] > -1) T[i][j][0] = T[i][j][2] = -1;
            if (T[i][j][1] > -1 && T[i][j][3] > -1) T[i][j][1] = T[i][j][3] = -1;

            vector<int> id;

            for (int d = 0; d < 4; ++d) if (T[i][j][d] > -1) id.push_back( T[i][j][d] );

            if (id.size() == 1) sat.force( id[0] );
            else if (id.size() == 2) sat.add_or( id[0], id[1] );
            else assert(false);
        }

    auto value = sat.solve();

    assert(!value.empty());

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (M[i][j] != 'T') continue;

            bool left  = value[ ID[i][j] ],    up   = value[ ID[i][j] + 1 ],
                 right = value[ ID[i][j] + 2], down = value[ ID[i][j] + 3 ];

            if (left && down)  M[i][j] = '1';
            if (down && right) M[i][j] = '2';
            if (right && up) M[i][j] = '3';
            if (up && left) M[i][j] = '4';
        }
    }

    for (int i = 0; i < n; ++i)
        cout << M[i] << endl;

    return 0;
}