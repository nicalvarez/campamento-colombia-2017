/*
	Pick's theorem
	A = I + B/2 - 1:
	A = Area of the polygon
	I = Number of integer coordinates points inside
	B = Number of integer coordinates points on the boundary

	Polygon's vertex must have integer coordinates

	Tested: LightOJ 1418
	Complexity: O(n)
*/

typedef long long ll;
typedef complex<ll> point;
struct segment { point p, q; };

ll points_on_segment(const segment &s)
{
	point p = s.p - s.q;
	return __gcd(abs(p.real()), abs(p.imag()));
}

// <Lattice points (not in boundary), Lattice points on boundary>
pair<ll, ll> pick_theorem(polygon &P)
{
	ll A = area2(P), B = 0, I = 0;
	for (int i = 0, n = P.size(); i < n; ++i)
		B += points_on_segment({P[i], P[NEXT(i)]});
	A = abs(A);
	I = (A - B) / 2 + 1;
	return {I, B};
}
