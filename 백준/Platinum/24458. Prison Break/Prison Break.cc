#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ff first
#define ss second
typedef pair<ll, ll> pos;
typedef pair<pos, pos> line;
pos  operator+(const pos& p, const pos& q){ return pos(p.ff + q.ff, p.ss + q.ss); }
pos  operator-(const pos& p, const pos& q){ return pos(p.ff - q.ff, p.ss - q.ss); }
pos& operator-(pos& p){ p.ff *= -1; p.ss *= -1; return p; }
pos& operator+=(pos& p, const pos& q){ return p = p + q; }
pos& operator-=(pos& p, const pos& q){ return p = p - q; }
ll operator*(const pos& p, const pos& q){ return p.ff*q.ss - p.ss*q.ff; }
template<typename T> ostream& operator<<(ostream& os, const pair<T, T>& p) { return os << p.ff << ' ' << p.ss; }
template<typename T> istream& operator>>(istream& is, pair<T, T>& p) { return is >> p.ff >> p.ss; }

inline ll ccw(const pos& p, const pos& q) { return (p.ff*q.ss) - (p.ss*q.ff); }
inline ll ccw(const pos& p, const pos& q, const pos& r) { return (p.ff-q.ff)*(p.ss-r.ss) - (p.ss-q.ss)*(p.ff-r.ff); }
inline int _ccw(const pos& p, const pos& q, const pos& r) { ll CCW = ccw(p, q, r); return (CCW?CCW/abs(CCW):0);}
inline int _ccw(const pos& p, const pos& q) { ll CCW = ccw(p, q); return (CCW?CCW/abs(CCW):0);}
inline ll dist(const pos& p, const pos& q) { return (p.ff-q.ff)*(p.ff-q.ff)+(p.ss-q.ss)*(p.ss-q.ss); }

void get_convex_hull(vector<pos>& arr, bool opt = false)
{
    swap(arr[0], *min_element(arr.begin(), arr.end()));
    sort(arr.begin()+1, arr.end(), [&](const pos& p, const pos& q)
    {
        ll cw = ccw(arr[0], p, q);
        return (cw ? cw > 0 : dist(arr[0], p) < dist(arr[0], q));
    });

    vector<pos> hull;
    for (auto& x : arr)
    {
        while ( opt && hull.size() > 1 && ccw(hull[hull.size()-2], hull.back(), x) <  0)  hull.pop_back();
        while (!opt && hull.size() > 1 && ccw(hull[hull.size()-2], hull.back(), x) <= 0)  hull.pop_back();
        hull.push_back(x);
    }

    int idx = 0;
    for (int i = 0; opt && i < arr.size(); i++)
        if (arr[i] == hull.back())
            idx = i;
    for (int i = arr.size()-1; opt && ccw(hull.front(), hull.back(), arr[i]) == 0; i--)
        if (hull.back() != arr[i] && ccw(hull.front(), hull.back(), arr[i]) == 0)
            hull.push_back(arr[i]);

    arr = hull;
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    set<line> lset;
    ll res = 0;
    int n, m;

    cin >> n;
    vector<pos> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    get_convex_hull(a);
    for (int i = 0; i < n; i++) lset.insert({a[i], a[(i+1)%n]});

    cin >> m;
    vector<pos> b = a;

    for (int i = 0; i < m; i++)
    {
        pos p; cin >> p;
        b.push_back(p);
    }

    get_convex_hull(b, true);
    m = b.size();

    for (int i = 0; i < m; i++)
    {
        line lb = line(b[i], b[(i+1)%m]);
        if (lset.find(lb) != lset.end()) res++;
    }

    cout << res << endl;
    return 0;
}
