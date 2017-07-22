#include <bits/stdc++.h>

using namespace std;

int main(){
    int n; cin >> n;

    int mode = 0, answer = 1;
    int v; cin >> v;

    for (int i = 1; i < n; ++i){
        int c; cin >> c;

        int nm;

        if (c == v) nm = mode;
        else nm = c > v ? +1 : -1;

        if (mode != nm){
            if (mode == 0) mode = nm;
            else{
                answer++;
                mode = 0;
            }
        }

        v = c;
    }

    cout << answer << endl;
}