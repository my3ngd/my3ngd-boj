#include <bits/stdc++.h>
using namespace std;
#define nxt(i, n) (((i)+1)%(n))
#define pre(i, n) (((i)-1+(n))%(n))
#define ff first
#define ss second
using ll = long long;

const ll INF = 1000000000000LL;

struct pos
{
    ll x, y;
    pos(ll x = 0, ll y = 0): x(x), y(y) {}
    pos  operator+ (const pos p) const { return pos(x + p.x, y + p.y); }
    pos  operator- (const pos p) const { return pos(x - p.x, y - p.y); }
    pos  operator* (const ll  k) const { return pos(x * k, y * k); }
    pos  operator/ (const ll  k) const { return pos(x / k, y / k); }
    ll   operator* (const pos p) const { return x * p.x + y * p.y; }
    ll   operator/ (const pos p) const { return x * p.y - y * p.x; }
    pos& operator+=(const pos p) { return *this = *this + p; }
    pos& operator-=(const pos p) { return *this = *this - p; }
    pos& operator*=(const ll  k) { return *this = *this * k; }
    pos& operator/=(const ll  k) { return *this = *this / k; }
    bool operator==(const pos p) const { return x == p.x && y == p.y; }
    bool operator!=(const pos p) const { return !(*this == p); }
    bool operator< (const pos p) const { return x < p.x || (x == p.x && y < p.y); }
    bool operator<=(const pos p) const { return *this < p || *this == p; }
    bool operator> (const pos p) const { return p < *this; }
    bool operator>=(const pos p) const { return *this > p || *this == p; }
    friend istream& operator>>(istream& is, pos& p) { return is >> p.x >> p.y; }
    friend ostream& operator<<(ostream& os, const pos& p) { return os << p.x << ' ' << p.y; }

    pos rot(void) const { return pos(-y, x); }
};

// ------------------------------------------------------------------------------------------------

ll dist(const pos p, const pos q = pos()) { pos d = p - q; return d * d; }
ll ccw(const pos a, const pos b) { return a / b; }
ll ccw(const pos a, const pos b, const pos c) { return ccw(b-a, c-a); }
int _ccw(const pos a, const pos b) { ll CCW = ccw(a, b); return (CCW > 0) - (CCW < 0); }
int _ccw(const pos a, const pos b, const pos c) { return _ccw(b-a, c-a); }

// ------------------------------------------------------------------------------------------------

pair<ll, ll> operator*(pos a, pair<pos, ll> b) { return make_pair(a*b.ff, b.ss); }

/* 세 점 CCW이 음수인가? */
bool convex(pos a, pos b, pos c) { return ccw(b-a, c-b) < 0; }

/* 삼각형 내 점 판별 */
bool point_in_tri(pos x, pos a, pos b, pos c) { return convex(a, b, x) && convex(b, c, x) && convex(c, a, x); }

const ll base = 1LL<<32;
pair<ll, ll> mul(ll a, ll b)
{
    bool minus = a < 0;
    if (minus) a *= -1;
    pair<ll, ll> res((a/base)*b, (a%base)*b);
    res.ff += res.ss/base;
    res.ss %= base;
    if (minus)
        res.ff = -res.ff,
        res.ss = -res.ss;
    return res;
}

bool smaller(pair<ll, ll> a, pair<ll, ll> b)
{
    if (a.ss < 0)
    {
        a.ff = -a.ff;
        a.ss = -a.ss;
    }
    if (b.ss < 0)
    {
        b.ff = -b.ff;
        b.ss = -b.ss;
    }
    return mul(a.ff, b.ss) < mul(b.ff, a.ss);
}

bool better_p(pos i1, pos i2, pos best, pos cand)
{
    return  mul(ccw(i2-i1,best-i1) * abs(ccw(i2-i1,best-i1)), dist(cand-i1)) <
            mul(ccw(i2-i1,cand-i1) * abs(ccw(i2-i1,cand-i1)), dist(best-i1));
}

struct line
{
    pos norm;
    ll c;

    line() {}
    line(pos a, pos b)
    {
        this->norm = (b-a).rot();
        this->c = this->norm*a;
    }
};

bool parallel(line a, line b)
{
    return ccw(a.norm, b.norm) == 0;
}

pair<pos, ll> intersection(line a, line b)
{
    return make_pair((a.norm * b.c - b.norm * a.c).rot(), ccw(a.norm, b.norm));
}

const int MAX = 1000;

int n;
pos a[MAX];
bool b[MAX];

