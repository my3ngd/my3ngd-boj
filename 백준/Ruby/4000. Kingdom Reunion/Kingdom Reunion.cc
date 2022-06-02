#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define ff first
#define ss second
#define nxt(i, n) ((i) + 1 < (n) ? (i) + 1 : 0)
#define pre(i, n) ((i) - 1 >= 0 ? (i) - 1 : (n) - 1)
#define THRESHOLD 5000
using pos = pair<ll, ll>;

bool between_ll(ll p, ll q, ll target) { return (min(p, q) <= target && target <= max(p, q)); }
bool between_pos(pos p, pos q, pos target) { return between_ll(p.ff, q.ff, target.ff) && between_ll(p.ss, q.ss, target.ss); }
pos  operator+(pos a, pos b) { return pos(a.ff + b.ff, a.ss + b.ss); }
pos  operator-(pos a, pos b) { return pos(a.ff - b.ff, a.ss - b.ss); }
pos  operator*(pos a, ll b) { return pos(a.ff * b, a.ss * b); }
pos  operator/(pos a, ll b) { return pos(a.ff / b, a.ss / b); }
ll   operator*(pos a, pos b) { return a.ff * b.ff + a.ss * b.ss; }
ll   operator/(pos a, pos b) { return a.ff * b.ss - a.ss * b.ff; }
pos& operator-(pos& a) { return a = -a; }
pos& operator+=(pos& a, pos b) { return a = a + b; }
pos& operator-=(pos& a, pos b) { return a = a - b; }
pos& operator*=(pos& a, ll b) { return a = a * b; }
pos& operator/=(pos& a, ll b) { return a = a / b; }
template<typename T> istream& operator>>(istream& is, pair<T, T>& a) { return is >> a.ff >> a.ss; }
template<typename T> ostream& operator<<(ostream& os, pair<T, T> a) { return os << a.ff << ' ' << a.ss; }
int _ccw(pos a, pos b) { ll CCW = a / b; return (CCW > 0) - (CCW < 0); }
int _ccw(pos a, pos b, pos c) { return _ccw(b - a, c - a); }


namespace utils
{
    ll get_polygon_area(const vector<pos>& polygon)
    {
        ll area = 0;
        for (int i = 0, j; i < polygon.size(); i++)
        {
            j = nxt(i, polygon.size());
            area += polygon[i].ff * polygon[j].ss - polygon[j].ff * polygon[i].ss;
        }
        return area;
    }

    ll tune_polygon(vector<pos>& points)
    {
        ll polygon_area = get_polygon_area(points);
        if (polygon_area == 0) return 0;
        if (polygon_area < 0)
        {
            reverse(points.begin(), points.end());
            polygon_area = -polygon_area;
        }
        // remove all colinear points
        deque<pos> res;
        for (auto &p: points)
        {
            while (res.size() >= 2 && _ccw(res[res.size()-2], res.back(), p) == 0 && between_pos(res[res.size()-2], p, res.back()))
                res.pop_back();
            res.push_back(p);
        }
        if (_ccw(res.back(), res.front(), res[1]) == 0 && between_pos(res.back(), res[1], res.front()))
            res.pop_front();
        if (_ccw(res[res.size()-2], res.back(), res.front()) == 0 && between_pos(res[res.size()-2], res.front(), res.back()))
            res.pop_back();
        points.clear();
        for (auto &p: res)
            points.push_back(p);
        return polygon_area;
    }

    vector<pair<pos, pos>> generate_lineset(const vector<pos>& points)
    {
        vector<pair<pos, pos>> lines;
        for (int i = 0; i < points.size(); i++)
        {
            pair<pos, pos> l = {points[i], points[nxt(i, points.size())]};
            if (l.ff > l.ss) swap(l.ff, l.ss);
            lines.push_back(l);
        }
        return lines;
    }

    bool is_line_colinear(const pair<pos, pos>& l1, const pair<pos, pos>& l2)
    {
        // for main_solver::is_intersect
        pos a = l1.ff, b = l1.ss,
            c = l2.ff, d = l2.ss;
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        int abc = _ccw(a, b, c), abd = _ccw(a, b, d),
            cda = _ccw(c, d, a), cdb = _ccw(c, d, b);
        if (abc || abd || cda || cdb) return false;
        // now a, b, c, d are in the same line
        // if they are intersect, ignore them
        // if they are not, no need to check intersection
        // so just return true
        return true;
    }

