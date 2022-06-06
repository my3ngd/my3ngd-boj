#include <bits/stdc++.h>
using namespace std;
typedef double dd;
const int MAX = 210;
const int WALL = 10;
const dd PI = 4*atan(1.0);
const dd TOL = 1e-10;

struct circle
{
	dd x, y, r;
} craters[MAX];

struct fenceSeg
{
	int c1;		// first circle index
	dd x1, y1;	// intersection point on first circle
	int c2;		// ditto for second circle
	dd x2, y2;
	dd ang;		// angle from center of circles to tangent points
};

fenceSeg fence[2*MAX-2];
int nfence;

inline bool eq(dd a, dd b)
{return (fabs(a-b) < TOL);}

inline dd dist(dd x1, dd y1, dd x2, dd y2)
{
	dd	dx = x2-x1,
		dy = y2-y1;
	return sqrt(dx*dx+dy*dy);
}

bool calcTangent(dd x1, dd y1, dd r1, dd x2, dd y2, dd r2, dd startAng, dd& x_1, dd& y_1, dd& x_2, dd& y_2, dd& ang)
{
	if (r2 < r1)		return calcTangent(x2, y2, r2, x1, y1, r1, startAng, x_2, y_2, x_1, y_1, ang);
	dd	dx = x2-x1,
		dy = y2-y1,
		dis_12 = sqrt(dx*dx+dy*dy),			// distance between centers
		tdist = dis_12*dis_12 - (r2-r1)*(r2-r1);
	
	if (tdist <= 0.0)		return false;
	
	tdist = sqrt(tdist);					// length of tangent line
	dd	a1 = atan2(dy, dx),					// angle of line between centers
		a2 = atan2(fabs(r2-r1), tdist),		// angle between that line and
		a3 = a1 - a2 - PI/2,				// first angle of radius to
		a4 = a1 + a2 + PI/2;				// second angle of radius to
	if (a3 < -PI)	a3 += 2*PI;
	if (a4 > PI)	a4 -= 2*PI;
	if (a4 < a3)	swap(a3, a4);
	if (!eq(a3, startAng) && a3 > startAng)
	{
		ang = a3;
		x_1 = x1 + r1*cos(ang);
		y_1 = y1 + r1*sin(ang);
		x_2 = x2 + r2*cos(ang);
		y_2 = y2 + r2*sin(ang);
		return true;
	}
	else if (!eq(a4, startAng) && a4 > startAng)
	{
		ang = a4;
		x_1 = x1 + r1*cos(ang);
		y_1 = y1 + r1*sin(ang);
		x_2 = x2 + r2*cos(ang);
		y_2 = y2 + r2*sin(ang);
		return true;
	}
	else
		return false;
}

dd getNextAngle(int idx, dd startAng, int n)
{
	dd x_1, y_1, x_2, y_2, ang;
	dd nextAng = 3*PI;
	fence[nfence].ang = -2*PI;
	bool found = false;
	for(int i = 0; i < n; i++)
	{
		if (i == idx)	continue;
		if ((calcTangent(craters[idx].x, craters[idx].y, craters[idx].r, craters[i].x, craters[i].y, craters[i].r, startAng, x_1, y_1, x_2, y_2, ang)) && 
			(ang < nextAng || (eq(ang, nextAng) && dist(x_1, y_1, x_2, y_2) > dist(x_1, y_1, fence[nfence].x2, fence[nfence].y2))))
		{
			fence[nfence].c1 = idx;
			fence[nfence].x1 = x_1;
			fence[nfence].y1 = y_1;
			fence[nfence].c2 = i;
			fence[nfence].x2 = x_2;
			fence[nfence].y2 = y_2;
			fence[nfence].ang = ang;
			nextAng = ang;
			found = true;
		}
	}
	dd retVal = fence[nfence].ang;
	if (found)	nfence++;
	return retVal;
}

int inside(int idx, int n)
{
	dd	x = craters[idx].x,
		y = craters[idx].y,
		r = craters[idx].r;

	for(int i = 0; i < n; i++)
	{
		if (i == idx)			continue;
		if (r > craters[i].r)	continue;

		dd	dx = craters[i].x - x,
			dy = craters[i].y - y;
		if (sqrt(dx*dx+dy*dy)+r <= craters[i].r)	return 1;
	}
	return 0;
}

int removeConcentricCircles(int n)
{
	for(int i = 0; i < n; i++)
	{
		int j = inside(i,n);
		if (j)
		{
			craters[i] = craters[n-1];
			i--, n--;
		}
	}
	return n;
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;	cin >> n;
	
	for(int i = 0; i < n; i++)
	{
		cin >> craters[i].x >> craters[i].y >> craters[i].r;
		craters[i].r += WALL;
	}
	
	n = removeConcentricCircles(n);

	// exception
	if (n == 1)
	{
		printf("%.8f", 2*PI*craters[0].r);
		return 0;
	}

	dd min_x = craters[0].x - craters[0].r;
	int idx = 0;
	for(int i = 1; i < n; i++)
	{
		dd tmp = craters[i].x - craters[i].r;
		if (tmp < min_x || (tmp == min_x && craters[i].y > craters[idx].y))
		{
			idx = i;
			min_x = tmp;
		}
	}
	dd prevAng, newAng = -2*PI;
	do
	{
		prevAng = newAng;
		newAng = getNextAngle(idx, newAng, n);
		idx = fence[nfence-1].c2;
	} while (newAng > prevAng);

	dd length = (fence[0].ang-fence[nfence-1].ang+2*PI)*craters[fence[0].c1].r + dist(fence[0].x1, fence[0].y1, fence[0].x2, fence[0].y2);
	for(int i = 1; i < nfence; i++)
		length += (fence[i].ang-fence[i-1].ang)*craters[fence[i].c1].r + dist(fence[i].x1, fence[i].y1, fence[i].x2, fence[i].y2);
	
	printf("%.8f", length);
}