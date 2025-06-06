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

const int mod = 998244353;

void Solve() {
    int n, p; string s;

    cin >> n >> p;
    cin >> s;
    cin >> s;

    int opens;
    if (s == "unknown") {
        opens = 400;
    }
    else {
        opens = stoll(s);
    }

    vector<int> known(n);
    vector<string> P(n);

    for (int i = 0; i < n; i++) {
        cin >> s;
        cin >> s;
        if (s == "unknown") {
            known[i] = 400;
        }
        else {
            known[i] = stoll(s);
        }
        cin >> P[i];
    }

    int t_size = 1 << p;
    vector<int> F(t_size, 1);

    for (int k = 0; k < n; k++) {
        vector<int> can(t_size, 0);

        for (int mask = 0; mask < t_size; mask++) {
            if (known[k] != 400) {
                if (__builtin_popcount(mask) != known[k]) {
                    continue;
                }
            }
            bool f = true;
            for (int j = 0; j < p; j++) {
                if (mask & (1 << j)) {
                    if (P[k][j] != '+' && P[k][j] != '?') {
                        f = false;
                        break;
                    }
                }
                else {
                    if (P[k][j] != '-' && P[k][j] != '.' && P[k][j] != '?') {
                        f = false;
                        break;
                    }
                }
            }
            if (f) {
                can[mask] = 1;
            }
        }

        vector<int> C = can;
        for (int i = 0; i < p; i++) {
            for (int mask = 0; mask < t_size; mask++) {
                if (mask & (1 << i)) {
                    C[mask] = C[mask] + C[mask ^ (1 << i)];
                    if (C[mask] >= mod) {
                        C[mask] -= mod;
                    }
                }
            }
        }

        for (int mask = 0; mask < t_size; mask++) {
            F[mask] = (F[mask] * C[mask]) % mod;
        }
    }

    vector<int> dp_ = F;
    for (int i = 0; i < p; i++) {
        for (int mask = t_size - 1; mask >= 0; mask--) {
            if (mask & (1 << i)) {
                dp_[mask] = dp_[mask] - dp_[mask ^ (1 << i)];
                if (dp_[mask] < 0) {
                    dp_[mask] += mod;
                }
            }
        }
    }

    int ans = 0;
    for (int mask = 0; mask < t_size; mask++) {
        if (opens == 400 || __builtin_popcount(mask) == opens) {
            ans += dp_[mask];
            if (ans >= mod) {
                ans -= mod;
            }
        }
    }

    cout << ans;
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
