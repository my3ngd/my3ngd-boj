#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pos = pair<ll, ll>;
#define ff first
#define ss second
#define endl '\n'
#define pre(i, n) (((i)+(n)-1)%(n))
#define nxt(i, n) (((i)+1)%(n))


vector<int> dfs(const vector<vector<int>>& tree, vector<int>& rank, int cur, int par = -1)
{
    if (tree[cur].size() == 1 && tree[cur][0] == par)
    {
        rank[cur] = 1;
        return {1};
    }
    multiset<int> s;
    for (int i = 0; i < tree[cur].size(); i++)
    {
        if (tree[cur][i] == par) continue;
        vector<int> chs = dfs(tree, rank, tree[cur][i], cur);
        for (int j = 0; j < chs.size(); j++)
            s.insert(chs[j]);
    }
    int pv = 0;
    for (auto& x: s)
        if (s.count(x) > 1)
            pv = max(pv, x);
    pv++;
    while (s.count(pv))
        pv++;
    rank[cur] = pv;
    vector<int> res;
    res.push_back(pv);
    for (auto& x: s)
    {
        if (x > pv)
        {
            res.push_back(x);
            pv++;
        }
    }
    return res;
}


int main(int argc, char const *argv[])
{
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<int>> tree(n+1);
    vector<int> rank(n+1);
    for (int i = 0; i < n-1; i++)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(tree, rank, 1);
    int res = -1;
    for (int i = 1; i < rank.size(); i++)
    {
        // cout << "/\t" << rank[i] << endl;
        res = max(res, rank[i]);
    }
    cout << res-1 << endl;

    return 0;
}
