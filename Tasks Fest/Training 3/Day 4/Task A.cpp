// #define _CRT_SECURE_NO_WARNINGS 

#include <iostream> 
#include <algorithm> 
#include <cmath> 
#include <climits> 
#include <vector> 
#include <queue> 
#include <deque> 
#include <array> 
#include <list> 
#include <stack> 
#include <tuple> 
#include <set> 
#include <unordered_set> 
#include <map> 
#include <unordered_map> 
#include <string> 
#include <cstring> 
#include <random> 
#include <bitset> 
#include <iomanip> 
#include <iterator> 
#include <functional> 
#include <ctime> 
#include <chrono> 
#include <cctype> 
#include <fstream> 
#include <ranges> 
#include <numeric> 
#include <complex> 
#include <cassert> 

using namespace std;

// #pragma GCC optimize("Ofast") 
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define int               long long 
#define sz(x)             ((int)(x).size()) 
#define mp                make_pair 
#define all(x)            (x).begin(), (x).end() 
#define pb                push_back 
#define pf                push_front 
#define ff                first 
#define ss                second 
#define unique(x)         (x).erase(unique(all(x)), (x).end()) 
#define min3(a, b, c)     min(a, min(b, c)) 
#define max3(a, b, c)     max(a, max(b, c)) 
#define FOR(i, a, b)      for (int i = (a); i <= (b); i++) 
#define ROF(i, a, b)      for (int i = (a); i >= (b); i--) 

using vi = vector<int>;
using vd = vector<double>;
using vpii = vector<pair<int, int>>;
using vpdd = vector<pair<double, double>>;
using pii = pair<int, int>;
using pdd = pair<double, double>;

template <typename Container>
void PRINT(const Container& container) {
    for (const auto& e : container) {
        cout << e << ' ';
    } cout << '\n';
}

void print_double(double ans, int num) {
    cout << fixed << setprecision(num) << ans << '\n';
}

const int inf = 1e18;
const double eps = 1e-9;
const double PI = 3.141592653589793;

string alh = "abcdefghijklmnopqrstuvwxyz";
string ALH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct Point {
    int x, y;

    Point(int x_, int y_) {
        x = x_;
        y = y_;
    }
};

int sign(int val) {
    if (val == 0) return 0;
    else if (val > 0) return 1;
    else return 2;
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return sign(val);
}

bool onsegment(Point p, Point q, Point r) {
    return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y));
}

bool FIND(pair<Point, Point> O1, pair<Point, Point> O2) {
    Point p1 = O1.first;
    Point q1 = O1.second;
    Point p2 = O2.first;
    Point q2 = O2.second;

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    if (o1 == 0 && onsegment(p1, p2, q1)) return true;
    if (o2 == 0 && onsegment(p1, q2, q1)) return true;
    if (o3 == 0 && onsegment(p2, p1, q2)) return true;
    if (o4 == 0 && onsegment(p2, q1, q2)) return true;

    return false;
}

struct S {
    vector<Point> P;

    int X1, Y1;
    int X2, Y2;

    S(Point p1, Point p2, Point p3, Point p4) {
        P.push_back(p1);
        P.push_back(p2);
        P.push_back(p3);
        P.push_back(p4);

        X1 = min({ p1.x, p2.x, p3.x, p4.x });
        X2 = max({ p1.x, p2.x, p3.x, p4.x });

        Y1 = min({ p1.y, p2.y, p3.y, p4.y });
        Y2 = max({ p1.y, p2.y, p3.y, p4.y });
    }
};

bool IN(S s1, S s2) {
    for (auto p : s2.P) {
        if (p.x >= s1.X1 && p.x <= s1.X2 && p.y >= s1.Y1 && p.y <= s1.Y2) {
            continue;
        }
        return false;
    }
    return true;
}

bool INN(S s1, S s2) {
    vector<int> cnt(4, 0);
    for (auto p : s2.P) {
        if (p.x > s1.X1 && p.x < s1.X2 && p.y < s1.Y1) {
            cnt[0] = 1;
        }
        if (p.x > s1.X1 && p.x < s1.X2 && p.y > s1.Y2) {
            cnt[1] = 1;
        }
        if (p.x > s1.Y1 && p.x < s1.Y2 && p.y < s1.X1) {
            cnt[2] = 1;
        }
        if (p.x > s1.Y1 && p.x < s1.Y2 && p.y > s1.X2) {
            cnt[3] = 1;
        }
    }
    int su = 0;
    for (auto p : cnt) {
        if (p == 0) {
            ++su;
        }
    }
    if (su == 0) {
        return true;
    }
    return false;
}

void Solve() {
    int x1, y1; cin >> x1 >> y1; Point xy1(x1, y1);
    int x2, y2; cin >> x2 >> y2; Point xy2(x2, y2);
    int x3, y3; cin >> x3 >> y3; Point xy3(x3, y3);
    int x4, y4; cin >> x4 >> y4; Point xy4(x4, y4);

    int u1, v1; cin >> u1 >> v1; Point uv1(u1, v1);
    int u2, v2; cin >> u2 >> v2; Point uv2(u2, v2);
    int u3, v3; cin >> u3 >> v3; Point uv3(u3, v3);
    int u4, v4; cin >> u4 >> v4; Point uv4(u4, v4);

    S s1(xy1, xy2, xy3, xy4);
    S s2(uv1, uv2, uv3, uv4);

    if (IN(s1, s2)) {
        cout << "YES";
        return;
    }
    else if (INN(s1, s2)) {
        cout << "YES";
        return;
    }
    else {
        for (int i = 0; i < 4; i++) {
            int l1 = i;
            int r1 = (i + 1) % 4;
            for (int j = 0; j < 4; j++) {
                int l2 = j;
                int r2 = (j + 1) % 4;
                Point p1 = s1.P[l1];
                Point p2 = s1.P[r1];
                Point p3 = s2.P[l2];
                Point p4 = s2.P[r2];
                if (FIND({ p1, p2 }, { p3, p4 }) == true) {
                    cout << "YES";
                    return;
                }
            }
        }
    }

    cout << "NO";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    /*
                      ________________
                     / Just solved it \
                     |   in my mind   |
                     \________________/
                    /
                   /
　　　　　／＞　 フ         ___________
　　　　　| 　_　 _|       |          |
　 　　　／`ミ _x 彡       |   WA 2   |
　　 　 /　　　 　 |       |__________|
　　　 /　 ヽ　　 ﾉ        /          /
　／￣|　　 |　|　|       /_________ /
　| (￣ヽ＿_ヽ_)_)
　＼二つ

    */

    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */

    // auto start = chrono::high_resolution_clock::now();

    int multitest = false;
    if (multitest == true) {
        int ctt; cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    // auto end = chrono::high_resolution_clock::now();

    /*
    cout << "Time taken: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " milliseconds" << endl;
    */

    return 0;
}
