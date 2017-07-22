#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
const int oo = 0x3f3f3f3f;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    while (n--){
        string s; cin >> s;
        int x = s[0] - 'a';
        int y = s[1] - '1';

        int ans = 0;

        for (int dx = -2; dx <= 2; ++dx){
            for (int dy = -2; dy <= 2; ++dy){
                if ((abs(dx) | abs(dy)) != 3) continue;
                int nx = x + dx;
                int ny = y + dy;
                if (0 <= nx && nx < 8 && 0 <= ny && ny < 8)
                    ++ans;
            }
        }

        cout << ans << endl;

    }

    return 0;
}
