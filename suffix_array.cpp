#include <bits/stdc++.h>
using namespace std;

vector<int> suffix_array(const string &s) {
    int n = s.size();
    vector<int> p(n), r(n);
    vector<long long> r2(n); 

    for (int i = 0; i < n; i++) {
        p[i] = i;
        r[i] = s[i];
    }
    for (int len = 1; len < n; len *= 2) {
        for (int i = 0; i < n; i++) r2[i] = ( (long long) r[i] << 32) + (i+len < n ? r[i+len] : -1);
        sort(p.begin(), p.end(), [&](int i, int j){ 
            return r2[i] < r2[j];
        });
        for (int i = 0; i < n; i++) {
            if (i > 0 && r2[p[i]] == r2[p[i-1]]) r[p[i]] = r[p[i-1]];
            else r[p[i]] = i;
        }
    }
    return p;
}

vector<int> lcp_array(const vector<int> &sa, const string &s) {
    int n = s.size();
    vector<int> rank(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;

    vector<int> ans(n);
    for (int i = 0, l = 0; i < n; i++) if (rank[i] > 0) {
        int j = sa[rank[i]-1];
        while (s[i+l] == s[j+l]) l++;
        ans[rank[i]] = l > 0 ? l-- : l;
    }
    ans[0] = -1;
    return ans;
}

int main() {
    string s = "banana";
    s += char(0);

    auto sa = suffix_array(s);
    for (auto x : sa) cerr << x << ' '; cerr << endl;

    auto lcp = lcp_array(sa,s);
    for (auto x : lcp) cerr << x << ' '; cerr << endl;

    return 0;
}

