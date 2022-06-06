#include <bits/stdc++.h>
#define ff first
#define ss second
#define nxt(i, n) (((i)+1)%(n))
#define pre(i, n) (((i)+(n)-1)%(n))
#define endl '\n'
using namespace std;
using ld = long double;
const ld eps = 1e-9;


typedef long double ld;
struct pos
{
    ld x, y;

    pos(ld x = 0, ld y = 0) : x(x), y(y) {}
    pos  operator+ (const pos p) const { return {x + p.x, y + p.y}; }
    pos  operator- (const pos p) const { return {x - p.x, y - p.y}; }
    pos  operator* (const int a) const { return {x * a, y * a}; }
    pos  operator/ (const int a) const { return {x / a, y / a}; }
    pos  operator* (const ld  a) const { return {x * a, y * a}; }
    pos  operator/ (const ld  a) const { return {x / a, y / a}; }
    ld   operator* (const pos p) const { return x * p.x + y * p.y; }
    ld   operator/ (const pos p) const { return x * p.y - y * p.x; }
    pos& operator+=(const pos p)       { return *this = *this + p; }
    pos& operator-=(const pos p)       { return *this = *this - p; }
    pos& operator*=(const int a)       { return *this = *this * a; }
    pos& operator/=(const int a)       { return *this = *this / a; }
    pos& operator*=(const ld  a)       { return *this = *this * a; }
    pos& operator/=(const ld  a)       { return *this = *this / a; }
    pos& operator- (void)              { return *this = *this * -1; }
    bool operator==(const pos p) const { return x == p.x && y == p.y; }
    bool operator!=(const pos p) const { return !(*this == p); }
    bool operator< (const pos p) const { return x < p.x || (x == p.x && y < p.y); }
    bool operator<=(const pos p) const { return *this < p || *this == p; }
    bool operator> (const pos p) const { return !(*this <= p); }
    bool operator>=(const pos p) const { return !(*this < p); }
    friend istream& operator>>(istream &is, pos &p) { return is >> p.x >> p.y; }
    friend ostream& operator<<(ostream &os, const pos &p) { return os << p.x << " " << p.y; }
};
using polygon = vector<pos>;

bool ne(ld x) { return x < -eps; }
bool ze(ld x) { return abs(x) <= eps; }
bool po(ld x) { return x > eps; }
bool eq(ld x, ld y)
{
    if (ze(x-y)) return true;
    ld lo = min( x*(1-eps), x*(1+eps) ), hi = max( x*(1-eps), x*(1+eps) );
    return (lo <= y && y <= hi);
}
bool eq(const vector<ld> &A, const vector<ld> &B)
{
    if (A.size() != B.size()) return false;
    for (int i = 0; i<A.size(); i++) if (!eq(A[i],B[i])) return false;
    return true;
}
bool eq(const pos &A, const pos &B) { return ze((B).x-(A).x) && ze((B).y-(A).y); }
int signum(ld x) { if (ze(x)) return 0; if (ne(x)) return -1; return 1; }
ld _ccw(const pos &A, const pos &B) { return (A).x * (B).y - (B).x * (A).y; }
ld size(const pos &A) { return sqrt((A).x * (A).x + (A).y * (A).y); }
bool ccw(const pos &A, const pos &B, const pos &C) { return po( _ccw( B-A, C-A )); }
bool ccw(const pos &B, const pos &C)               { return po( _ccw( B,   C ));   }

ld poly_area(const polygon &V)
{
    ld res = 0;
    for (int i = 0; i<V.size(); i++) res += _ccw( V[i], V[nxt(i, V.size())] );
    return abs(0.5 * res);
}

vector<ld> side_lengths(const polygon &P)
{
    int n = P.size();
    vector<ld> answer;
    for (int i = 0; i < n; i++)
        answer.push_back( size( P[nxt(i, n)] - P[i] ) );
    return answer;
}

