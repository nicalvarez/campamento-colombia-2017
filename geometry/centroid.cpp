
/*
	Centroid of a (possibly nonconvex) polygon
	Coordinates must be listed in a cw or ccw.

	Tested: SPOJ STONE
	Complexity: O(n)
*/
	
point centroid(const polygon &P)
{
	point c(0, 0);
	double scale = 3.0 * area2(P); // area2 = 2 * polygon_area
	for (int i = 0, n = P.size(); i < n; ++i)
	{
		int j = NEXT(i);
		c = c + (P[i] + P[j]) * (cross(P[i], P[j]));
	}
	return c / scale;
}
