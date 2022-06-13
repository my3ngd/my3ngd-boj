#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
inline int readChar();
template<class T = int> inline T readInt();
template<class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);
static const int buf_size = 1 << 18;
inline int getChar(){
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if(pos == len) pos = 0, len = fread(buf, 1, buf_size, stdin);
	if(pos == len) return -1;
	return buf[pos++];
}
inline int readChar(){
	int c = getChar();
	while(c <= 32) c = getChar();
	return c;
}
template <class T>
inline T readInt(){
	int s = 1, c = readChar();
	T x = 0;
	if(c == '-') s = -1, c = getChar();
	while('0' <= c && c <= '9') x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}
static int write_pos = 0;
static char write_buf[buf_size];
inline void writeChar(int x){
	if(write_pos == buf_size) fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}
template <class T>
inline void writeInt(T x, char end){
	if(x < 0) writeChar('-'), x = -x;
	char s[24]; int n = 0;
	while(x || !n) s[n++] = '0' + x % 10, x /= 10;
	while(n--) writeChar(s[n]);
	if(end) writeChar(end);
}
inline void writeWord(const char *s){
	while(*s) writeChar(*s++);
}
struct Flusher{
	~Flusher(){ if(write_pos) fwrite(write_buf, 1, write_pos, stdout), write_pos = 0; }
}flusher;
// justiceHui's fastio implementation

using ll = long long;
#define ff first
#define ss second
#define endl '\n'
#define pre(i, n) (((i)+(n)-1)%(n))
#define nxt(i, n) (((i)+1)%(n))

struct node
{
    ll min, max, sum;
    node(): min(0), max(0), sum(0) {}
    node(ll _min, ll _max, ll _sum): min(_min), max(_max), sum(_sum) {}
};

struct segbeats
{
    vector<ll> arr;
    vector<node> tree, lazy;

    segbeats(const vector<ll>& arr): arr(arr)
    {
        int n = 1;
        while (n < arr.size()) n <<= 1;
        tree.resize(n<<1);
        lazy.resize(n<<1);
        build(1, 0, arr.size()-1);
    }

    node mer(node a, node b)
    {
        return node(min(a.min, b.min), max(a.max, b.max), a.sum + b.sum);
    }

    node build(int idx, int nl, int nr)
    {
        if (nl == nr)   return tree[idx] = node(arr[nl], arr[nl], arr[nl]);
        int nm = nl + nr >> 1;
        return tree[idx] = mer(
            build(idx<<1|0, nl, nm),
            build(idx<<1|1, nm+1, nr)
        );
    }

    void propagate(int idx, int nl, int nr)
    {
        if (lazy[idx].sum == 0) return ;
        tree[idx].max += lazy[idx].max;
        tree[idx].min += lazy[idx].min;
        tree[idx].sum += lazy[idx].sum * (nr - nl + 1);
        for (int i = 0, ch; nl != nr && i < 2; i++)
        {
            ch = idx<<1|i;
            lazy[ch].max += lazy[idx].max;
            lazy[ch].min += lazy[idx].min;
            lazy[ch].sum += lazy[idx].sum;
        }
        lazy[idx] = node();
        return ;
    }

    void update_plus(int idx, int nl, int nr, int tl, int tr, ll val)
    {
        propagate(idx, nl, nr);
        if (tr <  nl || nr <  tl) return ;
        if (tl <= nl && nr <= tr)
        {
            lazy[idx].min += val;
            lazy[idx].max += val;
            lazy[idx].sum += val;
            return propagate(idx, nl, nr);
        }
        int nm = nl + nr >> 1;
        update_plus(idx<<1|0, nl, nm, tl, tr, val);
        update_plus(idx<<1|1, nm+1, nr, tl, tr, val);
        tree[idx] = mer(tree[idx<<1|0], tree[idx<<1|1]);
        return ;
    }

    void update_sqrt(int idx, int nl, int nr, int tl, int tr)
    {
        propagate(idx, nl, nr);
        if (tr <  nl || nr <  tl || (tree[idx].min == 1 && tree[idx].max == 1)) return ;
        if (tl <= nl && nr <= tr && tree[idx].min - (ll)sqrt(tree[idx].min) == tree[idx].max - (ll)sqrt(tree[idx].max))
        {
            ll val = tree[idx].max - (ll)sqrt(tree[idx].max);
            lazy[idx].min -= val;
            lazy[idx].max -= val;
            lazy[idx].sum -= val;
            return propagate(idx, nl, nr);
        }
        int nm = nl + nr >> 1;
        update_sqrt(idx<<1|0, nl, nm, tl, tr);
        update_sqrt(idx<<1|1, nm+1, nr, tl, tr);
        tree[idx] = mer(tree[idx<<1|0], tree[idx<<1|1]);
        return ;
    }

    ll query_sum(int idx, int nl, int nr, int tl, int tr)
    {
        propagate(idx, nl, nr);
        if (tr <  nl || nr <  tl) return 0;
        if (tl <= nl && nr <= tr) return tree[idx].sum;
        int nm = nl + nr >> 1;
        return query_sum(idx<<1|0, nl, nm, tl, tr) + query_sum(idx<<1|1, nm+1, nr, tl, tr);
    }

    void update_plus(int tl, int tr, ll val) { return update_plus(1, 0, arr.size()-1, tl, tr, val); }
    void update_sqrt(int tl, int tr) { return update_sqrt(1, 0, arr.size()-1, tl, tr); }
    ll query_sum(int tl, int tr) { return query_sum(1, 0, arr.size()-1, tl, tr); }
};


int main(int argc, char const *argv[])
{
    // ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int T = readInt();
    for (int n, q; T--; )
    {
        n = readInt(); q = readInt();
        vector<ll> a(n);
        for (auto& x: a) x = readInt();
        segbeats seg(a);
        for (int type; q--; )
        {
            type = readInt();
            if (type == 3)
            {
                int l, r; ll x;
                l = readInt(); r = readInt(); x = readInt();
                seg.update_plus(l-1, r-1, x);
            }
            else if (type == 1)
            {
                int l, r;
                l = readInt(); r = readInt();
                seg.update_sqrt(l-1, r-1);
            }
            else
            {
                int l, r;
                l = readInt(); r = readInt();
                writeInt(seg.query_sum(l-1, r-1), '\n');
            }
        }
    }
    Flusher();

    return 0;
}
