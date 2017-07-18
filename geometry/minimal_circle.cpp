/*
    Find circle with minimal ratio that contain
    a cloud of points in 2d.

    Complexity O(n) (Expected running time)
    Tested: opencup 010376(Stars in a Can)

    Note: Something went wrong when random_shuffle was applied.
    If random_shuffle is removed complexity might increase
    to O(n^3)
*/
struct circle{
    point center;
    double r;

    bool contain(point &p){
        return abs(center - p) < r + eps;
    }
};

circle min_circle(vector<point> &cloud, int a, int b){
    point center = (cloud[a] + cloud[b]) / double(2.);
    double rat = abs(center - cloud[a]);
    circle C = {center, rat};

    for (int i = 0; i < b; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        center = three_point_circle( cloud[a], cloud[b], cloud[i] );
        rat = abs(center - cloud[a]);
        C = {center, rat};
    }
    return C;
}

circle min_circle(vector<point> &cloud, int a){
    point center = (cloud[a] + cloud[0]) / double(2.);
    double rat = abs(center - cloud[a]);
    circle C = {center, rat};

    for (int i = 0; i < a; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        C = min_circle(cloud, a, i);
    }

    return C;
}

circle min_circle(vector<point> cloud){
    // random_shuffle(cloud.begin(), cloud.end());

    int n = (int)cloud.size();

    for (int i = 1; i < n; ++i){
        int u = rand() % i;
        swap(cloud[u], cloud[i]);
    }

    point center = (cloud[0] + cloud[1]) / double(2.);
    double rat = abs(center - cloud[0]);
    circle C = {center, rat};
    for (int i = 2; i < n; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        C = min_circle(cloud, i);
    }
    return C;
}