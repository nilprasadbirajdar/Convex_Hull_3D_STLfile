// #include <iostream>
// #include <vector>
// #include <fstream>
// #include <algorithm>
// using namespace std;

// struct Point3D {
//     int x, y, z;
//     Point3D(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
// };

// int orientation(Point3D p, Point3D q, Point3D r) {
//     int val = (q.y - p.y) * (r.z - q.z) - (q.z - p.z) * (r.y - q.y);
//     if (val == 0) {
//         val = (q.z - p.z) * (r.x - q.x) - (q.x - p.x) * (r.z - q.z);
//         if (val == 0) {
//             val = (q.x - p.x) * (r.y - q.y) - (q.y - p.y) * (r.x - q.x);
//         }
//     }
//     if (val == 0) return 0;
//     return (val > 0) ? 1 : -1;
// }

// int pointToSegmentDist(Point3D A, Point3D B, Point3D P) {
//     int ABx = B.x - A.x;
//     int ABy = B.y - A.y;
//     int ABz = B.z - A.z;
//     int APx = P.x - A.x;
//     int APy = P.y - A.y;
//     int APz = P.z - A.z;

//     int d1 = ABx * APx + ABy * APy + ABz * APz;
//     if (d1 <= 0) return (APx * APx + APy * APy + APz * APz);

//     int BPx = P.x - B.x;
//     int BPy = P.y - B.y;
//     int BPz = P.z - B.z;

//     int d2 = ABx * BPx + ABy * BPy + ABz * BPz;
//     if (d2 >= 0) return (BPx * BPx + BPy * BPy + BPz * BPz);

//     int cx = APy * ABz - APz * ABy; //cross product hai
//     int cy = APz * ABx - APx * ABz;
//     int cz = APx * ABy - APy * ABx;

//     return (cx * cx + cy * cy + cz * cz);
// }

// void findHull(Point3D A, Point3D B, vector<Point3D>& points, vector<Point3D>& convex_hull) {
//     int n = points.size();
//     if (n == 0) return;
//     int farthest = -1;
//     int max_dist = 0;

//     for (int i = 0; i < n; i++) {
//         int dist = pointToSegmentDist(A, B, points[i]);
//         if (dist > max_dist) {
//             max_dist = dist;
//             farthest = i;
//         }
//     }
//     if (farthest == -1){
//         return;
//     } 

//     Point3D C = points[farthest];
//     vector<Point3D> left_set, right_set;

//     for (int i = 0; i < n; i++) {

//         if (orientation(A, C, points[i]) == 1) left_set.push_back(points[i]);
//         if (orientation(C, B, points[i]) == -1) right_set.push_back(points[i]);
//     }
    
//     convex_hull.push_back(C);
//     cout<<C.x<<" "<<C.y<<" "<<C.z<<endl;
//     findHull(A, C, left_set, convex_hull);
//     findHull(C, B, right_set, convex_hull);
//     // convex_hull.push_back(C);
// }

// vector<Point3D> convexHull3D(vector<Point3D>& points) {
//     int n = points.size();
//     if (n < 4) {
//         cout << "Convex hull not possible with less than 4 points" << endl;
//         return vector<Point3D>();
//     }

//     int min_x = 0, max_x = 0;
//     for (int i = 1; i < n; i++) {
//         if (points[i].x < points[min_x].x) min_x = i;
//         if (points[i].x > points[max_x].x) max_x = i;
//     }

//     Point3D A = points[min_x];
//     Point3D B = points[max_x];

//     vector<Point3D> convex_hull;
//     convex_hull.push_back(A);
//     convex_hull.push_back(B);

//     vector<Point3D> left_set, right_set;

//     for (int i = 0; i < n; i++) {
//         if (orientation(A, B, points[i]) == 1) left_set.push_back(points[i]);
//         if (orientation(A, B, points[i]) == -1) right_set.push_back(points[i]);
//     }

//     findHull(A, B, left_set, convex_hull);
//     findHull(B, A, right_set, convex_hull);

//     return convex_hull;
// }

// int main() {
//     vector<Point3D> points;
//     ifstream inputFile("D:\\Projects\\STL_GNUPLOT\\output\\unique_point.txt");

//     if (!inputFile.is_open()) {
//         cerr << "Error opening the input file." << endl;
//         return 1;
//     }

//     double x, y, z;
//     while (inputFile >> x >> y >> z) {
//         points.push_back(Point3D(x, y, z));
//     }
//     //cout<<points.size()<<endl;
//     inputFile.close();

//     vector<Point3D> convex_hull = convexHull3D(points);

//     if (convex_hull.empty()) {
//         cout << "Convex hull not possible with the given points." << endl;
//     } else {
//         for (const Point3D& p : convex_hull) {
//             cout << p.x << " " << p.y << " " << p.z <<endl;
//         }
//     }

//     return 0;
// }
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long double ftype;

struct pt3 {
    ftype x, y, z;
    pt3(ftype x = 0, ftype y = 0, ftype z = 0) : x(x), y(y), z(z) {}
    pt3 operator-(const pt3 &o) const {
        return pt3(x - o.x, y - o.y, z - o.z);
    }
    pt3 cross(const pt3 &o) const {
        return pt3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    ftype dot(const pt3 &o) const {
        return x * o.x + y * o.y + z * o.z;
    }
};

struct face {
    int a, b, c;
    pt3 q;
};

const ftype EPS = 1e-9;

vector<face> hull3(const vector<pt3> &p) {
    int n = p.size();
    assert(n >= 3);
    vector<face> f;
    vector<vector<bool>> dead(n, vector<bool>(n, true));

    auto add_face = [&](int a, int b, int c) {
        f.push_back({a, b, c, (p[b] - p[a]).cross(p[c] - p[a])});
        dead[a][b] = dead[b][c] = dead[c][a] = false;
    };

    add_face(0, 1, 2);
    add_face(0, 2, 1);

    for (int i = 3; i < n; i++) {
        vector<face> f2;
        for (face &F : f) {
            if ((p[i] - p[F.a]).dot(F.q) > EPS) {
                dead[F.a][F.b] = dead[F.b][F.c] = dead[F.c][F.a] = true;
            } else {
                f2.push_back(F);
            }
        }

        f.clear();
        for (face &F : f2) {
            int arr[3] = {F.a, F.b, F.c};
            for (int j = 0; j < 3; j++) {
                int a = arr[j], b = arr[(j + 1) % 3];
                if (dead[b][a]) {
                    add_face(b, a, i);
                }
            }
        }

        f.insert(f.end(), f2.begin(), f2.end());
    }

    return f;
}

int main() {
    ifstream input("D:\\Projects\\STL_GNUPLOT\\output\\unique_point.txt");  // Open the input file containing points
    if (!input.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    vector<pt3> points;
    ftype x, y, z;

    while (input >> x >> y >> z) {
        points.emplace_back(x, y, z);
    }
    cout << points.size()<<endl;
    input.close();  // Close the input file

    vector<face> convexHull = hull3(points);

    cout << "Points on the Convex Hull:" << endl;
    for (const face &f : convexHull) {
        cout << points[f.a].x << " " << points[f.a].y << " " << points[f.a].z << endl;
        cout << points[f.b].x << " " << points[f.b].y << " " << points[f.b].z << endl;
        cout << points[f.c].x << " " << points[f.c].y << " " << points[f.c].z << endl;
    }

    return 0;
}
