// https://codeforces.com/gym/105884/problem/C
#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
using ftype = ll;
const double eps = 1e-9;
const double PI = acos((double)-1.0);
int sign(double x) { return (x > eps) - (x < -eps);}

struct P {
    ftype x, y;
    P() {}
    P(ftype x, ftype y): x(x), y(y) {}
    void read() {
        cin >> x >> y;
    }

    P& operator+=(const P &t) { x += t.x; y += t.y; return *this; }
    P& operator-=(const P &t) { x -= t.x; y -= t.y; return *this; }
    P& operator*=(ftype t) { x *= t; y *= t; return *this; }
    P& operator/=(ftype t) { x /= t; y /= t; return *this; }

    P operator+(const P &t) const { return P(*this) += t; }
    P operator-(const P &t) const { return P(*this) -= t; }
    P operator*(ftype t) const { return P(*this) *= t; }
    P operator/(ftype t) const { return P(*this) /= t; }

    bool operator == (P a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (P a) const { return !(*this == a); }
    bool operator < (P a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (P a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    P perp() const { return P(y, -x); } // 90° rotation clockwise Or P(y, -x) depending on the desired direction.
};

P operator*(ftype a, P b) {return b * a;}
inline ftype dot(P a, P b) {return a.x * b.x + a.y * b.y;}
inline ftype cross(P a, P b) {return a.x * b.y - a.y * b.x;}
ftype norm(P a) {return dot(a, a);}
double abs(P a) {return sqrt(norm(a));}
double proj(P a, P b) {return dot(a, b) / abs(b);}
double angle(P a, P b) {return acos(dot(a, b) / abs(a) / abs(b));}
P intersect(P a1, P d1, P a2, P d2) {return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;}

bool pointInTriangle(P a, P b, P c, P p) {
    ftype s1 = cross(b - a, p - a);
    ftype s2 = cross(c - b, p - b);
    ftype s3 = cross(a - c, p - c);
    return (s1 > 0 && s2 > 0 && s3 > 0) || (s1 < 0 && s2 < 0 && s3 < 0);
}
vector<P> ConvexHull(const vector<P> &_points, int n) {
    vector<P> hull, points;
    points = _points;
    sort(points.begin(), points.end());
    for(int rep = 0; rep < 2; rep++) {
        const int h = (int)hull.size();
        for(auto C : points) {
            while((int)hull.size() - h >= 2) {
                P A = hull[(int)hull.size()-2];
                P B = hull[(int)hull.size()-1];
                if(cross(B-A, C-A) <= 0) {
                    break;
                }
                hull.pop_back();
            }
            hull.push_back(C);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }
    return hull;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<P> points;
        map<P, int> id;
        for(int i = 0; i < n; i++) {
            P p;
            int x, y;
            cin >> x >> y;
            p.x = x;
            p.y = y;
            points.push_back(p);
            id[p] = i+1;
        }
        auto hull = ConvexHull(points, n);
        if(hull.size() == n) {
          cout << "-1\n"; 
          continue;
        }
        map<P, bool> check;
        for(auto p : hull) {
          check[p] = true;
        }
        int m = hull.size();
        for(auto p : points) {
          if(!check[p]) {
            bool ok = true;
            for(int i = 0; i < m && ok; i++) {
              for(int j = 0; j < m; j++) {
                int l = j, r = (j + 1) % m;
                if(i == l || i == r)continue;
                if(pointInTriangle(hull[i], hull[l], hull[r], p)) {
                  cout << id[p] << " " << id[hull[i]] << " " << id[hull[l]] << " " << id[hull[r]] << "\n";
                  ok = false;
                  break;
                }
              }
            }
            break;
          }
        }
    }
    return 0;
}