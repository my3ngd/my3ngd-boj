#include <bits/stdc++.h>
using ll = long long;
using namespace std;


int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
// dir: [d, r, u, l]


int trip(const vector<string>& mp, int x, int y, int dir)
{
    int n = mp.size();
    int m = mp[0].size();
    int cnt = 0;
    for (; 0 <= x && x < n && 0 <= y && y < m; cnt++)
    {
        // cout << x << " " << y << " | dir = " << dir << " ";
        if (mp[x][y] == '/')
        {
            if      (dir == 0) dir = 3;
            else if (dir == 1) dir = 2;
            else if (dir == 2) dir = 1;
            else if (dir == 3) dir = 0;
            else assert(false);
            x += dx[dir];
            y += dy[dir];
            // cout << " -> " << x << " " << y << "\n";
        }
        else
        {
            if      (dir == 0) dir = 1;
            else if (dir == 1) dir = 0;
            else if (dir == 2) dir = 3;
            else if (dir == 3) dir = 2;
            else assert(false);
            x += dx[dir];
            y += dy[dir];
            // cout << " -> " << x << " " << y << "\n";
        }
    }
    return cnt;
}



int main(int argc, char const *argv[])
{
    cin.tie(0)->sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<string> mp(n);
    for (auto& l: mp) cin >> l;
    // trip(mp, 0, 0, 0);
    int ans = 0;
    for (int i = 0; i < n; i++) ans = max(ans, trip(mp, i, 0, 1));
    for (int i = 0; i < n; i++) ans = max(ans, trip(mp, i, m-1, 3));
    for (int i = 0; i < m; i++) ans = max(ans, trip(mp, 0, i, 0));
    for (int i = 0; i < m; i++) ans = max(ans, trip(mp, n-1, i, 2));
    cout << ans << '\n';
    return 0;
}
