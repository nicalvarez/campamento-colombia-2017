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
const int MAXN = (int)1e5 + 10;

vector<int> lst;

void print(int b, int e){
    cout << e - b + 1 << endl;
    for (int i = b; i <= e; ++i)
        cout << lst[i] << endl;
    exit(0);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<int> V(n);

    int sum = 0;
    lst.push_back(0);
    for (int i = 1; i <= n; ++i){
        int v; cin >> v;
        lst.push_back(v);
        sum = (sum + v) % n;

        if (sum == 0) print(1, i);
        if (!V[sum]) V[sum] = i;
        else print(V[sum] + 1, i);
    }

    return 0;
}