    bool point_in_concave_polygon(const vector<pos>& polygon, const pos& p)
    {
        auto intersect = [&](const pair<pos, pos> l1, const pair<pos, pos>& l2)
        {
            pos a = l1.ff, b = l1.ss,
                c = l2.ff, d = l2.ss;
            int abc = _ccw(a, b, c), abd = _ccw(a, b, d),
                cda = _ccw(c, d, a), cdb = _ccw(c, d, b);
            return (abc * abd < 0) && (cda * cdb < 0);
        };
        // notice that need to check "fully inside" case only
        const int n = polygon.size();
        pos infty = p + pos(1e6, 1);  // gcd(1e6, 1) == 1
        bool is_in = false;
        for (int i = 0; i < n; i++)
        {
            int j = nxt(i, n);
            // if p is on the edge, return false
            if (_ccw(polygon[i], polygon[j], p) == 0 && between_pos(polygon[i], polygon[j], p))
                return false;
            // now, p is not on the edge
            if (intersect({polygon[i], polygon[j]}, {p, infty}))
                is_in = !is_in;
        }
        return is_in;
    }

    bool line_mergable(const pair<pos, pos>& l1, const pair<pos, pos>& l2, const pair<pos, pos>& l3)
    {
        vector<pair<pos, pos>> lines = {l1, l2, l3};
        for (int i = 0; i < 3; i++)
            for (int j = i + 1; j < 3; j++)
                if (!is_line_colinear(lines[i], lines[j]))
                    return false;
        // now, all lines are colinear
        sort(lines.begin(), lines.end(), [&](const pair<pos, pos>& p, const pair<pos, pos>& q)
        {
            if (p.ff == q.ff) return p.ss > q.ss;
            return p.ff < q.ff;
        });
        // line[0] is the longest line
        return lines[0].ff == lines[1].ff && lines[1].ss == lines[2].ff && lines[2].ss == lines[0].ss;
    }

    bool line_mergable(const pair<pos, pos>& l1, const pair<pos, pos>& l2, const pair<pos, pos>& l3, const pair<pos, pos>& l4)
    {
        vector<pair<pos, pos>> lines = {l1, l2, l3, l4};
        for (int i = 0; i < 4; i++)
            for (int j = i + 1; j < 4; j++)
                if (!is_line_colinear(lines[i], lines[j]))
                    return false;
        // now, all lines are colinear
        sort(lines.begin(), lines.end(), [&](const pair<pos, pos>& p, const pair<pos, pos>& q)
        {
            if (p.ff == q.ff) return p.ss > q.ss;
            return p.ff < q.ff;
        });
        // line[0] is the longest line
        return  (lines[0].ff == lines[1].ff && lines[1].ss == lines[2].ff && lines[2].ss == lines[3].ff && lines[3].ss == lines[0].ss) ||
                (lines[0].ff == lines[1].ff && lines[1].ss == lines[2].ff && lines[2].ss == lines[3].ss && lines[3].ff == lines[0].ss);
    }
}


namespace main_solver
{
    struct line
    {
        pos st, en;
        int idx;
        line() = default;
        line(const pos& _st, const pos& _en, int _idx = 0) : st(_st), en(_en), idx(_idx)
        {
            if (this->st.ff > this->en.ff)
                swap(this->st, this->en);
        }
        ld get(int cur) const
        {
            if (st.ff == en.ff) return 1.0L * (st.ss + en.ss) / 2;
            if (cur == st.ff) return st.ss;
            if (cur == en.ff) return en.ss;
            return st.ss + 1.0L * (en.ss - st.ss) * (cur - st.ff) / (en.ff - st.ff);
        }
        bool operator<(const line &l) const
        {
            if (idx == l.idx) return 0;
            int p = max(st.ff, l.st.ff);
            if (fabs(get(p) - l.get(p)) < 1e-20L) return idx < l.idx;
            return get(p) < l.get(p);
        }
        pair<pos, pos> get_seg(void) const { return {st, en}; }
    };

