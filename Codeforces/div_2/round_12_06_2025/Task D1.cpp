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

void Solve() {
    int n, k; cin >> n >> k;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }

    int q; cin >> q;

    for (int i = 0; i < q; i++) {
        int s; cin >> s;

        vector<bool> vis_from_left(n, false);
        vector<bool> vis_from_right(n, false);

        int t = 0;
        string move = "right";

        string ans = "...";

        bool FFF = false;
        for (int i = 0; i < n; i++) {
            if (s == p[i] && d[i] == 0) {
                FFF = true;
            }
        }

        while (ans == "...") {
            if (move == "right") {
                int ID = -1;
                for (int i = 0; i < n; i++) {
                    if (s < p[i] || (s == p[i] && FFF == true)) {
                        if (t + (p[i] - s) < d[i]) {
                            // pass
                        }
                        else {
                            if ((t + (p[i] - s) - d[i]) % k == 0) {
                                if (vis_from_right[i] == false) {
                                    vis_from_right[i] = true;
                                    ID = i;
                                }
                                else {
                                    ans = "NO";
                                }
                            }
                            else {
                                // pass
                            }
                        }
                    }
                    else {
                        // pass
                    }

                    if (ID != -1) {
                        break;
                    }
                }

                if (ans == "...") {
                    if (ID == -1) {
                        ans = "YES";
                    }
                    else {
                        if (p[ID] - s == 0) {
                            t += 1;
                            s -= 1;
                            move = "left";
                        }
                        else {
                            t += p[ID] - s;
                            s = p[ID];
                            move = "left";
                            FFF = false;
                        }
                    }
                }
            }
            else {
                int ID = -1;
                for (int i = n - 1; i >= 0; i--) {
                    if (s > p[i] || (s == p[i] && FFF == true)) {
                        if (t + (s - p[i]) < d[i]) {
                            // pass
                        }
                        else {
                            if ((t + (s - p[i]) - d[i]) % k == 0) {
                                if (vis_from_left[i] == false) {
                                    vis_from_left[i] = true;
                                    ID = i;
                                }
                                else {
                                    ans = "NO";
                                }
                            }
                            else {
                                // pass
                            }
                        }
                    }
                    else {
                        // pass
                    }

                    if (ID != -1) {
                        break;
                    }
                }

                if (ans == "...") {
                    if (ID == -1) {
                        ans = "YES";
                    }
                    else {
                        if (p[ID] - s == 0) {
                            t += 1;
                            s += 1;
                            move = "right";
                        }
                        else {
                            t += s - p[ID];
                            s = p[ID];
                            move = "right";
                            FFF = false;
                        }
                    }
                }
            }
        }

        cout << ans << '\n';
    }
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
