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

class DST {
private:
    int N, K;
    int neutral = 0;

    vector<vector<int>> Stable;
    vector<int> highestBit;
    vector<int> a;

    int Function(int left, int right) {
        return max(left, right);
    }
public:
    DST(const vector<int>& vec) {
        for (auto p : vec) {
            a.push_back(p);
        }

        this->K = 0;

        int n = (int)vec.size();
        int p = 1;
        while (p < n) {
            p <<= 1;
            ++(this->K);
        }

        for (int i = 0; i < p - n; i++) {
            a.push_back(neutral);
        }

        this->N = (int)a.size();

        highestBit.resize(N);
        highestBit[0] = 0;
        highestBit[1] = 0;
        for (int i = 2; i < N; i++) {
            highestBit[i] = highestBit[i >> 1] + 1;
        }

        Stable.resize(N);
        for (int i = 0; i < N; i++) {
            Stable[i].resize(K);
            Stable[i][0] = a[i];
        }

        int sz = 1;
        for (int lvl = 1; lvl < K; lvl++) {
            sz = sz <<= 1;
            for (int c = sz; c < N; c += sz << 1) {
                Stable[c][lvl] = a[c];
                for (int i = c + 1; i < c + sz; i++) {
                    Stable[i][lvl] = Function(Stable[i - 1][lvl], a[i]);
                }

                Stable[c - 1][lvl] = a[c - 1];
                for (int i = c - 2; i >= c - sz; i--) {
                    Stable[i][lvl] = Function(a[i], Stable[i + 1][lvl]);
                }
            }
        }
    }

    int query(int left, int right) {
        if (left == right) {
            return a[left];
        }
        else {
            int lvl = highestBit[left ^ right];
            return Function(Stable[left][lvl], Stable[right][lvl]);
        }
    }
};

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int m; cin >> m;
    vector<int> x(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i];
    }

    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) {
            cout << "NO\n";
            return;
        }
    }

    map<int, vector<int>> positions;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            positions[b[i]].push_back(i);
        }
    }

    map<int, int> M;
    for (int i = 0; i < m; i++) {
        M[x[i]] += 1;
    }

    DST dst(b);

    for (auto l_pos : positions) {
        int l = l_pos.first;
        vector<int> pos = l_pos.second;

        int k = M[l];

        k -= 1;
        for (int i = 0; i < pos.size() - 1; i++) {
            int p1 = pos[i];
            int p2 = pos[i + 1];

            if (dst.query(p1, p2) > l) {
                k -= 1;
            }
        }

        if (k < 0) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
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
