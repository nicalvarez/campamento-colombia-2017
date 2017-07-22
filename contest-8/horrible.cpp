#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define DB(x) cout << #x << "=" << x << endl

const int MAXN = (int)1e5 + 10;

typedef long long int64;

int64 ST[MAXN << 2];
int64 LZ[MAXN << 2];

void down_lazy(int p, int left, int right, int b, int mid, int e){
    ST[left] += LZ[p] * (mid - b + 1);
    LZ[left] += LZ[p];
    ST[right] += LZ[p] * (e - (mid + 1) + 1);
    LZ[right] += LZ[p];
    LZ[p] = 0;
}

void update(int p, int b, int e, int x, int y, int64 v){
    if (x <= b && e <= y){
        ST[p] += v * (e - b + 1);
        LZ[p] += v;
    }
    else{
        int mid = (b + e) >> 1;
        int left = p << 1;
        int right = left | 1;

        if (LZ[p]) down_lazy(p, left, right, b, mid, e);

        if (y <= mid) update(left, b, mid, x, y, v);
        else if (mid + 1 <= x) update(right, mid + 1, e, x, y, v);
        else{
            update(left,b,mid, x, y, v);
            update(right, mid + 1, e, x, y, v);
        }
        ST[p] = ST[left] + ST[right];
    }
}

int64 query(int p, int b, int e, int x, int y){
    if (x <= b && e <= y){
        return ST[p];
    }
    else{
        int mid = (b + e) >> 1;
        int left = p << 1;
        int right = left | 1;
        if (LZ[p]) down_lazy(p, left, right, b, mid, e);
        if (y <= mid) return query(left, b, mid, x, y);
        else if (mid + 1 <= x) return query(right, mid + 1, e,x,y);
        else return query(left, b, mid, x, y) + query(right, mid + 1, e,x,y);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, q;
        cin >> n >> q;
        memset(ST, 0, sizeof ST);
        memset(LZ, 0, sizeof LZ);
        while (q--){
            int m; cin >> m;
            if (m){
                int u, v;
                cin >> u >> v;
                cout << query(1,0,n-1,u-1,v-1) << endl;
            }
            else{
                int u, v;
                int64 k;
                cin >> u >> v >> k;

                update(1, 0, n - 1, u - 1, v - 1, k);
            }
        }
    }

    return 0;
}