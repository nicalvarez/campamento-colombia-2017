
const double pi = acos(-1.0);

// Construct a point on a sphere with center on the origin and radius R
// TESTED [COJ-1436]
struct vec{
	double x, y, z;
	vec (double x=0, double y=0, double z=0) : x(x), y(y), z(z) {}

	vec operator+(const vec a) const{
		return vec(x + a.x, y + a.y, z + a.z);
	}
	vec operator-(const vec a) const{
		return vec(x - a.x, y - a.y, z - a.z);
	}
	vec operator*(const double k) const{
		return vec(k * x, k * y, k * z);
	}
	vec operator/(const double k) const{
		return vec(x / k, y / k, z / k);
	}
	vec operator*(const vec a) const{
		return vec(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
	}
	double dot(const vec a) const{
		return x * a.x + y * a.y + z * a.z;
	}
};

ostream &operator<<(ostream &os, const vec &p)
{
	cout << "(" << p.x << ";" << p.y << ";" << p.z << ")" << endl;
	return os;
}

double abs(vec p)
{
	return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

vec from_polar(double lat, double lon, double R)
{
	lat = lat / 180.0 * pi;
	lon = lon / 180.0 * pi;
	return vec(R * cos(lat) * sin(lon),
				   R * cos(lat) * cos(lon), R * sin(lat));
}

struct plane
{
	double A, B, C, D;
};

/*
 Geodisic distance between points in a sphere
 R is the radius of the sphere
 */
double geodesic_distance(vec p, vec q, double r)
{
	return r * acos(p * q / r / r);
}

// Find the rect of intersection of two planes on the space
// The rect is given parametrical
// TESTED [TIMUS 1239]
void planePlaneIntersection(plane p, plane q)
{
	if (abs(p.C * q.B - q.C * p.B) < eps)
		return; // Planes are parallel

	double mz = (q.A * p.B - p.A * q.B) / (p.C * q.B - q.C * p.B);
	double nz = (q.D * p.B - p.D * q.B) / (p.C * q.B - q.C * p.B);

	double my = (q.A * p.C - p.A * q.C) / (p.B * q.C - p.C * q.B);
	double ny = (q.D * p.C - p.D * q.C) / (p.B * q.C - p.C * q.B);

	// parametric rect: (x, my * x + ny, mz * x * nz)
}
