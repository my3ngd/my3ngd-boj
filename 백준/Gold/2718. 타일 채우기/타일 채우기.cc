#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(int argc, char const *argv[])
{
    cin.tie(NULL)->sync_with_stdio(false);
    int T; cin >> T;
    vector<int> a(500);
    a[0] = 1; a[1] = 5; a[2] = 11; a[3] = 36;
    for (int n, sz = 5; T--; )
    {
        cin >> n;
        if (a[n-1] == 0)
            for (int i = sz-1; i < n; i++)
                a[i] = a[i-1] + a[i-2]*5 + a[i-3] - a[i-4];
        cout << a[n-1] << "\n";
        sz = max(sz, n);
    }
    return 0;
}
