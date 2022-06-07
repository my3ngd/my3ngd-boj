#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double ld;
#define ff first
#define ss second

vector<vector<int>> a;

vector<int> BFS(int st, int sz)
{
	vector<int> leaves;
	queue<int> q;
	vector<int> visit(sz+1, 0);

	q.push(st);
	while (q.size())
	{
		int tmp = q.front(); q.pop();
		for (int x : a[tmp])
		{
			if (!visit[x])
			{
				if (a[x].size() == 1)
					leaves.push_back(x);
				visit[x]++;
				q.push(x);
			}
		}
	}
	return leaves;
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	int n; cin >> n;
	n--;

	a.resize(n+1);
	vector<int> degree(n+1, 0);

	for (int i = 0; i < n; i++)
	{
		int x, y;	cin >> x >> y;
		a[x].push_back(y);	degree[x]++;
		a[y].push_back(x);	degree[y]++;
	}

	vector<int> res = BFS(1, n);
	if (res.size() <= 2)
	{
		for (int i = 0; i <= n; i++)	cout << i << " ";
		return 0;
	}
	queue<pair<int, int>> q;
	for (int x : res)
		q.push({x, 0});

	vector<int> visit(n+1, 0);
	for (int x : res)
		visit[x]++;
	vector<vector<int>> nodes;
	while (q.size())
	{
		pair<int, int> cur = q.front();	q.pop();

		if (cur.ss >= nodes.size())
			nodes.push_back({});

		for (int x : a[cur.ff])
		{
			degree[x]--;
			if (!visit[x] && degree[x] == 1)
			{
				visit[x]++;
				q.push({x, cur.ss+1});
				nodes[cur.ss].push_back(x);
			}
		}
	}

	res.clear();
	for (int i = 0; i < nodes.size(); i++)
		if (nodes[i].size() <= 2)
			for (int j = 0; j < nodes[i].size(); j++)
				res.push_back(nodes[i][j]);

	sort(res.begin(), res.end());
	for (int x : res)
		cout << x << " ";

	return 0;
}