int ID;

struct object
{
    int id;
    polygon P;
    object(const polygon &P) : P(P) { id = ID++; }
};


void write_poly(const polygon &P)
{
    cout << P.size();
    for (auto pt : P) cout << " " << (pt).x << " " << (pt).y;
    cout << endl;
}


polygon read_poly(void)
{
    int n; cin >> n;
    polygon P(n);
    for (int i = 0; i < n; i++)
        cin >> P[i];
    return P;
}

polygon nice_rect(ld x, ld y, ld dx = 0, ld dy = 0) { return { pos(dx,dy), pos(dx+x,dy), pos(dx+x,dy+y), pos(dx,dy+y) }; }

void cut_paste(int startWith, const vector<polygon> &cutInto, const vector<polygon> &rearrangeInto, const polygon &endWith)
{
    cout << "scissors" << endl << startWith << " " << cutInto.size() << endl;
    vector<int> new_ids;
    for (const auto &piece : cutInto) { new_ids.push_back( ID++ ); write_poly(piece); }
    cout << "tape" << endl << rearrangeInto.size();
    for (int x : new_ids) cout << " " << x;
    cout << endl;
    for (const auto &piece : rearrangeInto) write_poly(piece);
    write_poly(endWith);
}

object nice_rect_to_nice_rect(object rect_in, const polygon &rect_out)
{
    while (true)
    {
        ld x1 = (rect_in.P[2]).x, y1 = (rect_in.P[2]).y, x2 = (rect_out[2]).x, y2 = (rect_out[2]).y;
        if (eq(x1,x2)) return rect_in;
        if (!ne(x1 - 2*x2))
        {
            cut_paste(
                rect_in.id,
                { nice_rect( x1/2, y1 ), nice_rect( x1/2, y1, x1/2,  0 ) },
                { nice_rect( x1/2, y1 ), nice_rect( x1/2, y1,    0, y1 ) },
                nice_rect( x1/2,y1*2 )
            );
            rect_in = object(nice_rect(x1/2,y1*2));
            continue;
        }

        if (!ne(y1 - 2*y2))
        {
            cut_paste(
                rect_in.id,
                { nice_rect( x1, y1/2 ), nice_rect( x1, y1/2,  0, y1/2 ) },
                { nice_rect( x1, y1/2 ), nice_rect( x1, y1/2, x1,    0 ) },
                nice_rect( x1*2,y1/2 )
            );
            rect_in = object(nice_rect(x1*2,y1/2));
            continue;
        }

        if (po(x1 - x2))
        {
            ld x0 = x1 - x2, y0 = y1 * x0 / x2;
            cut_paste(
                rect_in.id,
                { { pos(0,0), pos(x2,y1), pos(0,y1) },    { pos(0,0), pos(x0,0), pos(x0,y0) },   { pos(x0,0), pos(x1,0), pos(x1,y1), pos(x2,y1), pos(x0,y0) } },
                { { pos(0,y0), pos(x2,y2), pos(0,y2) }, { pos(x2-x0,y1), pos(x2,y1), pos(x2,y2) }, { pos(0,0), pos(x2,0), pos(x2,y1), pos(x2-x0,y1), pos(0,y0) }  },
                nice_rect(x2,y2)
            );
            return object(rect_out);
        } else {
            ld y0 = y1 - y2, x0 = x1 * y0 / y2;
            cut_paste(
                rect_in.id,
                { { pos(0,0), pos(x1,0), pos(x1,y2) },    { pos(0,0), pos(x0,y0), pos(0,y0) },             { pos(0,y0), pos(x0,y0), pos(x1,y2), pos(x1,y1), pos(0,y1) } },
                { { pos(x0,0), pos(x2,0), pos(x2,y2) }, { pos(x2-x0,y2-y0), pos(x2,y2), pos(x2-x0,y2) }, { pos(0,0), pos(x0,0), pos(x1,y2-y0), pos(x1,y2), pos(0,y2) }  },
                nice_rect(x2,y2)
            );
            return object(rect_out);
        }
    }
}

