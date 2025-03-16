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

#pragma GCC optimize("Ofast") 
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

int C[10][105];
int Current_sloy[65][65];
int Next_sloy[65][65];

bool OK(int mask1, int mask2, int mask3, int n) {
    for (int i = 1; i < n; i++) {
        if ((mask2 & (1 << i))) {
            if
            (
                (mask1 & (1 << i)) &&
                (mask3 & (1 << i)) &&
                (mask2 & (1 << (i - 1))) &&
                (mask2 & (1 << (i + 1)))
            )
            {
                return false;
            }
        }
    }
    return true;
}

int GetSum(int j, int mask, int n) {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) {
            ans += C[i][j];
        }
    }
    return ans;
};

void Solve() {
    int n, m; cin >> n >> m;

    int S = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> C[i][j];
            S += C[i][j];
        }
    } if (n <= 2 || m <= 2) { cout << S; return; }

    // ------------------------------ //

    int ans = 0;

    for (int mask1 = 0; mask1 < (1 << n); mask1++) {
        for (int mask2 = 0; mask2 < (1 << n); mask2++) {
            Current_sloy[mask1][mask2] = GetSum(0, mask1, n) + GetSum(1, mask2, n);
            Next_sloy[mask1][mask2] = 0;
        }
    }

    for (int i = 1; i < m - 1; i++) {
        for (int mask1 = 0; mask1 < (1 << n); mask1++) {
            for (int mask2 = 0; mask2 < (1 << n); mask2++) {
                for (int mask3 = 0; mask3 < (1 << n); mask3++) {
                    if (OK(mask1, mask2, mask3, n)) {
                        Next_sloy[mask2][mask3] = max(Next_sloy[mask2][mask3], 
                            Current_sloy[mask1][mask2] + GetSum(i + 1, mask3, n));
                    }
                    ans = max(ans, Next_sloy[mask2][mask3]);
                }
            }
        }
        for (int mask2 = 0; mask2 < (1 << n); mask2++) {
            for (int mask3 = 0; mask3 < (1 << n); mask3++) {
                Current_sloy[mask2][mask3] = Next_sloy[mask2][mask3];
                Next_sloy[mask2][mask3] = 0;
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
　 　　　／ミ _x 彡       |   WA 2   |
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
