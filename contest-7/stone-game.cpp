#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    int v = 0;
    cin >> s;
    for (auto c : s){
        v += (c - '0');
        v %= 3;
    }

    if (v == 0) cout << 2 << endl;
    else{
        cout << 1 << endl;
        cout << v << endl;
    }

    return 0;
}