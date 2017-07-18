/*
	Circles

	Tested: AIZU
*/

// circle-circle intersection
vector<point> intersect(circle C, circle D)
{
	double d = abs(C.p - D.p);
	if (sign(d - C.r - D.r) > 0) return {};      // too far
	if (sign(d - abs(C.r - D.r)) < 0) return {}; // too close
	double a = (C.r*C.r - D.r*D.r + d*d) / (2*d);
	double h = sqrt(C.r*C.r - a*a);
	point v = (D.p - C.p) / d;
	if (sign(h) == 0) return {C.p + v*a};         // touch
	return {C.p + v*a + point(0,1)*v*h,           // intersect
			C.p + v*a - point(0,1)*v*h};
}

// circle-line intersection
vector<point> intersect(line L, circle C)
{
	point u = L.p - L.q, v = L.p - C.p;
	double a = dot(u, u), b = dot(u, v), c = dot(v, v) - C.r*C.r;
	double det = b*b - a*c;
	if (sign(det) < 0) return {};             // no solution
	if (sign(det) == 0) return {L.p - b/a*u}; // touch
	return {L.p + (-b + sqrt(det))/a*u,
			L.p + (-b - sqrt(det))/a*u};
}

// circle tangents through point
vector<point> tangent(point p, circle C)
{
	// not tested enough

	double D = abs(p - C.p);

	if (D + eps < C.r) return {};
	point t = C.p - p;

	double theta = asin( C.r / D );
	double d = cos(theta) * D;

	t = t / abs(t) * d;
	if ( abs(D - C.r) < eps ) return {p + t};
	point rot( cos(theta), sin(theta) );
	return {p + t * rot, p + t * conj(rot)};
}

bool incircle(point a, point b, point c, point p)
{
	a -= p; b -= p; c -= p;
	return norm(a) * cross(b, c)
			+ norm(b) * cross(c, a)
			+ norm(c) * cross(a, b) >= 0;
			// < : inside, = cocircular, > outside
}

point three_point_circle(point a, point b, point c)
{
	point x = 1.0 / conj(b - a), y = 1.0 / conj(c - a);
	return (y - x) / (conj(x) * y - x * conj(y)) + a;
}

/*
    Get the center of the circles that pass through p0 and p1
    and has ratio r.

    Be careful with epsilon.
*/
vector<point> two_point_ratio_circle(point p0, point p1, double r){
    if (abs(p1 - p0) > 2 * r + eps) // Points are too far.
        return {};

    point pm = (p1 + p0) / 2.0l;
    point pv = p1 - p0;

    pv = point(-pv.imag(), pv.real());

    double x1 = p1.real(), y1 = p1.imag();
    double xm = pm.real(), ym = pm.imag();
    double xv = pv.real(), yv = pv.imag();

    double A = (sqr(xv) + sqr(yv));
    double C = sqr(xm - x1) + sqr(ym - y1) - sqr(r);
    double D = sqrt( - 4 * A * C );
    double t = D / 2.0 / A;

    if (abs(t) <= eps)
        return {pm};

    return {c1, c2};
}

/*
	Area of the intersection of a circle with a polygon
	Circle's center lies in (0, 0)
	Polygon must be given counterclockwise

	Tested: LightOJ 1358
	Complexity: O(n)
*/

#define x(_t) (xa + (_t) * a)
#define y(_t) (ya + (_t) * b)

double radian(double xa, double ya, double xb, double yb)
{
	return atan2(xa * yb - xb * ya, xa * xb + ya * yb);
}

double part(double xa, double ya, double xb, double yb, double r)
{
	double l = sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
	double a = (xb - xa) / l, b = (yb - ya) / l, c = a * xa + b * ya;
	double d = 4.0 * (c * c - xa * xa - ya * ya + r * r);
	if (d < eps)
		return radian(xa, ya, xb, yb) * r * r * 0.5;
	else
	{
		d = sqrt(d) * 0.5;
		double s = -c - d, t = -c + d;
		if (s < 0.0) s = 0.0;
		else if (s > l) s = l;
		if (t < 0.0) t = 0.0;
		else if (t > l) t = l;
		return (x(s) * y(t) - x(t) * y(s)
				+ (radian(xa, ya, x(s), y(s))
				+ radian(x(t), y(t), xb, yb)) * r * r) * 0.5;
	}
}

double intersection_circle_polygon(const polygon &P, double r)
{
	double s = 0.0;
	int n = P.size();;
	for (int i = 0; i < n; i++)
		s += part(P[i].real(), P[i].imag(),
			P[NEXT(i)].real(), P[NEXT(i)].imag(), r);
	return fabs(s);
}