pair<polygon,polygon> tri_to_nice_tri(const polygon &P)
{
    vector<ld> sides = side_lengths(P);
    vector<ld> copied = sides;
    int offset = 0;
    rotate( copied.begin(), copied.begin()+1, copied.end() ); if (copied > sides) sides = copied, offset = 2;
    rotate( copied.begin(), copied.begin()+1, copied.end() ); if (copied > sides) sides = copied, offset = 1;
    ld x = sides[0], y = sides[1], z = sides[2], cx = (x*x + z*z - y*y) / (2*x), cy = sqrt( z*z - cx*cx );
    polygon tar = { pos(0, 0), pos(x, 0), pos(cx, cy) };
    polygon src = { tar[offset], tar[(offset+1)%3], tar[(offset+2)%3] };
    return {src, tar};
}

object tri_to_nice_tri(const object &tri_in)
{
    auto nice = tri_to_nice_tri(tri_in.P);
    cout << "tape" << endl;
    cout << "1 " << tri_in.id << endl;
    write_poly(nice.first);
    write_poly(nice.second);
    return object(nice.second);
}

object nice_triangle_to_nice_rectangle(const object &tri_in)
{
    ld x = (tri_in.P[1]).x, cx = (tri_in.P[2]).x, cy = (tri_in.P[2]).y;
    cut_paste(
        tri_in.id,
        { { pos(0,0), pos(x,0), pos((x+cx)/2,cy/2), pos(cx/2,cy/2) }, { pos(cx,cy/2), pos((x+cx)/2,cy/2), pos(cx,cy) }, { pos(cx/2,cy/2), pos(cx,cy/2), pos(cx,cy) } },
        { { pos(0,0), pos(x,0), pos((x+cx)/2,cy/2), pos(cx/2,cy/2) }, { pos(x,cy/2), pos((x+cx)/2,cy/2), pos(x,0) },    { pos(cx/2,cy/2), pos(0,cy/2), pos(0,0) }    },
        nice_rect(x,cy/2)
    );
    return object(nice_rect(x,cy/2));
}

object rectangle_to_nice_triangle(const object &rect_in, const polygon &tri)
{
    polygon nice = tri_to_nice_tri(tri).second;
    ld x = (nice[1]).x, cx = (nice[2]).x, cy = (nice[2]).y;

    cout << "tape" << endl;
    cout << "1 " << rect_in.id << endl;
    ld width = (rect_in.P[2]).x - (rect_in.P[0]).x, height = (rect_in.P[2]).y - (rect_in.P[0]).y;
    write_poly( nice_rect(width,height) );
    write_poly( nice_rect(width,height) );
    object rect(nice_rect(width,height));

    rect = nice_rect_to_nice_rect(rect,nice_rect(x,width*height/x));

    cut_paste(
            rect.id,
            { { pos(0,0), pos(x,0), pos((x+cx)/2,cy/2), pos(cx/2,cy/2) }, { pos(x,cy/2), pos((x+cx)/2,cy/2), pos(x,0) },    { pos(cx/2,cy/2), pos(0,cy/2), pos(0,0) }    },
            { { pos(0,0), pos(x,0), pos((x+cx)/2,cy/2), pos(cx/2,cy/2) }, { pos(cx,cy/2), pos((x+cx)/2,cy/2), pos(cx,cy) }, { pos(cx/2,cy/2), pos(cx,cy/2), pos(cx,cy) } },
            nice
    );
    return object(nice);
}

bool is_triangle_ear(const polygon &P, pos A, pos B, pos C)
{
    if (!ccw(A,B,C)) return false;
    for (pos X : P)
    {
        if (eq(A,X) || eq(B,X) || eq(C,X)) continue;
        if (ccw(A,B,X) && ccw(B,C,X) && ccw(C,A,X)) return false;
    }
    return true;
}