    bool is_intersect(line a, line b, bool include_edge = true)
    {
        if (utils::is_line_colinear(a.get_seg(), b.get_seg())) return false;
        pos A(a.st.ff, a.st.ss), B(a.en.ff, a.en.ss),
            C(b.st.ff, b.st.ss), D(b.en.ff, b.en.ss);
        auto in_line = [&](const pos& p, const pos& q, const pos& t)
        {
            return between_pos(p, q, t) && _ccw(p, q, t) == 0;
        };
        if (!include_edge && (in_line(A, B, C) || in_line(A, B, D) || in_line(C, D, A) || in_line(C, D, B)))
            return false;
        if (_ccw(A, B, C) == 0 && _ccw(A, B, D) == 0)
        {
            if (A.ff > B.ff) swap(A.ff, B.ff);
            if (A.ss > B.ss) swap(A.ss, B.ss);
            if (C.ff > D.ff) swap(C.ff, D.ff);
            if (C.ss > D.ss) swap(C.ss, D.ss);
            if (max(A.ff, C.ff) == min(B.ff, D.ff) && max(A.ss, C.ss) == min(B.ss, D.ss))  return false;
            if (max(A.ff, C.ff) <= min(B.ff, D.ff) && max(A.ss, C.ss) <= min(B.ss, D.ss))  return true;
            return false;
        }
        if (A == B || A == C || A == D || B == C || B == D || C == D) return false;
        if (_ccw(A, B, C) * _ccw(A, B, D) > 0) return false;
        if (_ccw(C, D, A) * _ccw(C, D, B) > 0) return false;
        return true;
    }

    bool any_intersect(vector<line>& lines, bool include_edge = true)
    {
        int n = lines.size();
        vector<set<line>::iterator> iters(n);
        vector<pos> events;
        sort(lines.begin(), lines.end(), [&](const line& a, const line& b)
        {
            if (a.st.ff != b.st.ff) return a.st.ff < b.st.ff;
            if (a.st.ss != b.st.ss) return a.st.ss < b.st.ss;
            return (a.en.ss - a.st.ss) * (b.en.ff - b.st.ff) < (a.en.ff - a.st.ff) * (b.en.ss - b.st.ss);
        });
        for (int i = 0; i < n; i++)
            lines[i].idx = i;
        for (int i = 0; i < n; i++)
        {
            events.emplace_back(lines[i].st.ff, ~i);  // ~i < 0
            events.emplace_back(lines[i].en.ff, i);   // i >= 0
        }
        sort(events.begin(), events.end());
        set<line> lineset;
        for (auto &e : events)
        {
            ll p = e.ss;
            if (p < 0) p = ~p;
            if (e.ss < 0)
            {
                auto loc = lineset.lower_bound(lines[p]);
                if (loc != lineset.end() && is_intersect(*loc, lines[p], include_edge))
                    return true;
                if (loc != lineset.begin() && is_intersect(*prev(loc), lines[p], include_edge))
                    return true;
                iters[p] = lineset.insert(loc, lines[p]);
            }
            else
            {
                auto loc = lineset.erase(iters[p]);
                if (loc != lineset.begin() && loc != lineset.end() && is_intersect(*prev(loc), *loc, include_edge))
                    return true;
            }
        }
        return false;
    }

    bool is_polygon_simple(const vector<pos>& p1)
    {
        int n = p1.size();
        vector<pos> p2, p3;
        for (int i = 0; i < n; i++)
        {
            p2.emplace_back(p1[i].ff - p1[i].ss, p1[i].ss + p1[i].ff);
            p3.emplace_back(p1[i].ss, p1[i].ff);
        }
        vector<line> l1, l2, l3;
        for (int i = 0; i < n; i++)
        {
            line l = line(p1[i], p1[nxt(i, n)]);
            if (l.st != l.en)
            {
                if (l.st > l.en) swap(l.st, l.en);
                l1.emplace_back(l.st, l.en, i);
            }
            l = line(p2[i], p2[nxt(i, n)]);
            if (l.st != l.en)
            {
                if (l.st > l.en) swap(l.st, l.en);
                l2.emplace_back(l.st, l.en, i);
            }
            l = line(p3[i], p3[nxt(i, n)]);
            if (l.st != l.en)
            {
                if (l.st > l.en) swap(l.st, l.en);
                l3.emplace_back(l.st, l.en, i);
            }
        }
        return !any_intersect(l1, true) && !any_intersect(l2, true) && !any_intersect(l3, true);
    }

