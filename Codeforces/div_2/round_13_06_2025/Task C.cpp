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

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using max_heap = priority_queue<T>;

#define BIT(n) (1LL << (n))
#define HAS_BIT(x, n) (((x) >> (n)) & 1)
#define SET_BIT(x, n) ((x) | BIT(n))

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

int get(vector<int>& ps, int l, int r) {
    if (l == 0) {
        return ps[r];
    }
    return ps[r] - ps[l - 1];
}

void Solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        if (a[i] <= k) {
            a[i] = 1;
        }
        else {
            a[i] = -1;
        }
    }

    vector<int> ps(n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += a[i];
        ps[i] = s;
    }

    // neg pos pos

    int s1 = 0;
    int s2 = 0;
    int s3 = 0;

    int w0 = -1;
    int w1 = -1;

    for (int i = n - 1; i >= 2; i--) {
        s3 += a[i];
        s1 = 0;
        s2 = 0;

        if (s3 == 0 && w0 == -1) {
            for (int j = i - 1; j >= 1; j--) {
                s2 += a[j];

                if (s2 >= 0) {
                    cout << "YES\n";
                    return;
                }
            }

            w0 = 1;
        }

        if (s3 == 1 && w1 == -1) {
            for (int j = i - 1; j >= 1; j--) {
                s2 += a[j];

                if (s2 >= 0) {
                    cout << "YES\n";
                    return;
                }
            }

            w1 = 1;
        }
    }

    // pos pos neg

    int ss1 = 0;
    int ss2 = 0;
    int ss3 = 0;

    int ww0 = -1;
    int ww1 = -1;

    for (int i = 0; i < n - 2; i++) {
        ss1 += a[i];
        ss2 = 0;
        ss3 = 0;

        if (ss1 == 0 && ww0 == -1) {
            for (int j = i + 1; j < n - 1; j++) {
                ss2 += a[j];

                if (ss2 >= 0) {
                    cout << "YES\n";
                    return;
                }
            }

            ww0 = 1;
        }

        if (ss1 == 1 && ww1 == -1) {
            for (int j = i + 1; j < n - 1; j++) {
                ss2 += a[j];

                if (ss2 >= 0) {
                    cout << "YES\n";
                    return;
                }
            }

            ww1 = 1;
        }
    }

    // pos neg pos

    int sss1 = 0;
    int sss2 = 0;
    int sss3 = 0;

    int l = -1;
    int r = -1;

    for (int i = 0; i < n; i++) {
        sss1 += a[i];

        if (sss1 >= 0) {
            l = i;
            break;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        sss3 += a[i];

        if (sss3 >= 0) {
            r = i;
            break;
        }
    }

    if (l != -1 && r != -1 && l < r) {
        if (l + 1 != r) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
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
    freopen("task.in", "r", stdin);
    freopen("task.out", "w", stdout);
    */

    // auto start = chrono::high_resolution_clock::now();

    int multitest = true;
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
