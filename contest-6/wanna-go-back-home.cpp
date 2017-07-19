#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10; 

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s; cin >> s;
    string dir = "SNEW";
    vector<bool> present(4);

    for (int i = 0; i < 4; ++i)
        present[i] = s.find( dir[i] ) != s.npos;

    cout << (present[0] == present[1] && present[2] == present[3] ? "Yes" : "No") << endl;

    return 0;
}