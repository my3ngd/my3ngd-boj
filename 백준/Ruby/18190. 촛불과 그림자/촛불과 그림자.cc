#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pos = pair<ll, ll>;
using pof = pair<ld, ld>;
#define ff first
#define ss second
const ld EPS = 1e-9;
template<typename T> pair<T, T>  operator+(pair<T, T>& a, pair<T, T>& b) { return {a.ff + b.ff, a.ss + b.ss}; }
template<typename T> pair<T, T>  operator-(pair<T, T>& a, pair<T, T>& b) { return {a.ff - b.ff, a.ss - b.ss}; }
template<typename T> pair<T, T>& operator+=(pair<T, T>& a, pair<T, T>& b) { return a = a + b; }
template<typename T> pair<T, T>& operator-=(pair<T, T>& a, pair<T, T>& b) { return a = a - b; }
template<typename T> pair<T, T>& operator*=(pair<T, T>& a, T k) { return a = a * k; }
template<typename T> pair<T, T>& operator/=(pair<T, T>& a, T k) { return a = a / k; }
template<typename T> T           operator*(pair<T, T>& a, pair<T, T>& b) { return a.ff * b.ff + a.ss * b.ss; }
template<typename T> T           operator/(pair<T, T>& a, pair<T, T>& b) { return a.ff * b.ss - a.ss * b.ff; }
template<typename T> pair<T, T>  operator*(pair<T, T>& a, T k) { return {a.ff * k, a.ss * k}; }
template<typename T> pair<T, T>  operator/(pair<T, T>& a, T k) { return {a.ff / k, a.ss / k}; }
template<typename T> pair<T, T>& operator-(pair<T, T>& a) { return a = {-a.ff, -a.ss}; }
template<typename T> istream& operator>>(istream& is, pair<T, T>& p) { return is >> p.ff >> p.ss; }
template<typename T> ostream& operator<<(ostream& os, pair<T, T>& p) { return os << p.ff << ' ' << p.ss; }
template<typename T> T ccw(pair<T, T> a, pair<T, T> b) { return a.ff * b.ss - a.ss * b.ff; }
template<typename T> T ccw(pair<T, T> a, pair<T, T> b, pair<T, T> c) { return ccw(b-a, c-a); }
template<typename T> int _ccw(pair<T, T> p, pair<T, T> q, pair<T, T> r) { T CCW = ccw(p, q, r); return (CCW ? (CCW > 0 ? 1 : -1) : 0); }
template<typename T> T dist(pair<T, T> a, pair<T, T> b) { return (a - b) * (a - b); }

void init_area(vector<pos>& a, vector<ll>& area)
{
    area.resize(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        area[i] = ccw(a[0], a[i], a[(i+1)%a.size()]);
        assert(area[i] >= 0);
        if (i) area[i] += area[i-1];
        // 좌표 범위가 -4억 ~ 4억 이므로 최대 넓이는 8억 제곱 = 64경 <= (1 << 63)
        assert(area[i] >= 0);
    }
    return ;
}


ll get_area(vector<pos>& a, vector<ll>& area, int st, int en)
{
    if (st == en)  return 0;
    if (st >  en)  return area.back() - get_area(a, area, en, st);
    ll tri = ccw(a[0], a[st], a[en]);   assert(tri >= 0);
    if (st > 0) return area[en-1] - area[st-1] - tri;
    else        return area[en-1] - tri;
}


int point_in_convex(pos& point, vector<pos>& hull)
{
    auto Between = [&](ll& a, ll& b, ll& t) { return (a <= t && t <= b) || (b <= t && t <= a); };
    auto between = [&](pos& a, pos& b, pos& t) { return Between(a.ff, b.ff, t.ff) && Between(a.ss, b.ss, t.ss); };
    int S = 1, E = hull.size()-1, M, ans=0;
    while (E - S > 1)
    {
        M = S + E >> 1;
        if (ccw(hull[0], hull[M], point) < 0) E = M;
        else S = M;
    }
    ll  r0 = abs(ccw(hull[0], hull[S], hull[E])),
        r1 = abs(ccw(hull[0], hull[S], point)),
        r2 = abs(ccw(hull[0], hull[E], point)),
        r3 = abs(ccw(hull[S], hull[E], point)),
        r4 = ccw(hull[0], hull[1], point),
        r5 = ccw(hull[0], hull[hull.size()-1], point);

    if      (r0 == (r1+r2+r3) && r3 && r4 && r5)                      return 1;
    else if (r3 == 0 && between(hull[S], hull[E], point))       return 0;
    else if (r4 == 0 && between(hull[0], hull[1], point))             return 0;
    else if (r5 == 0 && between(hull[0], hull[hull.size()-1], point)) return 0;
    else    return -1;
}


