#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ff first
#define ss second
typedef pair<ll, ll> pos;
pos  operator+(const pos& p, const pos& q){ return pos(p.ff + q.ff, p.ss + q.ss); }
pos  operator-(const pos& p, const pos& q){ return pos(p.ff - q.ff, p.ss - q.ss); }
pos& operator-(pos& p){ p.ff *= -1; p.ss *= -1; return p; }
pos& operator+=(pos& p, const pos& q){ return p = p + q; }
pos& operator-=(pos& p, const pos& q){ return p = p - q; }
ll operator*(const pos& p, const pos& q){ return p.ff*q.ss - p.ss*q.ff; }
template<typename T> ostream& operator<<(ostream& os, const pair<T, T>& p) { return os << p.ff << ' ' << p.ss; }
template<typename T> istream& operator>>(istream& is, pair<T, T>& p) { return is >> p.ff >> p.ss; }
 
inline ll dist(const pos& p, const pos& q) { return (p.ff-q.ff)*(p.ff-q.ff)+(p.ss-q.ss)*(p.ss-q.ss); }
inline ll ccw(const pos& p, const pos& q) { return (p.ff*q.ss) - (p.ss*q.ff); }
inline ll ccw(const pos& p, const pos& q, const pos& r) { return (p.ff-q.ff)*(p.ss-r.ss) - (p.ss-q.ss)*(p.ff-r.ff); }
inline int _ccw(const pos& p, const pos& q, const pos& r) { ll CCW = ccw(p, q, r); return (CCW?CCW/abs(CCW):0);}
inline int _ccw(const pos& p, const pos& q) { ll CCW = ccw(p, q); return (CCW?CCW/abs(CCW):0);}
 
inline ll MOD (ll x) { return (x%1000000007); }
 
int point_in_convex(pos& point, vector<pos>& hull)
{
	auto Between = [&](const ll& a, const ll& b, const ll& t) { return (a <= t && t <= b) || (b <= t && t <= a); };
	auto between = [&](const pos& a, const pos& b, const pos& t) { return Between(a.ff, b.ff, t.ff) && Between(a.ss, b.ss, t.ss); };
	int head = 1, tail = hull.size()-1, body, ans=0;
	while (tail - head > 1)
	{
		body = (head+tail) >> 1;
		if (ccw(hull[0], hull[body], point) < 0)
			tail = body;
		else
			head = body;
	}
	ll  r0 = abs(ccw(hull[0], hull[head], hull[tail])),
		r1 = abs(ccw(hull[0], hull[head], point)),
		r2 = abs(ccw(hull[0], hull[tail], point)),
		r3 = abs(ccw(hull[head], hull[tail], point)),
		r4 = ccw(hull[0], hull[1], point),
		r5 = ccw(hull[0], hull[hull.size()-1], point);
 
	if		(r0 == (r1+r2+r3) && r3 && r4 && r5)						return 1;
	else if	(r3 == 0 && between(hull[head], hull[tail], point))			return 0;
	else if	(r4 == 0 && between(hull[0], hull[1], point))				return 0;
	else if	(r5 == 0 && between(hull[0], hull[hull.size()-1], point))	return 0;
	else	return -1;
}
 
 
// ri: {1: right, -1: left}
int convex_tangent(vector<pos> &C, pos P, int ri = 1)
{
	C.push_back(C[0]);
	auto side = [&](ll c){ return c > 0 ? ri : c == 0 ? 0 : -ri; };
	auto local = [&](pos P, pos a, pos b, pos c) { return side(ccw(P, a, b)) <= 0 && side(ccw(P, b, c)) >= 0; };
	auto Between = [&](const ll& a, const ll& b, const ll& t) { return (a <= t && t <= b) || (b <= t && t <= a); };
	auto between = [&](const pos& a, const pos& b, const pos& t) { return Between(a.ff, b.ff, t.ff) && Between(a.ss, b.ss, t.ss); };
	auto nxt = [&](int k)	{ return (k+1)%C.size(); };
	auto pre = [&](int k)	{ return (k ? k-1 : C.size()-1); };
	auto tune = [&](int idx)
	{
		if		(ri > 0 && !_ccw(P, C[idx], C[pre(idx)]))	idx = pre(idx);
		else if	(ri < 0 && !_ccw(P, C[idx], C[nxt(idx)]))	idx = nxt(idx);
		return idx;
	};
 
	int N = C.size()-1, S = 0, E = N, M;
 
	if ( local(P, C[1], C[0], C[N-1]) ) { C.pop_back(); return tune(0); }
 
	while (S+1 < E)
	{
		M = (S+E) / 2;
		if ( local(P, C[M-1], C[M], C[M+1]) ) { C.pop_back(); return tune(M); }
		if ( side(ccw(P, C[S], C[S+1])) < 0) // ri
		{
			if		( side(ccw(P, C[M], C[M+1])) > 0)	E = M;
			else if	( side(ccw(P, C[M], C[S])) > 0)		S = M;
			else										E = M;
		}
		else // down
		{
			if		( side(ccw(P, C[M], C[M+1])) < 0)	S = M;
			else if	( side(ccw(P, C[M], C[S])) < 0)		S = M;
			else										E = M;
		}
	}
 
	C.pop_back();
	if ( S && local(P, C[S-1], C[S], C[S+1]) )		return tune(S);
	if ( E != N && local(P, C[E-1], C[E], C[E+1]) )	return tune(E);
	return -1;
}
 
void init_area(const vector<pos>& a, vector<ll>& area)
{
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
 
ll get_area(const vector<pos>& a, const vector<ll>& area, int st, int en)
{
	if (st == en)	return 0;
	if (st >  en)	return area.back() - get_area(a, area, en, st);
	ll tri = ccw(a[0], a[st], a[en]);	assert(tri >= 0);
	if (st > 0)	return area[en-1] - area[st-1] - tri;
	else		return area[en-1] - tri;
}
 
 
int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	int n, m; cin >> n >> m;
	vector<pos> dart(n);
	for (auto& i : dart) cin >> i;
 
	vector<ll> area(n);
	init_area(dart, area);
	vector<ll> users(2);
	for (auto& user: users)
	{
		for (int i = 0; i < m; i++)
		{
			pos p; cin >> p;
			int included = point_in_convex(p, dart);
			if	  (included == 1)  // inside
				user = MOD(user + MOD(area.back()));
			else if (included == -1) // outside
			{
				ll temp = get_area(dart, area, convex_tangent(dart, p, -1), convex_tangent(dart, p,  1));
				user = MOD(user + MOD(min(temp, area.back() - temp)));
			}
			assert(user >= 0);
		}
	}
 
	// result
	cout << (users[0] == users[1] ? "same" : (users[0] > users[1] ? "ym" : "hb")) << '\n';
	cout << users[0] << ' ' << users[1] << '\n';
	return 0;
}
