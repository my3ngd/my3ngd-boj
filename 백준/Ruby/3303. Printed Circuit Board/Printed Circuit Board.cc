#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pos = pair<ll, ll>;
#define ff first
#define ss second
#define pre(i, n) (((i)+(n)-1)%(n))
#define nxt(i, n) (((i)+1)%(n))
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
istream& operator>>(istream& is, pos& p) { return is >> p.ff >> p.ss; }
ostream& operator<<(ostream& os, const pos& p) { return os << p.ff << ' ' << p.ss; }
ll ccw(pos a, pos b) { return a.ff * b.ss - a.ss * b.ff; }
ll ccw(pos a, pos b, pos c) { return ccw(b-a, c-a); }
int _ccw(pos p, pos q) { ll CCW = ccw(p, q); return (CCW > 0) - (CCW < 0); }
int _ccw(pos p, pos q, pos r) { ll CCW = ccw(p, q, r); return (CCW > 0) - (CCW < 0); }
ll dist(pos a, pos b = {0, 0}) { pos c = a - b; return c.ff * c.ff + c.ss * c.ss; }

namespace std
{
    template<typename T>
    struct hash<pair<T, T>>
    {
        size_t operator()(const pair<T, T>& p) const
        {
            return hash<ll>()(p.ff) * 1000000LL +  hash<ll>()(p.ss);
        }
    };
} // for using unordered_map


int handle_small_case(int n, const vector<pos>& a, unordered_map<pos, int>& mp)
{
    if (n == 1)
    {
        cout << "1\n1\n";
        return 1;
    }
    else if (n == 2)
    {
        if (_ccw(a[0], a[1]) == 0)
        {
            cout << "1\n";
            if (dist(a[0]) < dist(a[1]))
                cout << mp[a[0]] << "\n";
            else
                cout << mp[a[1]] << "\n";
        }
        else
            cout << "2\n1 2\n";
        return 1;
    }
    return 0;
}


int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n; cin >> n;
    vector<pos> a(n);
    unordered_map<pos, int> mp;
    cin >> a[0];    mp[a[0]] = 1;
    int lo_idx = 0, hi_idx = 0;
    pos lo = a[0], hi = a[0];
    bool flag = false;
    for (int i = 1; i < n; i++)
    {
        cin >> a[i];
        mp[a[i]] = i + 1;
        if (_ccw(a[i], lo) > 0 || (_ccw(a[i], lo) == 0 && dist(a[i]) < dist(lo)))
        {
            lo = a[i];
            lo_idx = i;
        }
        if (_ccw(a[i], hi) < 0 || (_ccw(a[i], hi) == 0 && dist(a[i]) < dist(hi)))
        {
            hi = a[i];
            hi_idx = i;
        }
        if (!flag && i > 1 && _ccw(a[i-2], a[i-1], a[i]) != 0)
            flag = true;
    }

    if (handle_small_case(n, a, mp))
        return 0;

    if (!flag)
    {
        if (_ccw(a[0], a[1]) == 0)
            cout << "1\n" << mp[a[lo_idx]] << "\n";
        else
        {
            cout << n << "\n";
            for (int i = 0; i < n; i++)
                cout << i+1 << " ";
            cout << "\n";
        }
    }

    if (_ccw(a[pre(hi_idx, n)], hi, a[nxt(hi_idx, n)]) > 0)
    {
        reverse(a.begin(), a.end());  // now cw direction
        lo_idx = n - 1 - lo_idx;
        hi_idx = n - 1 - hi_idx;
    }

    vector<pos> res;
    res.reserve(n+1);
    res.push_back(lo);
    for (int i = nxt(lo_idx, n); i != hi_idx; i = nxt(i, n))
    {
        const pos& p = a[i];

        if (_ccw(res.back(), p) > 0)
        {
            res.push_back(p);
            continue;
        }
        else if (_ccw(res.back(), p) == 0)
        {
            if (dist(res.back()) > dist(p))
                res.back() = p;
            continue;
        }
        if (_ccw(res[res.size()-2], res[res.size()-1], p) < 0)
            continue;
        assert(res.size() >= 2);
        while (dist(p) < dist(res.back()) && (_ccw(res.back(), p) < 0 || (_ccw(res.back(), p) == 0 && dist(res.back()) > dist(p))))
            res.pop_back();
        if (_ccw(res.back(), p) > 0 || (_ccw(res.back(), p) <= 0 && dist(res.back()) > dist(p)))
            res.push_back(p);
    }
    res.push_back(hi);

    vector<int> print(res.size());
    for (int i = 0; i < res.size(); i++)
        print[i] = mp[res[i]];
    sort(print.begin(), print.end());
    cout << print.size() << "\n";
    for (auto& p: print)
        cout << p << " ";
    cout << "\n";

    return 0;
}
