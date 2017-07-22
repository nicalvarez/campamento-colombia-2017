#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl << flush;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;

namespace FFT
{
    int POW2 = 131072;
    int MAXN = 131072 + 10;
    const long double PI = 2 * acos(0.0L);

    typedef complex<double> base;

    base fa[2097152 + 10],fb[2097152 + 10];

    void fft(base *a, bool invert)
    {
        int n = POW2;
        for ( int i = 1 , j = 0 ; i < n; ++i)
        {
            int bit = n >> 1;
            for ( ; j >= bit ; bit >>= 1 )
                j -= bit ;
            j += bit;
            if ( i < j ) swap ( a[i] , a[j] );
        }
        for ( int len = 2 ; len <= n ; len <<= 1 )
        {
            double ang = 2 * PI / len * ( invert ? -1:1);
            base wlen ( cos ( ang ) , sin ( ang ) );
            for ( int i = 0 ; i < n ; i += len )
            {
                base w ( 1 , 0 ) ;
                for ( int j = 0 ; j < len / 2 ; ++j )
                {
                    base u = a [i+j],v = a[i+j+len / 2 ] * w ;
                    a [ i + j ] = u + v ;
                    a [ i + j + len / 2 ] = u - v ;
                    w = w*wlen ;
                }
            }
        }
        if (invert)
        {
            for ( int i = 0 ; i < n ; ++i )
                a[i]/=n;
        }
    }
    void multiply(int* a, int* b, int *c, int pow2)
    {
        POW2 = pow2;
        MAXN = pow2;
        memset(fa,0,sizeof fa);
        memset(fb,0,sizeof fb);

        for(int i = 0; i < MAXN; i++)
        {
            fa[i] = a[i];
            fb[i] = b[i];
        }

        fft (fa, false) ,  fft (fb, false);

        for ( int i = 0 ; i < MAXN; ++i )
            fa[i] = fa[i]*fb[i] ;

        fft (fa, true);

        for ( int i = 0 ; i < MAXN; ++ i )
            c[i] = int(fa[i].real() + 0.5);
    }
}

int a[2097152 + 10];
int b[2097152 + 10];

const int MAXN = 500000;

pii st[MAXN << 2];

void build(int p, int l, int r){
    if (l == r) st[p] = MP(b[l], -l);
    else{
        int mid = (l + r) >> 1;
        int le = p << 1;
        int ri = le | 1;
        build(le, l, mid);
        build(ri, mid + 1, r);
        st[p] = max(st[le], st[ri]);
    }
}

pii query(int p, int l, int r, int x, int y){
    if (x <= l && r <= y) return st[p];
    int mid = (l + r) >> 1;
    int le = p << 1;
    int ri = le | 1;
    if (y <= mid) return query(le, l, mid, x, y);
    if (mid + 1 <= x) return query(ri, mid + 1, r, x, y);
    return max(query(le, l, mid, x, y), query(ri, mid + 1, r, x, y));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 1; i * i <= MAXN; ++i){
        a[i * i]++;
        for (int j = i * i + i; j <= MAXN; j += i)
            a[j] += 2;
    }

    int64 c = 1;
    while (c <= MAXN) c *= 2;
    c *= 2;

    FFT::multiply(a, a, b, c);

    int q; cin >> q;
    build(1, 0, MAXN);
    while (q--){
        int l, r; cin >> l >> r;
        auto ans = query(1, 0, MAXN, l, r);
        cout << -ans.second << " " << ans.first << endl;
    }

    return 0;
}