    bool is_polygon_overlapped(const vector<pos>& a, const vector<pos>& b)
    {
        set<pair<pos, pos>> lineset;
        for (int i = 0; i < a.size(); i++)
        {
            pair<pos, pos> l = make_pair(a[i], a[nxt(i, a.size())]);
            if (l.ff > l.ss) swap(l.ff, l.ss);
            lineset.insert(l);
        }
        for (int i = 0; i < b.size(); i++)
        {
            pair<pos, pos> l = make_pair(b[i], b[nxt(i, b.size())]);
            if (l.ff > l.ss) swap(l.ff, l.ss);
            if (lineset.find(l) != lineset.end()) lineset.erase(l);
        }
        if (lineset.empty()) return true;  // same polygon
        // there is/are point(s) that is not in the polygon b but in the polygon a
        set<pos> pointset;
        for (auto &p: a)
            pointset.insert(p);
        for (auto &p: b)
            if (pointset.find(p) != pointset.end())
                pointset.erase(p);
        if (pointset.empty())
            return true;  // a is a subset of b
        pos pp = *pointset.begin();
        // find index of pp in a
        int idx = -1;
        for (int i = 0; i < a.size(); i++)
            if (a[i] == pp)
            {
                idx = i;
                break;
            }
        auto odd_point = [&](pos st, pos en)
        {
            pos md = (st + en) / 2;
            for (; md.ff%2 == 0 && md.ss%2 == 0; md = (md + en) / 2);
            assert(_ccw(st, md, en) == 0);
            return md;
        };
        pos qq = a[pre(idx, a.size())];
        pos rr = a[nxt(idx, a.size())];
        pos mpq = odd_point(qq, pp);
        pos mpr = odd_point(pp, rr);
        pos mll = odd_point(lineset.begin()->ff, lineset.begin()->ss);
        return utils::point_in_concave_polygon(b, mpq) || utils::point_in_concave_polygon(b, mpr) || utils::point_in_concave_polygon(b, mll);
    }

    bool is_polygon_intersect(const vector<pos>& a1, const vector<pos>& b1)
    {
        vector<pos> a2, a3, b2, b3;
        for (int i = 0; i < a1.size(); i++)
        {
            a2.emplace_back(a1[i].ff - a1[i].ss, a1[i].ss + a1[i].ff);
            a3.emplace_back(a1[i].ss, a1[i].ff);
        }
        for (int i = 0; i < b1.size(); i++)
        {
            b2.emplace_back(b1[i].ff - b1[i].ss, b1[i].ss + b1[i].ff);
            b3.emplace_back(b1[i].ss, b1[i].ff);
        }
        vector<line> l1, l2, l3;
        for (int i = 0; i < a1.size(); i++) l1.emplace_back(a1[i], a1[nxt(i, a1.size())], i);
        for (int i = 0; i < a2.size(); i++) l2.emplace_back(a2[i], a2[nxt(i, a2.size())], i);
        for (int i = 0; i < a3.size(); i++) l3.emplace_back(a3[i], a3[nxt(i, a3.size())], i);
        for (int i = 0; i < b1.size(); i++) l1.emplace_back(b1[i], b1[nxt(i, b1.size())], i + a1.size());
        for (int i = 0; i < b2.size(); i++) l2.emplace_back(b2[i], b2[nxt(i, b2.size())], i + a1.size());
        for (int i = 0; i < b3.size(); i++) l3.emplace_back(b3[i], b3[nxt(i, b3.size())], i + a1.size());
        if (any_intersect(l1, false) || any_intersect(l2, false) || any_intersect(l3, false)) return true;
        vector<pos> da, db;
        for (auto &p: a1) da.push_back(p*2);
        for (auto &p: b1) db.push_back(p*2);
        if (is_polygon_overlapped(da, db) || is_polygon_overlapped(db, da)) return true;
        // Feel Bad...
        if (da.size() <= THRESHOLD && db.size() <= THRESHOLD)
        {
            for (int i = 0; i < da.size(); i++)
                if (utils::point_in_concave_polygon(db, da[i]) ||
                    utils::point_in_concave_polygon(db, (da[i] + da[nxt(i, da.size())]) / 2))
                    return true;
            for (int i = 0; i < db.size(); i++)
                if (utils::point_in_concave_polygon(da, db[i]) ||
                    utils::point_in_concave_polygon(da, (db[i] + db[nxt(i, db.size())]) / 2))
                    return true;
        }
        return false;
    }

