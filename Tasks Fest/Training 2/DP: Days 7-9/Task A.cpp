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

int DP[205][205][205];

void Solve() {
    int Red_count, Green_count, Blue_count;
    cin >> Red_count >> Green_count >> Blue_count;

    deque<int> R(Red_count);
    for (int i = 0; i < Red_count; i++) {
        cin >> R[i];
    }
    sort(R.begin(), R.end());
    reverse(R.begin(), R.end());
    R.push_front(0);

    deque<int> G(Green_count);
    for (int i = 0; i < Green_count; i++) {
        cin >> G[i];
    }
    sort(G.begin(), G.end());
    reverse(G.begin(), G.end());
    G.push_front(0);

    deque<int> B(Blue_count);
    for (int i = 0; i < Blue_count; i++) {
        cin >> B[i];
    }
    sort(B.begin(), B.end());
    reverse(B.begin(), B.end());
    B.push_front(0);

    for (int i = 0; i < 205; i++) {
        for (int j = 0; j < 205; j++) {
            for (int k = 0; k < 205; k++) {
                DP[i][j][k] = 0;
            }
        }
    }

    for (int r = 0; r <= Red_count; r++) {
        for (int g = 0; g <= Green_count; g++) {
            for (int b = 0; b <= Blue_count; b++) {
                int F = 0;
                if (r > 0) {
                    F = DP[r - 1][g][b];
                }

                int S = 0;
                if (g > 0) {
                    S = DP[r][g - 1][b];
                }

                int T = 0;
                if (b > 0) {
                    T = DP[r][g][b - 1];
                }

                DP[r][g][b] = max3(F, S, T);

                if (b >= 1 && g >= 1) {
                    DP[r][g][b] = max(DP[r][g][b], DP[r][g - 1][b - 1] + B[b] * G[g]);
                }
                if (r >= 1 && g >= 1) {
                    DP[r][g][b] = max(DP[r][g][b], DP[r - 1][g - 1][b] + R[r] * G[g]);
                }
                if (r >= 1 && b >= 1) {
                    DP[r][g][b] = max(DP[r][g][b], DP[r - 1][g][b - 1] + R[r] * B[b]);
                }
            }
        }
    }

    int ans = 0;

    for (int r = 0; r <= Red_count; r++) {
        for (int g = 0; g <= Green_count; g++) {
            for (int b = 0; b <= Blue_count; b++) {
                ans = max(ans, DP[r][g][b]);
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
