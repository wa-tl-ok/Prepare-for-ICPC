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
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    int m = 10'000;

    vector<vector<int>> DP(m + 1);
    for (int i = 0; i <= m; i++) {
        DP[i].resize(n + 1);
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            DP[i][j] = 0;
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            DP[i][j] = max(DP[i][j], DP[i][j - 1]);

            int A = a[j - 1].first;
            int B = a[j - 1].second;
            int jump = 0;
            int plus = 0;

            while (true) {
                if (A == 1 && B == 1) {
                    A -= 1;
                    B -= 1;
                    jump += 1;
                    plus += 2;
                }
                else {
                    if (A < B) {
                        A -= 0;
                        B -= 1;
                        jump += A;
                        plus += 1;
                    }
                    else {
                        A -= 1;
                        B -= 0;
                        jump += B;
                        plus += 1;
                    }
                }

                if (jump <= i) {
                    DP[i][j] = max(DP[i][j], DP[i - jump][j - 1] + plus);
                }

                if (jump > i || (A == 0 && B == 0)) {
                    break;
                }
            }

            if (DP[i][j] >= k) {
                cout << i << '\n';
                return;
            }
        }
    }
    
    cout << -1 << '\n';
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