vector<polygon> triangulate(polygon P)
{
    int n = P.size();
    if (n == 3) return {P};
    for (int i = 0; i < n; i++) if (is_triangle_ear(P,P[i],P[nxt(i, n)],P[(i+2)%n]))
    {
        polygon Q = P;
        Q.erase( Q.begin()+nxt(i, n) );
        vector<polygon> answer = triangulate(Q);
        answer.push_back( {P[i],P[nxt(i, n)],P[(i+2)%n]} );
        return answer;
    }
    assert(false);
}

vector<object> triangulate_input(const object &poly_in)
{
    int n = poly_in.P.size();
    cout << "scissors" << endl;
    cout << poly_in.id << " " << n-2 << endl;

    vector<object> answer;
    for (polygon troj : triangulate(poly_in.P))
    {
        write_poly(troj);
        answer.push_back(object(troj));
    }
    return answer;
}

object merge_rectangulation(const vector<object> &rect)
{
    cout << "tape" << endl;
    cout << rect.size();
    for (auto rect : rect) cout << " " << rect.id;
    cout << endl;
    ld dx = 0;
    for (auto rect : rect)
    {
        auto P = rect.P;
        ld width = (P[2]).x;
        for (auto &pt : P) pt += dx;
        write_poly(P);
        dx += width;
    }
    write_poly(nice_rect(dx,dx));
    return object(nice_rect(dx,dx));
}

vector<object> split_square(const object &sq_in, const vector<polygon> &pieces)
{
    ld a = (sq_in.P[2]).x, dx = 0;
    cout << "scissors" << endl;
    cout << sq_in.id << " " << pieces.size() << endl;
    vector<object> answer;
    for (auto tri : pieces)
    {
        ld width = poly_area(tri) / a;
        auto rect = nice_rect(width,a,dx,0);
        write_poly(rect);
        answer.push_back(object(rect));
        dx += width;
    }
    return answer;
}

void merge_triangulation(const vector<object> &have, vector<polygon> &want, polygon &goal)
{
    int n = have.size();
    cout << "tape" << endl;
    cout << n;
    for (auto tri : have) cout << " " << tri.id;
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        auto havelen = side_lengths(have[i].P);
        while (true)
        {
            auto wantlen = side_lengths(want[i]);
            if (eq(havelen,wantlen)) break;
            rotate( want[i].begin(), want[i].begin()+1, want[i].end() );
        }
        write_poly(want[i]);
    }
    write_poly(goal);
}

int main(int argc, char const* argv[])
{
    cin.tie(NULL)->sync_with_stdio(false);
    ID = 0;
    cout << fixed << setprecision(15);

    polygon pa = read_poly();
    polygon pb = read_poly();

    vector<object> TRIANGULATION = triangulate_input(object(pa));
    ld area = poly_area(pa);
    ld des_y = sqrt(area);
    vector<object> RECTANGULATION;

    for (const auto& tri : TRIANGULATION)
    {
        object nice_tri = tri_to_nice_tri(tri);
        object rect1 = nice_triangle_to_nice_rectangle(nice_tri);
        object rect2 = nice_rect_to_nice_rect(rect1,nice_rect(poly_area(rect1.P)/des_y,des_y));
        RECTANGULATION.push_back(rect2);
    }

    object square = merge_rectangulation(RECTANGULATION);
    vector<polygon> output_triangulation = triangulate(pb);
    RECTANGULATION = split_square(square,output_triangulation);
    TRIANGULATION.clear();

    for (int i = 0; i<output_triangulation.size(); i++)
        TRIANGULATION.push_back(
            rectangle_to_nice_triangle(
                RECTANGULATION[i],
                output_triangulation[i]
            )
        );
    merge_triangulation(TRIANGULATION,output_triangulation,pb);

    return 0;
}