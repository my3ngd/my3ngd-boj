#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
using ll = long long;
using ld = long double;
using pos = pair<ll, ll>;
const ll INF = LLONG_MAX;

pos operator+(pos p, pos q) { return pos(p.ff+q.ff, p.ss+q.ss); }
pos operator-(pos p, pos q) { return pos(p.ff-q.ff, p.ss-q.ss); }
pos operator*(pos p, ll& f) { return pos(p.ff*f, p.ss*f); }
pos operator/(pos p, ll& f) { return pos(p.ff/f, p.ss/f); }
ll  operator*(pos p, pos q) { return p.ff*q.ff + p.ss*q.ss; }
ll  operator/(pos p, pos q) { return p.ff*q.ss - p.ss*q.ff; }
pos& operator+=(pos& p, pos q) { return p = p + q; }
pos& operator-=(pos& p, pos q) { return p = p - q; }
pos& operator*=(pos& p, ll& f) { return p = p * f; }
pos& operator/=(pos& p, ll& f) { return p = p / f; }
ll   dist(pos p, pos q) { pos r = p-q; return r*r; }
template <typename T> istream& operator>>(istream& is, pair<T,T>& p) { return is >> p.ff >> p.ss; }
template <typename T> ostream& operator<<(ostream& os, pair<T,T>& p) { return os << p.ff << " " << p.ss; }

struct node
{
    pos p, st, en;
    bool dir, exist;  // 0: lr, 1: ud
    node() = default;
    node(pos p, pos st, pos en, bool dir) : p(p), st(st), en(en), dir(dir) {}
};


struct kd_tree
{
    vector<node> tree;
    vector<pos> arr;
    ll res;

    kd_tree(vector<pos>& points): arr(points)
    {
        int n = 1;
        for (; n < points.size(); n <<= 1);
        tree.resize(n<<1);
        init(0, arr.size()-1, 1);
    }

    bool comp_horizontal(pos p, pos q) { return p < q; }
    bool comp_vertical(pos p, pos q) { return pos(p.ss, p.ff) < pos(q.ss, q.ff); }
    ll sq(ll x) { return x*x; }

    void init(int s, int e, int idx)
    {
        ll min_x = INF, min_y = INF, max_x = -INF, max_y = -INF;
        for (int i = s; i <= e; i++)
            min_x = min(min_x, arr[i].ff),
            min_y = min(min_y, arr[i].ss),
            max_x = max(max_x, arr[i].ff),
            max_y = max(max_y, arr[i].ss);
        tree[idx].dir = (max_x - min_x < max_y - min_y);  // if leftside is smaller -> vertically oriented
        sort(arr.begin()+s, arr.begin()+e+1, [&](pos a, pos b)
        {
            return tree[idx].dir ? comp_vertical(a, b) : comp_horizontal(a, b);
        });
        int m = s + e >> 1;
        tree[idx] = node(arr[m], pos(min_x, min_y), pos(max_x, max_y), tree[idx].dir);
        tree[idx].exist = true;
        if (s < m) init(s, m-1, idx<<1|0);
        if (m < e) init(m+1, e, idx<<1|1);
        return ;
    }

    void nearest_query(int idx, pos p)
    {
        if (p != tree[idx].p)
            res = min(res, dist(p, tree[idx].p));
        if (tree[idx].dir)  // vertical case
        {
            if (!comp_vertical(tree[idx].p, p))
            {
                if (tree[idx<<1|0].exist)
                    nearest_query(idx<<1|0, p);
                if (tree[idx<<1|1].exist && sq(tree[idx<<1|1].st.ss - p.ss) < res)
                    nearest_query(idx<<1|1, p);
            }
            else
            {
                if (tree[idx<<1|1].exist)
                    nearest_query(idx<<1|1, p);
                if (tree[idx<<1|0].exist && sq(tree[idx<<1|0].en.ss - p.ss) < res)
                    nearest_query(idx<<1|0, p);
            }
        }
        else
        {
            if (!comp_horizontal(tree[idx].p, p))
            {
                if (tree[idx<<1|0].exist)
                    nearest_query(idx<<1|0, p);
                if (tree[idx<<1|1].exist && sq(tree[idx<<1|1].st.ff - p.ff) < res)
                    nearest_query(idx<<1|1, p);
            }
            else
            {
                if (tree[idx<<1|1].exist)
                    nearest_query(idx<<1|1, p);
                if (tree[idx<<1|0].exist && sq(tree[idx<<1|0].en.ff - p.ff) < res)
                    nearest_query(idx<<1|0, p);
            }
        }
    }
};


void run(void)
{
    int n; cin >> n;
    vector<pos> arr(n);
    for (auto& p: arr) cin >> p;
    kd_tree kd(arr);
    for (auto& p: arr)
    {
        kd.res = INF;
        kd.nearest_query(1, p);
        cout << kd.res << "\n";
    }
}


int main(int argc, char const *argv[])
{
    cin.tie(NULL)->sync_with_stdio(false);
    int T; cin >> T;
    while (T--) run();
    return 0;
}
