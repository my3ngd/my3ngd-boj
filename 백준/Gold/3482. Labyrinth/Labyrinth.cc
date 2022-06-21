#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int res;

int dfs(const vector<string>& a, int x, int y, int k)
{
    int aa = 0, bb = 0, r = k + (k&1?-1:1);
    for (int dir = 0; dir < 4; dir++)
    {
        if (dir != r)
        {
            int nx = x + dx[dir], ny = y + dy[dir];
            if (a[nx][ny] == '#') continue;
            int c = dfs(a, nx, ny, dir) + 1;
            if (aa < c) bb = aa, aa = c;
            else if (bb < c) bb = c;
        }
        res = max(res, aa + bb);
    }
    return aa;
}

void DFS(const vector<string>& a, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == '.')
            {
                dfs(a, i, j, 4);
                return ;
            }
    assert(false);
}

void sol(void)
{
    int n, m; cin >> m >> n;
    vector<string> a(n);
    for (auto& l: a) cin >> l;
    DFS(a, n, m);
    cout << "Maximum rope length is " << res << ".\n";
    return ;
}


int main(int argc, char const *argv[])
{
    cin.tie(NULL)->sync_with_stdio(false);
    int t; cin >> t;
    for (; t--; res = 0)
        sol();
    return 0;
}
