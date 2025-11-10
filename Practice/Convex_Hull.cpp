// https://lightoj.com/problem/guarding-bananas

#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
using ftype = ll;
#define double long double
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
    P& operator+=(const P &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    P& operator-=(const P &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    P& operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    P& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    P operator+(const P &t) const {return P(*this) += t;}
    P operator-(const P &t) const {return P(*this) -= t;}
    P operator*(ftype t) const {return P(*this) *= t;}
    P operator/(ftype t) const {return P(*this) /= t;}
    bool operator == (P a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (P a) const { return !(*this == a); }
    bool operator < (P a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (P a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
};

P operator*(ftype a, P b) {return b * a;}
inline ftype dot(P a, P b) {return a.x * b.x + a.y * b.y;}
inline ftype cross(P a, P b) {return a.x * b.y - a.y * b.x;}
ftype norm(P a) {return dot(a, a);}
double abs(P a) {return sqrt(norm(a));}
double proj(P a, P b) {return dot(a, b) / abs(b);}
double angle(P a, P b) {return acos(dot(a, b) / abs(a) / abs(b));}
P intersect(P a1, P d1, P a2, P d2) {return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;}


void ConvexHull(set<P> &f, int n) {
    vector<P> hull, points;
    for(auto x : f) {
        points.push_back(x);
    }
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
    if(hull.size() <= 2) {
        cout << 0.000 << "\n";
        return;
    }
    double ans = 190.00;
    for(int i = 0; i < (int) hull.size(); i++) {
        int j = i-1;
        int k = i+1;
        if(j == -1)j = (int)hull.size()-1;
        if(k == (int)hull.size()) k = 0;
        double tmp = angle(hull[j]-hull[i], hull[k]-hull[i])*180.0/PI;
        ans = min(ans, tmp);
    }
    cout << fixed << setprecision(12) << ans << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt, cs;
    tt = 1, cs = 1;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        set<P> points;
        for(int i = 0; i < n; i++) {
            P p;
            p.read();
            points.insert(p);
        }
        cout << "Case " << cs++ << ": ";
        ConvexHull(points, n);
    }
    return 0;
}