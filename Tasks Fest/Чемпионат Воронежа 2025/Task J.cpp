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
    const int MAX_A = 26;
    const int MAX_N = 100;
    vector<vector<int>> comb(MAX_N + 1, vector<int>(MAX_N + 1, 0));

    for (int i = 0; i <= MAX_N; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            if (comb[i][j] > 1e18) {
                comb[i][j] = 1e18;
            }
        }
    }

    string g; cin >> g;
    if (g == "encode") {
        int x, y; cin >> x >> y;
        int xy = (x - 1) * 1'000'000'000 + (y - 1);

        int k = 0;
        int sum = 0;

        while (true) {
            int sum_new_k = comb[MAX_A + k][k + 1];

            if (sum + sum_new_k > xy) {
                break;
            }

            sum += sum_new_k;
            k++;
        }

        int rem = xy - sum;

        int tk = k + 1;
        vector<int> indices;
        int cur = 0;

        for (int i = 0; i < tk; i++) {
            while (true) {
                int cnt = comb[MAX_A - cur + tk - i - 1 - 1][tk - i - 1];

                if (cnt > rem || cnt == 0) {
                    break;
                }

                rem -= cnt;
                cur++;
            }

            indices.push_back(cur);
        }

        string s;
        for (int idx : indices) {
            s += 'a' + idx;
        }

        cout << s;
    }
    else {
        string s; cin >> s;
        sort(s.begin(), s.end());
        vector<int> indices;
        for (char c : s) {
            indices.push_back(c - 'a');
        }

        int rank = 0;
        int cur = 0;
        int sz = indices.size();

        for (int elem : indices) {
            for (int c = cur; c < elem; c++) {
                if (MAX_A <= c) {
                    continue;
                }

                rank += comb[MAX_A - c + sz - 1 - 1][sz - 1];
            }

            cur = elem;
            sz--;
        }

        int sum = 0;
        for (int i = 1; i < indices.size(); i++) {
            sum += comb[MAX_A + i - 1][i];
        }

        int xy = sum + rank;

        int x = xy / 1'000'000'000 + 1;
        int y = xy % 1'000'000'000 + 1;

        cout << x << ' ' << y;
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
