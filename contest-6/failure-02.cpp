#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int64,int64> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct point{
    double x, y;
    int id;

    point(double x=0, double y=0, int id=-1) : x(x), y(y), id(id) {}

    bool operator <(const point &q) const{
        if (x != q.x) return x < q.x;
        return y < q.y;
    }

    point operator+(const point &q) const{
        return point(x + q.x, y + q.y);
    }

    point operator-(const point &q) const{
        return point(x - q.x, y - q.y);
    }
};

double norm(point p) { return p.x * p.x + p.y * p.y; }
double abs(point p) { return sqrt( norm(p) ); }

struct vantage_point_tree
{
    struct node
    {
        point p;
        double th;
        node *l, *r;
    }*root;

    vector<pair<double, point>> aux;

    vantage_point_tree(vector<point> ps)
    {
        for (int i = 0; i < ps.size(); ++i)
            aux.push_back({ 0, ps[i] });
        root = build(0, ps.size());
    }

    node *build(int l, int r)
    {
        if (l == r)
            return 0;
        swap(aux[l], aux[l + rand() % (r - l)]);
        point p = aux[l++].second;
        if (l == r)
            return new node({ p });
        for (int i = l; i < r; ++i)
            aux[i].first = norm(p - aux[i].second);
        int m = (l + r) / 2;
        nth_element(aux.begin() + l, aux.begin() + m, aux.begin() + r);
        return new node({ p, sqrt(aux[m].first), build(l, m), build(m, r) });
    }

    priority_queue<pair<double, node*>> que;

    void k_nn(node *t, point p, int k)
    {
        if (!t)
            return;
        double d = abs(p - t->p);
        if (que.size() < k)
            que.push({ d, t });
        else if (que.top().first > d)
        {
            que.pop();
            que.push({ d, t });
        }
        if (!t->l && !t->r)
            return;
        if (d < t->th)
        {
            k_nn(t->l, p, k);
            if (t->th - d <= que.top().first)
                k_nn(t->r, p, k);
        }
        else
        {
            k_nn(t->r, p, k);
            if (d - t->th <= que.top().first)
                k_nn(t->l, p, k);
        }
    }

    vector<point> k_nn(point p, int k)
    {
        k_nn(root, p, k);
        vector<point> ans;
        for (; !que.empty(); que.pop())
            ans.push_back(que.top().second->p);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

inline int64 sqr(int64 a) { return a * a; }

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t--){
        int n; cin >> n;

        vector<point> L(n);
        vector<pii> R(n);

        for (int i = 0; i < n; ++i){
            cin >> R[i].first >> R[i].second;
            L[i] = point(R[i].first, R[i].second, i);
        }

        vantage_point_tree tree(L);

        auto dist = [&](int u, int v){
            return sqr(R[u].first - R[v].first) + sqr(R[u].second - R[v].second);
        };

        for (int i = 0; i < n; ++i){
            auto closest = tree.k_nn(L[i], 2);
            int it = 0;

            int64 value = dist(i, closest[1].id);
            cout << value << endl;
        }
    }

    return 0;
}