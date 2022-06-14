#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char const *argv[])
{
    cin.tie(NULL)->sync_with_stdio(false);
    int n; cin >> n;
    vector<ll> a;
    ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        ll x; cin >> x;
        sum += x;
        a.push_back(x);
    }
    for (int i = 0; i < n; i++)
        a.push_back(a[i]);
    ll res = 0;
    for (int i = 0; i < n; i++)
    {
        ll cur = 0;
        for (int j = 0; j < n; j++)
        {
            cur += a[i+j];
            if (cur < 0)
                res += -(cur+1) / sum + 1;
        }
    }
    cout << res << "\n";
    return 0;
}