// ri: {1: right, -1: left}
int convex_tangent(vector<pos> &C, pos P, int ri = 1)
{
    C.push_back(C[0]);
    auto side = [&](ll c){ return c > 0 ? ri : c == 0 ? 0 : -ri; };
    auto local = [&](pos P, pos a, pos b, pos c) { return side(ccw(P, a, b)) <= 0 && side(ccw(P, b, c)) >= 0; };
    auto Between = [&](ll& a, ll& b, ll& t) { return (a <= t && t <= b) || (b <= t && t <= a); };
    auto between = [&](pos& a, pos& b, pos& t) { return Between(a.ff, b.ff, t.ff) && Between(a.ss, b.ss, t.ss); };
    auto nxt = [&](int k) { return (k+1)%C.size(); };
    auto pre = [&](int k) { return (k ? k-1 : C.size()-1); };
    auto tune = [&](int idx) { return idx; };
    int N = C.size()-1, S = 0, E = N, M;

    if ( local(P, C[1], C[0], C[N-1]) ) { C.pop_back(); return tune(0); }
    while (S+1 < E)
    {
        M = S + E >> 1;
        if (local(P, C[M-1], C[M], C[M+1])) { C.pop_back(); return tune(M); }
        if (side(ccw(P, C[S], C[S+1])) < 0)
        {
            if      ( side(ccw(P, C[M], C[M+1])) > 0)   E = M;
            else if ( side(ccw(P, C[M], C[S])) > 0)     S = M;
            else                                        E = M;
        }
        else
        {
            if      ( side(ccw(P, C[M], C[M+1])) < 0)   S = M;
            else if ( side(ccw(P, C[M], C[S])) < 0)     S = M;
            else                                        E = M;
        }
    }
    C.pop_back();
    if ( S && local(P, C[S-1], C[S], C[S+1]) )      return tune(S);
    if ( E != N && local(P, C[E-1], C[E], C[E+1]) ) return tune(E);
    return -1;
}


pair<int, int> halfline_intersection(pos& P, pos& Q, vector<pos>& outer)
{
    // edge case: {PQ} intersects {outer[0], outer.back()}
    if (_ccw(P, Q, outer[0]) > 0 && _ccw(P, Q, outer.back()) < 0) return {outer.size()-1, 0};
    if (_ccw(P, Q, outer[0]) == 0 && _ccw(P, Q, outer[1]) > 0) return {0, 0};
    if (_ccw(P, Q, outer.back()) == 0 && _ccw(P, Q, outer[0]) > 0) return {outer.size()-1, outer.size()-1};
    int S = 0, M, E = outer.size()-1;
    while (S+1 < E)
    {
        M = S + E >> 1;
        // case 1: ccw(outer[M], P, outer[S]) >= 0 (normal case)
        if (_ccw(outer[M], P, outer[S]) >= 0)
        {
            // if Q is between outer[S] and outer[M]
            if      (_ccw(P, outer[M], Q) <  0 && _ccw(P, outer[S], Q) >  0) E = M;
            else if (_ccw(P, outer[M], Q) == 0 && _ccw(P, outer[S], Q) >  0) return {M, M};
            else if (_ccw(P, outer[M], Q) <  0 && _ccw(P, outer[S], Q) == 0) return {S, S};
            else                                                             S = M;
        }
        // case 2: ccw(outer[M], P, outer[S] < 0) (unnormal case)
        else
        {
            if      (_ccw(P, outer[M], Q) >  0 && _ccw(P, outer[S], Q) <  0) S = M;
            else if (_ccw(P, outer[M], Q) == 0 && _ccw(P, outer[S], Q) <  0) return {M, M};
            else if (_ccw(P, outer[M], Q) >  0 && _ccw(P, outer[S], Q) == 0) return {S, S};
            else                                                             E = M;
        }
    }
    if (_ccw(P, Q, outer[S]) == 0) return {S, S};
    if (_ccw(P, Q, outer[E]) == 0) return {E, E};
    return {S, E};
}


