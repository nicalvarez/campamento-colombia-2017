#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-7;

struct point{
    double x, y, z;

    point(){
        x = y = z = 0;
    }

    point(double X, double Y, double Z){
        x = X, y = Y, z = Z;
    }

    bool positive(){
        return x >= 0 && y >= 0 && z >= 0;
    }

    double norm(){
        return sqrt(x * x + y * y + z * z);
    }

    point normalized(){
        return (*this) * (1.0 / norm());
    }

    double operator *(point &p){
        return p.x * x + p.y * y + p.z * z;
    }

    point operator *(double v){
        return point(x * v, y * v, z * v);
    }

    void print(){
        cout << x << " " << y << " " << z << endl;
    }
};

double sqr(double v){
    return v * v;
}

struct sphere{
    point p;
    double r;

    bool ray(point R){
        double l = (p * R) / (R * R);
        double d = sqrt(sqr(p.x - l * R.x) + sqr(p.y - l * R.y) + sqr(p.z - l * R.z));
        return d <= r + eps;
    }
};

struct plane{
    double A, B, C, D;
    plane(){
        A = B = C = D = 0;
    }

    plane(sphere s){
        point p = s.p.normalized();
        A = p.x, B = p.y, C = p.z;
        double n = s.p.norm();
        D = -sqrt(1 - s.r * s.r / n / n);
    }

    double eval(point p){
        return p.x * A + p.y * B + p.z * C + D;
    }

    void print(){
        cout << "plane: " << A << " " << B << " " << C << " " << D << endl;
    }
};

vector<double> solveQuadratic(double A, double B, double C){
    double D = B * B - 4 * A * C;
    vector<double> sol;

    if (abs(D) < eps){
        sol.push_back(-B / 2.0 / A);
    }

    if (D < 0) return sol;

    sol.push_back((-B + sqrt(D)) / 2.0 / A);
    sol.push_back((-B - sqrt(D)) / 2.0 / A);

    return sol;
}

// Plane-Plane-Sphere Intersection
vector<point> intersect(plane p1, plane p2){
    vector<point> ans;

    if (abs(p1.C * p2.B - p2.C * p1.B) < eps) return ans;

    double mz = (p2.A * p1.B - p1.A * p2.B) / (p1.C * p2.B - p2.C * p1.B);
    double nz = (p2.D * p1.B - p1.D * p2.B) / (p1.C * p2.B - p2.C * p1.B);

    double my = (p2.A * p1.C - p1.A * p2.C) / (p1.B * p2.C - p1.C * p2.B);
    double ny = (p2.D * p1.C - p1.D * p2.C) / (p1.B * p2.C - p1.C * p2.B);

    double A = 1 + my * my + mz * mz;
    double B = 2 * my * ny + 2 * mz * nz;
    double C = ny * ny + nz * nz - 1;

    vector<double> sol = solveQuadratic(A, B, C);

    for (auto x : sol){
        point p(x, my * x + ny, mz * x + nz);
        if (p.positive()) ans.push_back(p);
    }

    return ans;
}

vector<int> check(point p, vector<sphere> &spheres){
    vector<int> ans;
    for (int i = 0; i < (int)spheres.size(); ++i)
        if (spheres[i].ray(p)) ans.push_back(i);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<sphere> spheres(n);
    vector<plane> planes(n);
    vector<int> ans;

    for (int i = 0; i < n; ++i){
        cin >> spheres[i].p.x >> spheres[i].p.y >> spheres[i].p.z >> spheres[i].r;
        planes[i] = plane(spheres[i]);
    }

    for (int i = 0; i < n; ++i){
        auto cur = check(spheres[i].p, spheres);
        if (cur.size() > ans.size()) ans = cur;
        for (int j = i + 1; j < n; ++j){
            auto inter = intersect(planes[i], planes[j]);
            for (auto ii : inter){
                cur = check(ii, spheres);
                if (cur.size() > ans.size()) ans = cur;
            }
        }
    }

    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i)
        cout << ans[i] + 1 << " \n"[i + 1 == (int)ans.size()];

    return 0;
}