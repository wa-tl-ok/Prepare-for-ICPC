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

struct Block {
    int S;
    vector<int> P;
};

void Solve() {
    int n; cin >> n;
    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }

    vector<Block> ALL;

    int cur_S = 0;
    vector<int> cur_P;

    for (int i = 0; i < 2 * n; i++) {
        if (cur_P.size() == 0) {
            cur_S += 1;
            cur_P.push_back(a[i]);
        }
        else {
            if (a[i] < cur_P[0]) {
                cur_S += 1;
                cur_P.push_back(a[i]);
            }
            else {
                Block b;
                b.S = cur_S;
                b.P = cur_P;
                ALL.push_back(b);

                cur_S = 1;
                cur_P = { a[i] };
            }
        }
    }

    Block b;
    b.S = cur_S;
    b.P = cur_P;
    ALL.push_back(b);

    int N = ALL.size();
    int M = n;

    vector<vector<bool>> DP(M + 1);
    for (int i = 0; i <= M; i++) {
        DP[i].resize(N + 1);
    }

    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= N; j++) {
            DP[i][j] = false;
        }
    }

    for (int i = 0; i <= N; i++) {
        DP[0][i] = true;
    }

    vector<vector<char>> Go(M + 1);
    for (int i = 0; i <= M; i++) {
        Go[i].resize(N + 1);
    }

    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= N; j++) {
            Go[i][j] = '.';
        }
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            DP[i][j] = DP[i][j - 1];

            if (DP[i][j] == true) {
                Go[i][j] = 'L';
                continue;
            }

            if (i - ALL[j - 1].S >= 0 && DP[i - ALL[j - 1].S][j - 1] == true) {
                DP[i][j] = DP[i - ALL[j - 1].S][j - 1];
                Go[i][j] = 'U';
            }
        }
    }

    int i = M;
    int j = N;

    if (DP[i][j] == false) {
        cout << -1;
        return;
    }

    deque<int> A;

    while (i > 0 || j > 0) {
        if (j == 0) {
            i -= 1;
        }
        else if (i == 0) {
            j -= 1;
        }
        else {
            if (Go[i][j] == 'U') {
                i -= ALL[j - 1].S;
                A.push_front(j - 1);
                j -= 1;
            }
            else {
                j -= 1;
            }
        }
    }

    vector<bool> used(ALL.size(), false);
    for (int i = 0; i < A.size(); i++) {
        used[A[i]] = true;
    }

    deque<int> B;
    for (int i = 0; i < ALL.size(); i++) {
        if (used[i] == false) {
            B.push_back(i);
        }
    }

    for (auto id : A) {
        vector<int> v = ALL[id].P;
        for (auto e : v) {
            cout << e << ' ';
        }
    }

    cout << endl;

    for (auto id : B) {
        vector<int> v = ALL[id].P;
        for (auto e : v) {
            cout << e << ' ';
        }
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
