#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pos = pair<ll, ll>;
#define ff first
#define ss second
#define endl "\n"
#define nxt(i, n) (((i)+1) % (n))
#define pre(i, n) (((i)+(n)-1) % (n))
#define mod(a, n) (((a) + (n)) % (n))
pos  operator+(pos& a, pos& b) { return {a.ff + b.ff, a.ss + b.ss}; }
pos  operator-(pos& a, pos& b) { return {a.ff - b.ff, a.ss - b.ss}; }
pos  operator*(pos& a, ll& b) { return {a.ff * b, a.ss * b}; }
pos  operator/(pos& a, ll& b) { return {a.ff / b, a.ss / b}; }
pos& operator+=(pos& a, pos& b) { return a = a + b; }
pos& operator-=(pos& a, pos& b) { return a = a - b; }
ll   operator*(pos& a, pos& b) { return a.ff * b.ff + a.ss * b.ss; }
ll   operator/(pos& a, pos& b) { return a.ff * b.ss - a.ss * b.ff; }
pos  operator*(pos& a, ll k) { return {a.ff * k, a.ss * k}; }
pos  operator/(pos& a, ll k) { return {a.ff / k, a.ss / k}; }
pos& operator-(pos& a) { return a = {-a.ff, -a.ss}; }
template <typename T> istream& operator>>(istream& is, pair<T, T>& p) { return is >> p.ff >> p.ss; }
template <typename T> ostream& operator<<(ostream& os, pair<T, T>& p) { return os << p.ff << ' ' << p.ss; }
ll ccw(pos a, pos b) { return a.ff * b.ss - a.ss * b.ff; }
ll ccw(pos a, pos b, pos c) { return ccw(b-a, c-a); }
int _ccw(pos p, pos q, pos r) { ll CCW = ccw(p, q, r); return (CCW ? (CCW > 0 ? 1 : -1) : 0); }
ll dist(pos a, pos b) { pos c = a - b; return c * c; }


int slice_hull(vector<pos>& hull, int i, int j)
{
    int ni = nxt(i, hull.size()),
        nj = nxt(j, hull.size()),
        pi = pre(i, hull.size()),
        pj = pre(j, hull.size());
    pos a = hull[ni] - hull[i],
        b = hull[pj] - hull[j],
        x = hull[pi] - hull[i],
        y = hull[nj] - hull[j];
    if (a / b > 0)  return  1;
    if (x / y < 0)  return -1;
    return 0;
}


pair<int, int> get_range(vector<pos>& hull, const vector<pair<int, int>>& near, int cur)
{
    pair<int, int> res;
    int n = hull.size();
    int S = (near[cur].ss - cur + n)%n + 1, E = n - (cur - near[cur].ff + n)%n - 1, M;

    // find lower bound of range
    while (S < E)
    {
        M = S + E >> 1;
        if (slice_hull(hull, cur, mod(cur+M, n)) > -1) E = M;
        else S = M + 1;
    }
    res.ff = S;
    // find upper bound of range
    S = (near[cur].ss - cur + n)%n + 1, E = n - (cur - near[cur].ff + n)%n - 1;
    while (S < E)
    {
        M = S + E + 1 >> 1;
        if (slice_hull(hull, cur, mod(cur+M, n)) > 0) E = M - 1;
        else S = M;
    }
    res.ss = S;
    return res;
}


ll run(void)
{
    int n; cin >> n;
    vector<pos> hull(n);
    for (auto& p: hull) cin >> p;
    reverse(hull.begin(), hull.end());
    vector<int> corner;
    for (int i = 0; i < hull.size(); i++)
        if (_ccw(hull[pre(i, n)], hull[i], hull[nxt(i, n)]) != 0)
            corner.push_back(i);
    // nearest corner
    vector<pair<int, int>> near(hull.size());
    for (int i = 0, ni, j = 0; i < near.size(); i++)
    {
        ni = mod(i+corner[0], n);
        near[ni].ff = corner[pre(j, corner.size())];  // left nearest corner
        near[ni].ss = corner[j];  // right nearest corner
        if (ni == corner[j])
        {
            near[ni].ss = corner[nxt(j, corner.size())];
            j++;
        }
    }
    if (_ccw(hull.back(), hull[0], hull[1]) == 0)
        near[0].ss = near[n-1].ss;

    ll res = 0;
    if (corner.size() == 3)
    {
        int a = corner[0], b = corner[1], c = corner[2];
        ll acnt = (c-b-1+n)%n, bcnt = (a-c-1+n)%n, ccnt = (b-a-1+n)%n;
        res += acnt + bcnt + ccnt;
        res += (acnt+2) * (acnt+1) >> 1;
        res += (bcnt+2) * (bcnt+1) >> 1;
        res += (ccnt+2) * (ccnt+1) >> 1;
        return res;
    }

    // normal counting
    for (int i = 0; i < n; i++)
    {
        pair<int, int> range = get_range(hull, near, i);
        res += range.ss - range.ff + 1;
    }
    res >>= 1;
    // "neighbor" edge cases
    for (auto& p: corner)
    {
        int cur_idx = p;
        int pre_idx = near[cur_idx].ff;
        if (slice_hull(hull, cur_idx, pre_idx) == 0)
        {
            int k = (cur_idx - pre_idx + n) % n + 1;
            res += k * (k - 1) >> 1;
        }
    }
    return res;
}


int main(int argc, char const *argv[])
{
    cin.tie(0)->sync_with_stdio(false);
    int T; cin >> T;
    while (T--)
        cout << run() << endl;
    return 0;
}
