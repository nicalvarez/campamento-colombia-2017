#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

const int maxn = 110;

vi ady[maxn];
int color[maxn];
int lst[maxn];

int main()
{
    int n; cin >> n;
    int tot = 0;
    for (int i = 1; i <= n; ++i){
        while (true){
            int v; cin >> v;
            if (!v) break;
            ady[i].push_back(v);
        }
        if (ady[i].size() == 0){
            cout << 0 << endl;
            exit(0);
        }
    }
    for (int i = 1; i <= n; ++i){
        bool found = false;
        for (int j = 0; j < ady[i].size() && !found; ++j){
            int neig = ady[i][j];
            if (color[neig]) found = true;
        }
        if (!found){
            lst[tot++] = i;
            color[i] = 1;
        }
    }
    cout << tot << endl;
    for (int i = 0; i < tot; ++i)
        cout << lst[i] << " \n"[i + 1 == tot];
}