    bool is_polygon_unionable(const vector<pos>& points_a, const vector<pos>& points_b, const vector<pos>& points_c)
    {
        vector<pair<pos, pos>>  a = utils::generate_lineset(points_a),
                                b = utils::generate_lineset(points_b),
                                c = utils::generate_lineset(points_c);
        set<pair<pos, pos>> A_set, B_set, C_set;
        for (const auto &l: a) A_set.insert(l);
        for (const auto &l: b) B_set.insert(l);
        for (const auto &l: c) C_set.insert(l);
        for (auto &l: a)
        {
            if (A_set.find(l) != A_set.end() && B_set.find(l) != B_set.end())
            {
                A_set.erase(l);
                B_set.erase(l);
            }
            if (A_set.find(l) != A_set.end() && C_set.find(l) != C_set.end())
            {
                A_set.erase(l);
                C_set.erase(l);
            }
        }
        for (auto &l: b)
        {
            if (B_set.find(l) != B_set.end() && A_set.find(l) != A_set.end())
            {
                A_set.erase(l);
                B_set.erase(l);
            }
            if (B_set.find(l) != B_set.end() && C_set.find(l) != C_set.end())
            {
                B_set.erase(l);
                C_set.erase(l);
            }
        }

        // case work
        if      (C_set.size() == 0)  return A_set.empty() && B_set.empty();
        else if (C_set.size() == 1)
        {
            if      (A_set.size() == 1 && B_set.size() == 2)
                return utils::line_mergable(*A_set.begin(), *B_set.begin(), *B_set.rbegin(), *C_set.begin());
            else if (A_set.size() == 2 && B_set.size() == 1)
                return utils::line_mergable(*A_set.begin(), *A_set.rbegin(), *B_set.begin(), *C_set.begin());
            else if (A_set.size() == 1 && B_set.size() == 1)
                return utils::line_mergable(*A_set.begin(), *B_set.begin(), *C_set.begin());
        }
        else if (C_set.size() == 2)
        {
            if (A_set.size() == 1 && B_set.size() == 1)
                return utils::line_mergable(*A_set.begin(), *B_set.begin(), *C_set.begin(), *C_set.rbegin());
            else if (A_set.size() == 2 && B_set.size() == 2)
            {
                // (A.begin, A.rbegin), (B.begin, B.rbegin), (C.begin, C.rbegin) -> 8 cases
                // if any of the case is true, then the polygon is unionable
                pair<pos, pos>  A1 = *A_set.begin(), A2 = *A_set.rbegin(),
                                B1 = *B_set.begin(), B2 = *B_set.rbegin(),
                                C1 = *C_set.begin(), C2 = *C_set.rbegin();
                return  (utils::line_mergable(A1, B1, C1) && (utils::line_mergable(A2, B2, C2))) ||
                        (utils::line_mergable(A1, B1, C2) && (utils::line_mergable(A2, B2, C1))) ||
                        (utils::line_mergable(A1, B2, C1) && (utils::line_mergable(A2, B1, C2))) ||
                        (utils::line_mergable(A1, B2, C2) && (utils::line_mergable(A2, B1, C1))) ||
                        (utils::line_mergable(A2, B1, C1) && (utils::line_mergable(A1, B2, C2))) ||
                        (utils::line_mergable(A2, B1, C2) && (utils::line_mergable(A1, B2, C1))) ||
                        (utils::line_mergable(A2, B2, C1) && (utils::line_mergable(A1, B1, C2))) ||
                        (utils::line_mergable(A2, B2, C2) && (utils::line_mergable(A1, B1, C1)));
            }
            else return false;
        }
        return false;
    }
}


int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<pos> a, b, c;
    int n;
    cin >> n; a.resize(n); for (auto &p: a) cin >> p;
    cin >> n; b.resize(n); for (auto &p: b) cin >> p;
    cin >> n; c.resize(n); for (auto &p: c) cin >> p;
    ll area_a = utils::tune_polygon(a);
    ll area_b = utils::tune_polygon(b);
    ll area_c = utils::tune_polygon(c);
    if      (area_a == 0 || !main_solver::is_polygon_simple(a)) cout << "Aastria is not a polygon\n";
    else if (area_b == 0 || !main_solver::is_polygon_simple(b)) cout << "Abstria is not a polygon\n";
    else if (area_c == 0 || !main_solver::is_polygon_simple(c)) cout << "Aabstria is not a polygon\n";
    else if (main_solver::is_polygon_intersect(a, b))           cout << "Aastria and Abstria intersect\n";
    else if (!main_solver::is_polygon_unionable(a, b, c))       cout << "The union of Aastria and Abstria is not equal to Aabstria\n";
    else    cout << "OK\n";
    return 0;
}
