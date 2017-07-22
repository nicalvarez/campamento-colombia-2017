#include <bits/stdc++.h>
using namespace std;

vector<int> suffix_array(const string &s) {
    int n = s.size();
    vector<int> sa(n), rank(n);
    vector<long long> rank2(n); 

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }
    for (int len = 1; len < n; len *= 2) {
        for (int i = 0; i < n; i++) rank2[i] = ( (long long) rank[i] << 32) + (i+len < n ? rank[i+len] : -1);
        sort(sa.begin(), sa.end(), [&](int i, int j){ 
            return rank2[i] < rank2[j];
        });
        for (int i = 0; i < n; i++) {
            if (i > 0 && rank2[sa[i]] == rank2[sa[i-1]]) rank[sa[i]] = rank[sa[i-1]];
            else rank[sa[i]] = i;
        }
    }
    return sa;
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

