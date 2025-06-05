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
    int n; cin >> n;

    vector<int> a, s;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
        if (ai == 1) {
            s.push_back(i + 1);
        }
        else {
            continue;
        }
    }

    int total_pairs = (n - s.size()) * (n - s.size() - 1) / 2;
    int max_cost = n * (n - 1) / 2;

    if (s.size() == 0) {
        for (int k = 0; k <= max_cost; k++) {
            cout << 0 << ' ';
        }
        return;
    }

    vector<vector<int>> dp_prev(n + 1, vector<int>(max_cost + 1, inf));

    for (int new_pos = 1; new_pos <= n; new_pos++) {
        if (abs(new_pos - s[0]) > max_cost) {
            continue;
        }

        if (new_pos - 1 >= 2) {
            dp_prev[new_pos][abs(new_pos - s[0])] = (new_pos - 1) * (new_pos - 1 - 1) / 2;
        }
        else {
            dp_prev[new_pos][abs(new_pos - s[0])] = 0;
        }
    }

    for (int idx = 1; idx < s.size(); idx++) {
        vector<vector<int>> dp_next(n + 1, vector<int>(max_cost + 1, inf));

        for (int pos_prev = 1; pos_prev <= n; pos_prev++) {
            for (int new_pos = pos_prev + 1; new_pos <= n; new_pos++) {
                int cost_move = abs(new_pos - s[idx]);

                int add;
                if (new_pos - pos_prev - 1 >= 2) {
                    add = (new_pos - pos_prev - 1) * (new_pos - pos_prev - 1 - 1) / 2;
                }
                else {
                    add = 0;
                }

                for (int cost_prev = 0; cost_prev <= max_cost; cost_prev++) {
                    if (dp_prev[pos_prev][cost_prev] == inf) {
                        continue;
                    }

                    int cost_new = cost_prev + cost_move;

                    if (cost_new > max_cost) {
                        continue;
                    }

                    int new_value = dp_prev[pos_prev][cost_prev] + add;

                    if (new_value < dp_next[new_pos][cost_new]) {
                        dp_next[new_pos][cost_new] = new_value;
                    }
                }
            }
        }

        dp_prev = move(dp_next);
    }

    vector<int> min_total(max_cost + 1, inf);
    for (int pos = 1; pos <= n; pos++) {
        int add_last;
        if (n - pos >= 2) {
            add_last = (n - pos) * (n - pos - 1) / 2;
        }
        else {
            add_last = 0;
        }

        for (int cost = 0; cost <= max_cost; cost++) {
            if (dp_prev[pos][cost] == inf) {
                continue;
            }

            int total_val = dp_prev[pos][cost] + add_last;

            if (total_val < min_total[cost]) {
                min_total[cost] = total_val;
            }
        }
    }

    vector<int> min_total_up_to(max_cost + 1, inf);
    int current_min = inf;
    for (int k = 0; k <= max_cost; k++) {
        if (min_total[k] < current_min) {
            current_min = min_total[k];
        }
        min_total_up_to[k] = current_min;
    }

    for (int k = 0; k <= max_cost; k++) {
        cout << total_pairs - min_total_up_to[k] << ' ';
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
