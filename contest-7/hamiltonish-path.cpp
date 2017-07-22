#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

int main(){

    int n, m;
    cin >> n >> m;

    vector<bool> seen(n);
    vector<vi> adj(n);

    int x, y;

    for (int i = 0; i < m; ++i){
        cin >> x >> y;
        x--; y--;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    seen[x] = seen[y] = true;

    vi path;
    bool change = true;

    while (change){
        path.push_back( x );
        change = false;

        for (auto u : adj[x])
            if (!seen[u]){
                seen[u] = true;
                x = u;
                change = true;
                break;
            }
    }

    change = true;

    reverse(path.begin(), path.end());

    while (change){
        path.push_back(y);
        change = false;

        for (auto u : adj[y])
            if (!seen[u]){
                seen[u] = change = true;
                y = u;
                break;
            }
    }

    cout << path.size() << endl;

    for (auto u : path)
        cout << u + 1 << " ";

    cout << endl;

}