// intersection point
pof cramer(const pair<pof, pof>& l1, const pair<pof, pof>& l2)
{
    auto eqld = [&](const ld& x, const ld& y) { return abs(x-y) < EPS; };
    auto eqpof = [&](const pof& p, const pof& q) { return eqld(p.ff, q.ff) && eqld(p.ss, q.ss); };

    if (eqpof(l1.ff, l1.ss))return l1.ff;
    if (eqpof(l2.ff, l2.ss))return l2.ff;

    ld  x1=l1.ff.ff, y1=l1.ff.ss, x2=l1.ss.ff, y2=l1.ss.ss,
        X1=l2.ff.ff, Y1=l2.ff.ss, X2=l2.ss.ff, Y2=l2.ss.ss,
        A = y2-y1, B = x1-x2, C = x1*(y2-y1) - y1*(x2-x1),
        D = Y2-Y1, E = X1-X2, F = X1*(Y2-Y1) - Y1*(X2-X1);
    return {(C*E-B*F)/(A*E-B*D), (A*F-C*D)/(A*E-B*D)};
}


void solve(pos& p, vector<pos>& outer, vector<pos>& inner, vector<ll>& o_area, vector<ll>& i_area)
{
    // 1. get tangent
    int ltan = convex_tangent(inner, p, -1),
        rtan = convex_tangent(inner, p,  1);
    pos ltanp = inner[ltan],
        rtanp = inner[rtan];
    // 2. get intersection points of {{p, ltan}, outer}, {{p, rtan}, outer}
    pair<int, int>  l_idx = halfline_intersection(p, ltanp, outer),
                    r_idx = halfline_intersection(p, rtanp, outer);
    ll partial_outhull_area = get_area(outer, o_area, r_idx.ss, l_idx.ff);
    if (l_idx == r_idx) partial_outhull_area = 0;
    ll semi_tri = abs(ccw(p, outer[r_idx.ss], outer[l_idx.ff]));
    if (l_idx == r_idx) semi_tri = 0;
    ll block = abs(ccw(p, rtanp, ltanp)) - abs(get_area(inner, i_area, ltan, rtan)) + i_area.back();

    ld res = 0, le_extra = 0, ri_extra = 0;
    if (l_idx != r_idx)
    {
        if (l_idx.ff != l_idx.ss)
        {
            pof inter_l = cramer({outer[l_idx.ff], outer[l_idx.ss]}, {p, ltanp});
            le_extra = abs(ccw(inter_l, pof(p.ff, p.ss), pof(outer[l_idx.ff])));
        }
        if (r_idx.ff != r_idx.ss)
        {
            pof inter_r = cramer({outer[r_idx.ff], outer[r_idx.ss]}, {p, rtanp});
            ri_extra = abs(ccw(inter_r, pof(p.ff, p.ss), pof(outer[r_idx.ss])));
        }
    }
    else
    {
        pof inter_l = cramer({outer[l_idx.ff], outer[l_idx.ss]}, {p, ltanp});
        pof inter_r = cramer({outer[r_idx.ff], outer[r_idx.ss]}, {p, rtanp});
        le_extra = abs(ccw(inter_l, inter_r, pof(p.ff, p.ss)));
    }
    res = partial_outhull_area + semi_tri - block + le_extra + ri_extra;
    cout << fixed << setprecision(10) << res/2 << '\n';
}


int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, q; cin >> n >> m >> q;
    vector<pos> outer(n), inner(m);
    for (auto& x: outer) cin >> x;
    for (auto& x: inner) cin >> x;

    // 0. init area vector
    vector<ll> o_area, i_area;
    init_area(outer, o_area);
    init_area(inner, i_area);

    for (pos p; q--; )
    {
        cin >> p;
        if      (point_in_convex(p, outer) !=  1) cout << "OUT\n";
        else if (point_in_convex(p, inner) != -1) cout << "IN\n";
        else solve(p, outer, inner, o_area, i_area);
    }
    return 0;
}
