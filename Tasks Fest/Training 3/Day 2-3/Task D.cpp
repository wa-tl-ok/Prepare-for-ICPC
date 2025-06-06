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

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> DP(n);
    for (int i = 0; i < n; i++) {
        DP[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            DP[i][j] = 1e18;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                DP[i][j] = 1;
            }

            if (i > j) {
                DP[i][j] = 0;
            }
        }
    }

    for (int D = 0; D < n; D++) {
        for (int i = 0; i < n - D; i++) {
            int j = i + D;

            if (i != 0) {
                DP[i - 1][j] = min(DP[i - 1][j], DP[i][j] + 1);

                int ans = 1e18;
                if (a[i - 1] == a[i]) {
                    if (i != n - 1) {
                        ans = 1 + DP[i + 1][j];
                    }
                    else {
                        ans = 1;
                    }
                }

                for (int k = i + 1; k <= j; k++) {
                    if (a[k] == a[i - 1]) {
                        if (k != n - 1) {
                            ans = min(ans, DP[i][k - 1] + DP[k + 1][j]);
                        }
                        else {
                            ans = min(ans, DP[i][k - 1] + 0);
                        }
                    }
                }

                DP[i - 1][j] = min(DP[i - 1][j], ans);
            }
            if (j != n - 1) {
                DP[i][j + 1] = min(DP[i][j + 1], DP[i][j] + 1);

                int ans = 1e18;
                if (a[j] == a[j + 1]) {
                    if (j != 0) {
                        ans = 1 + DP[i][j - 1];
                    }
                    else {
                        ans = 1;
                    }
                }

                for (int k = j - 1; k >= i; k--) {
                    if (a[k] == a[j + 1]) {
                        if (k != 0) {
                            ans = min(ans, DP[i][k - 1] + DP[k + 1][j]);
                        }
                        else {
                            ans = min(ans, 0 + DP[k + 1][j]);
                        }
                    }
                }

                DP[i][j + 1] = min(DP[i][j + 1], ans);
            }
        }
    }

    cout << DP[0][n - 1];
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
