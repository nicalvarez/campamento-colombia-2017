/*
	Convex Hull 3d implementation.
	Coplanar points case not handled.

	Complexity: O(n^2)
    Tested: opencup 010376(Stars in a Can)
*/
struct face{
	int I[3];
	vec normal;
	int operator[](const int idx) const{
		return I[idx];
	}
};

vector<face> triangulation(vector<vec> &cloud){
	vector<face> F(4);
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 3; ++j)
			F[i].I[j] = j + (j >= i);
		F[i].normal = ( cloud[ F[i][1] ] - cloud[ F[i][0] ]) *
					  ( cloud[ F[i][2] ] - cloud[ F[i][0] ]);

		if (F[i].normal.dot( cloud[i] - cloud[ F[i][0] ] ) > 0){
			F[i].normal = F[i].normal * -1.;
			swap( F[i].I[1], F[i].I[2] );
		}
	}

	int n = (int)cloud.size();
	vector<vi> cnt(n, vi(n));
	vector<vi> tmr(n, vi(n));

	auto mark = [&](int u, int v, int i){
		if (u > v) swap(u, v);
		if (tmr[u][v] != i){
			tmr[u][v] = i;
			cnt[u][v] = 0;
		}
		cnt[u][v]++;
	};

	auto get  = [&](int u, int v){
		if (u > v) swap(u, v);
		return cnt[u][v];
	};

	for (int i = 4; i < n; ++i){
		vector<face> QF;
		vec x = cloud[i];

		for (auto f : F){
			if (f.normal.dot( x - cloud[f[0]] ) > 0){
				mark(f[0], f[1], i);
				mark(f[1], f[2], i);
				mark(f[2], f[0], i);
			}
			else
				QF.push_back( f );
		}

		for (auto f : F){
			if (f.normal.dot( x - cloud[f[0]] ) > 0){
				for (int j = 0; j < 3; ++j){
					int a = f[j], b = f[j != 2 ? j + 1 : 0];
					if (get(a, b) != 1) continue;
					vec u = cloud[a], v = cloud[b];
					vec ref = cloud[ f[j ? j - 1 : 2] ];

					face qf = {i, a, b, vec()};
					qf.normal = (u - x) * (v - x);

					if (qf.normal.dot( ref - x ) > 0){
						qf.normal = qf.normal * -1.;
						swap(qf.I[1], qf.I[2]);
					}

					QF.push_back(qf);
				}
			}
		}
		F.swap( QF );
	}

	return F;
}

/*
	Convex Hull 3d implementation.
	Complexity O(n^4)
	It works ok with coplanar points

	UNTESTED [With the new vec(point3) structure]
*/
struct face{
	int idx[3];

	face(){}
	face(int i, int j, int k){
		idx[0] = i, idx[1] = j, idx[2] = k;
	}

	int& operator[](int u) { return idx[u]; }
};

vector<face> convex_hull( vector<vec> &cloud ){

	int n = (int)cloud.size();
	vector<int> L(n);

	vector<face> faces;

	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			for (int k = j + 1; k < n; ++k){

				vec a = cloud[i], b = cloud[j], c = cloud[k];
				vec nr = (b - a) * (c - a);

				int pnt = 0;
				L[ pnt++ ] = j;
				L[ pnt++ ] = k;

				bool proc = true;

				int v = 0, V = 0;

				for (int l = 0; l < n && proc; ++l){
					if (l == i || l == j || l == k) continue;

					double t = nr.dot( cloud[l] - a );
					if ( abs(t) < eps){
						if (l < k) proc = false;
						else L[ pnt++ ] = l;
					}
					else{
						if (t < 0) v = -1;
						else       V = +1;
					}
				}

				if (!proc || v * V == -1) continue;

				function<bool(int,int)> compare = [&](int u, int v){
					return nr.dot( (cloud[u] - a) * (cloud[v] - a) ) > 0;
				};

				sort(L, L + pnt, compare);

				for (int l = 0; l + 1 < pnt; ++l)
					faces.push_back( face(i, L[l], L[l + 1]) );
			}

	return faces;
}

// Find mass center of a polyhedron given the external faces
// O(n)
void mass_center( vector<vec> &cloud, vector<face> &faces ){
	vec pivot = cloud[0];

	double x = 0, y = 0, z = 0, v = 0;

	for (auto f : faces){
		auto value = 	( cloud[f[0]] - pivot ).dot(
						( cloud[f[1]] - pivot) * (cloud[f[2]] - pivot)
						);

		vec sum = cloud[f[0]] + cloud[f[1]] + cloud[f[2]] + pivot;
		double cvol = abs( 1. * value / 6 );

		v += cvol;

		cvol /= 4;

		x += cvol * sum.X[0];
		y += cvol * sum.X[1];
		z += cvol * sum.X[2];
	}

	x /= v, y /= v, z /= v;

	// Mass center of a polyhedron at (x, y, z)
}

