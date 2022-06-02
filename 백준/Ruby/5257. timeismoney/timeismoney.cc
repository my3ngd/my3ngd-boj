/*
	0. 왼쪽 끝점, 아래 끝점 잡고
	1. 반씩 쪼개가면서 MST 구하고, (time, cost) 점 찍음
	2. time * cost가 최소가 되는 점 찾음
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double ld;
#define ff first
#define ss second
typedef pair<ll, ll> pos;
pos operator+(const pos& p, const pos& q){ return pos(p.ff + q.ff, p.ss + q.ss); }
pos operator-(const pos& p, const pos& q){ return pos(p.ff - q.ff, p.ss - q.ss); }

struct edge
{
	ll st, en, time, cost;
};

struct union_find
{
	vector<int> pa;

	void init(int n)
	{
		pa.resize(n+1);
		for (int i = 0; i < n; i++)
			pa[i] = i;
	}

	int FIND(int x) { return pa[x] = (pa[x] == x ? x : FIND(pa[x])); }

	bool UNION(int p, int q)
	{
		p = FIND(p),
		q = FIND(q);
		if (p == q)	return 0;
		pa[q] = p;	return 1;
	}
} uf;

const ll INF = 1e9;
pos C(INF, INF), Mc(INF, INF);
vector<edge> arr;
int n, m;

pos MST_point(ll c1, ll c2, bool print = false)
{
	pos res(0, 0);
	uf.init(n);
	sort(arr.begin(), arr.end(), [&](const edge& p, const edge& q)
	{
		return c1*p.time + c2*p.cost < c1*q.time + c2*q.cost;
	});
	for (int i = 0; i < m; i++)
	{
		if (uf.UNION(arr[i].st, arr[i].en))
		{
			res.ff += arr[i].time;
			res.ss += arr[i].cost;
			if (print)	cout << arr[i].st << " " << arr[i].en << "\n";
		}
	}
	if (C.ff*C.ss > res.ff*res.ss)
	{
		C.ff = res.ff; Mc.ff = c1;
		C.ss = res.ss; Mc.ss = c2;
	}
	return res;
}

inline bool is_ccw(const pos& p, const pos& q, const pos& r) { return (p.ff-q.ff)*(p.ss-r.ss) > (p.ss-q.ss)*(p.ff-r.ff); }

inline void divcon(const pos& st, const pos& en)
{
	pos md = st - en; md = MST_point(md.ss, -md.ff);  // rot cw pi/4
	if (is_ccw(st, md, en))	divcon(st, md), divcon(md, en);
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	cin >> n >> m;
	arr.resize(m);
	for (int i = 0; i < m; i++)
		cin >> arr[i].st >> arr[i].en >> arr[i].time >> arr[i].cost;

	pos	up = MST_point(1, 0),
		dn = MST_point(0, 1);

	divcon(up, dn);
	cout << C.ff << " " << C.ss << "\n\n";
	MST_point(Mc.ff, Mc.ss, 1);

	return 0;
}
