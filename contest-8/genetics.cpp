#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

struct node{
    int64 count[4], size;
    int idx;
    node *l, *r;
};

string dna = "AGTC";
map<char,int> dnaid;

int num(char c){
    return dnaid[ c ];
}

node* clone(node *u){
    node *v = new node();
    v->size = u->size, v->idx = u->idx;
    v->l = u->l, v->r = u->r;
    for (int i = 0; i < 4; ++i)
        v->count[i] = u->count[i];
    return v;
}

int64 size(node *u){
    return u ? u->size : 0LL;
}

int get(node *u, int p){
    return u ? u->count[p] : 0;
}

node *update(node *u){
    u->size = size(u->l) + size(u->r) + 1;

    for (int i = 0; i < 4; ++i)
        u->count[ i ] = get(u->l, i) + get(u->r, i);
    u->count[ u->idx ]++;
    return u;
}

node* merge( node *u, node *v ){
    if (!u || !v) return u ? u : v;

    int l = size(u), r = size(v);

    if (rand() % (l + r) < l){
        u = clone( u );
        u->r = merge( u->r, v );
        return update( u );
    }
    else{
        v = clone( v );
        v->l = merge(u, v->l);
        return update( v );
    }
}

pair<node*,node*> split(node *u, int k){
    if (!u) return make_pair(nullptr, nullptr);

    u = clone(u);

    if (k <= size( u->l )){
        auto cur = split( u->l, k );
        u->l = cur.second;
        return {cur.first, update(u) };
    }
    else{
        auto cur = split( u->r, k - size(u->l) - 1);
        u->r = cur.first;
        return {update(u), cur.second};
    }
}

node* build(int b, int e, string &s){
    if (b > e) return nullptr;

    int m = (b + e) >> 1;
    node *u = new node();

    u->idx = num( s[m] );
    u->l = build(b, m - 1, s);
    u->r = build(m + 1, e, s);

    return update(u);

}

node *mutate(node *u, int k, int v){
    u = clone(u);

    if (k <= size(u->l))
        u->l = mutate(u->l, k, v);
    else if (size(u->l) + 1 == k)
        u->idx = v;
    else
        u->r = mutate(u->r, k - size(u->l) - 1, v);

    return update(u);
}

void dfs( node* u){
    if (!u) return;

    dfs(u->l);

    cout << dna[ u->idx ] << endl;
    for (int i = 0; i < 4; ++i)
        cout << u->count[i] << " ";
    cout << endl;

    dfs(u->r);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 4; ++i)
        dnaid[ dna[i] ] = i;

    int n; cin >> n;

    vector<node*> version(1);

    for (int i = 1; i <= n; ++i){
        string s; cin >> s;
        version.push_back( build(0, s.length() - 1, s ) );
    }

    int q; cin >> q;

    while (q--){
        string comm;
        cin >> comm;

        if (comm == "MUTATE"){
            int id, k; char m;
            cin >> id >> k >> m;

            version[id] = mutate( version[id], k, num(m) );
        }
        else if (comm == "CROSS"){
            int id1, id2, k1, k2;
            cin >> id1 >> id2 >> k1 >> k2;

            auto dna1 = split( version[id1], k1 );
            auto dna2 = split( version[id2], k2 );

            node* dna3 = merge( dna1.first, dna2.second );
            node* dna4 = merge( dna2.first, dna1.second );

            version.push_back( dna3 );
            version.push_back( dna4 );
        }
        else{
            int id, k1, k2;
            cin >> id >> k1 >> k2;

            node *u = split(version[id], k2).first;
                  u = split(u, k1 - 1).second;

            for (int i = 0; i < 4; ++i)
                cout << u->count[i] << " \n"[i + 1 == 4];
        }
    }

    return 0;
}