bool star(void)
{
    for (int i = 0; i < n; i++)
    {
        line l1(a[i], a[nxt(i, n)]);
        pos v = a[nxt(i, n)] - a[i];
        pair<ll, ll> low = make_pair(-INF, 1);
        pair<ll, ll> high = make_pair(INF, 1);;
        bool ok = true;
        for (int j=0; j<n; j++) if (i!=j)
        {
            line l2(a[j], a[nxt(j, n)]);
            if (parallel(l1, l2))
            {
                if (l2.norm * a[i] > l2.c)
                {
                    ok = false;
                    break;
                }
            }
            else
            {
                pair<ll, ll> tmp = v * intersection(l1, l2);
                if (ccw(l1.norm, l2.norm) > 0)
                {
                    if (smaller(low, tmp))
                        low = tmp;
                }
                else
                {
                    if (smaller(tmp, high))
                        high = tmp;
                }
            }
        }
        if (smaller(low,high) && ok)
            return true;
    }
    return false;
}

bool run(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
    {
        char c; cin >> c;
        b[i] = c == 'C';
    }

    bool all_black = true, all_white = true;
    for (int i = 0; i < n; i++)
    {
        all_black &=  b[i];
        all_white &= !b[i];
    }
    if (all_black) return false;
    if (all_white) return star();

    while (true)
    {
        if (n == 3) return false;
        int i1 = 0, i2 = 0, i3 = 0;
        for (i1 = 0; i1 < n; i1++)
        {
            i2 = nxt(i1, n);
            i3 = nxt(i2, n);
            if (b[i1] && b[i2] && convex(a[i1], a[i2], a[i3]))
                break;
        }
        if (i1 == n) break;

        int best = -1;
        for (int i = 0; i < n; i++)
            if (i != i1 && i != i2 && i != i3 && point_in_tri(a[i], a[i1], a[i2], a[i3]))
                if (best == -1 || better_p(a[i1], a[i2], a[best], a[i]))
                    best = i;

        if (best == -1)
        {
            for (int i = i2+1; i < n; i++)
            {
                a[i-1] = a[i];
                b[i-1] = b[i];
            }
            n--;
            continue;
        }

        int j1 = i2, j2 = best;
        if (j2 < j1) swap(j1, j2);

        bool all_black_le = true, all_black_ri = true;

        for (int i = 0; i < n; i++)
            if (!b[i])
            {
                if (i >= j1 && i < j2)
                    all_black_le = false;
                else
                    all_black_ri = false;
            }
        if (!all_black_le && !all_black_ri)
            return false;

        if (all_black_le)
        {
            for (int i = j2; i < n; i++)
            {
                a[i-(j2-j1-1)] = a[i];
                b[i-(j2-j1-1)] = b[i];
            }
            b[j1] = true;
            n -= (j2-j1-1);
        }
        else
        {
            for (int i = j1; i <= j2; i++)
            {
                a[i-j1] = a[i];
                b[i-j1] = b[i];
            }
            n = (j2-j1+1);
            b[n-1] = true;
        }

    }

    for (int i = 0; i < n; i++)
        if (b[i] && b[nxt(i, n)])
            return false;

    for (int i = 0, j, k, l; i < n; i++)
    {
        j = nxt(i, n);
        k = nxt(j, n);
        l = nxt(k, n);
        if (b[j] && convex(a[i], a[j], a[k]) == convex(a[j], a[k], a[l]))
            return false;
    }

    int i1 = 0;
    while (!b[i1]) i1++;
    int i2 = i1 + 1;
    while (i2 < n && !b[i2]) i2++;

    if (i2 == n)
    {
        line l1(a[i1], a[nxt(i1, n)]);
        pos v = a[nxt(i1, n)] - a[i1];
        pair<ll, ll> low = make_pair(-INF, 1);
        pair<ll, ll> high = make_pair(INF, 1);;
        for (int i = 0; i < n; i++)
        {
            if (i!=i1)
            {
                line l2(a[i], a[nxt(i, n)]);
                if (parallel(l1, l2))
                {
                    if (l2.norm * a[i1] > l2.c)
                        return false;
                }
                else
                {
                    pair<ll, ll> tmp = v * intersection(l1, l2);
                    if (ccw(l1.norm, l2.norm) > 0)
                    {
                        if (smaller(low, tmp)) low = tmp;
                    }
                    else
                    {
                        if (smaller(tmp, high)) high = tmp;
                    }
                }
            }
        }
        if (!smaller(low,high)) return false;
    }
    else
    {
        line l1(a[i1], a[nxt(i1, n)]);
        line l2(a[i2], a[nxt(i2, n)]);
        if (parallel(l1, l2)) return false;
        pair<pos, ll> v = intersection(l1, l2);
        for (int i = 0; i < n; i++)
        {
            line l3(a[i], a[nxt(i, n)]);
            if ( b[i] && (smaller(l3.norm*v, make_pair(l3.c, 1)) || smaller(make_pair(l3.c, 1), l3.norm*v))) return false;
            if (!b[i] && !smaller(l3.norm*v, make_pair(l3.c, 1))) return false;
        }
    }

    return true;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int t; cin >> t;
    while (t--)
        cout << (run() ? "TAK\n" : "NIE\n");
    return 0;
}
