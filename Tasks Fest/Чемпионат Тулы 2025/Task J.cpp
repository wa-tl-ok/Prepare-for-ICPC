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

int x_val, y_val;

int count_sec(int mask) {
    return __builtin_popcount(mask);
}

bool check(int col, int left_col, int curr_col, int right_col, int k, int x, int y) {
    for (int row = 0; row < 2; row++) {
        int s = (curr_col >> row) & 1;
        int count_s1 = 0;
        int count_c1 = 0;

        if (col > 0) {
            if ((left_col >> row) & 1) {
                count_s1++;
            }
            else {
                count_c1++;
            }
        }

        if (col + 1 < k) {
            if ((right_col >> row) & 1) {
                count_s1++;
            }
            else {
                count_c1++;
            }
        }

        if ((curr_col >> (1 - row)) & 1) {
            count_s1++;
        }
        else {
            count_c1++;
        }

        if (s == 1) {
            if (x != -1 && count_s1 != x) {
                return false;
            }
            if (y != -1 && count_c1 != y) {
                return false;
            }
        }
        else {
            bool told_truth_x = (x == -1) || (count_s1 == x);
            bool told_truth_y = (y == -1) || (count_c1 == y);
            if (told_truth_x && told_truth_y) {
                return false;
            }
        }
    }

    return true;
}

struct Node {
    int total;
    tuple<int, int, int> parent_key;
    bool has_parent;

    Node() : total(0), has_parent(false) {}
    Node(int t) : total(t), has_parent(false) {}
    Node(int t, tuple<int, int, int> par) : total(t), parent_key(par), has_parent(true) {}
};

void Solve() {
    int k; cin >> k >> x_val >> y_val;

    vector<map<tuple<int, int, int>, Node>> dp_min_all(k);
    vector<map<tuple<int, int, int>, Node>> dp_max_all(k);

    for (int mask = 0; mask < 4; mask++) {
        tuple<int, int, int> key = make_tuple(0, 0, mask);
        dp_min_all[0][key] = Node(count_sec(mask));
        dp_max_all[0][key] = Node(count_sec(mask));
    }

    if (k > 1) {
        for (int j = 1; j < k; j++) {
            map<tuple<int, int, int>, Node> dp_min_curr;
            map<tuple<int, int, int>, Node> dp_max_curr;

            for (int mask_pp = 0; mask_pp < 4; mask_pp++) {
                for (int mask_p = 0; mask_p < 4; mask_p++) {
                    for (int mask_c = 0; mask_c < 4; mask_c++) {
                        int left_col_val;
                        if (j > 1) {
                            left_col_val = mask_pp;
                        }
                        else {
                            left_col_val = 0;
                        }

                        if (check(j - 1, left_col_val, mask_p, mask_c, k, x_val, y_val) == false) {
                            continue;
                        }

                        int total_here = count_sec(mask_c);
                        int best_min = INT_MAX;
                        int best_max = INT_MIN;

                        tuple<int, int, int> best_min_parent_key;
                        tuple<int, int, int> best_max_parent_key;

                        bool found_min = false;
                        bool found_max = false;

                        for (const auto& entry : dp_min_all[j - 1]) {
                            auto key_prev = entry.first;

                            int pp_prev = get<0>(key_prev);
                            int p_prev = get<1>(key_prev);
                            int c_prev = get<2>(key_prev);

                            if (p_prev == mask_pp && c_prev == mask_p) {
                                int total_prev = entry.second.total;
                                int total_all = total_prev + total_here;

                                if (total_all < best_min) {
                                    best_min = total_all;
                                    best_min_parent_key = key_prev;
                                    found_min = true;
                                }
                            }
                        }

                        for (const auto& entry : dp_max_all[j - 1]) {
                            auto key_prev = entry.first;

                            int pp_prev = get<0>(key_prev);
                            int p_prev = get<1>(key_prev);
                            int c_prev = get<2>(key_prev);

                            if (p_prev == mask_pp && c_prev == mask_p) {
                                int total_prev = entry.second.total;
                                int total_all = total_prev + total_here;

                                if (total_all > best_max) {
                                    best_max = total_all;
                                    best_max_parent_key = key_prev;
                                    found_max = true;
                                }
                            }
                        }

                        if (found_min) {
                            tuple<int, int, int> key_curr = make_tuple(mask_pp, mask_p, mask_c);
                            dp_min_curr[key_curr] = Node(best_min, best_min_parent_key);
                        }

                        if (found_max) {
                            tuple<int, int, int> key_curr = make_tuple(mask_pp, mask_p, mask_c);
                            dp_max_curr[key_curr] = Node(best_max, best_max_parent_key);
                        }
                    }
                }
            }

            if (dp_min_curr.empty()) {
                cout << -1 << endl;
                return;
            }

            dp_min_all[j] = dp_min_curr;
            dp_max_all[j] = dp_max_curr;
        }
    }

    int min_total = INT_MAX;
    tuple<int, int, int> min_key;

    int max_total = INT_MIN;
    tuple<int, int, int> max_key;

    if (k == 1) {
        for (const auto& entry : dp_min_all[0]) {
            auto key = entry.first;
            int mask_c = get<2>(key);

            if (!check(0, 0, mask_c, 0, k, x_val, y_val) == false) {
                continue;
            }

            if (entry.second.total < min_total) {
                min_total = entry.second.total;
                min_key = key;
            }

            if (dp_max_all[0].at(key).total > max_total) {
                max_total = dp_max_all[0].at(key).total;
                max_key = key;
            }
        }
    }
    else {
        for (const auto& entry : dp_min_all[k - 1]) {
            auto key = entry.first;

            int mask_pp = get<0>(key);
            int mask_p = get<1>(key);
            int mask_c = get<2>(key);

            if (check(k - 1, mask_p, mask_c, 0, k, x_val, y_val) == false) {
                continue;
            }

            if (entry.second.total < min_total) {
                min_total = entry.second.total;
                min_key = key;
            }
        }

        for (const auto& entry : dp_max_all[k - 1]) {
            auto key = entry.first;

            int mask_pp = get<0>(key);
            int mask_p = get<1>(key);
            int mask_c = get<2>(key);

            if (check(k - 1, mask_p, mask_c, 0, k, x_val, y_val) == false) {
                continue;
            }

            if (entry.second.total > max_total) {
                max_total = entry.second.total;
                max_key = key;
            }
        }
    }

    if (min_total == INT_MAX) {
        cout << -1 << endl;
        return;
    }

    cout << min_total << endl;

    vector<int> min_masks;
    tuple<int, int, int> cur_key = min_key;
    for (int j = k - 1; j >= 0; j--) {
        min_masks.push_back(get<2>(cur_key));
        if (j > 0) {
            if (j == k - 1) {
                cur_key = dp_min_all[k - 1].at(cur_key).parent_key;
            }
            else {
                cur_key = dp_min_all[j].at(cur_key).parent_key;
            }
        }
    }

    reverse(min_masks.begin(), min_masks.end());

    string row0, row1;
    for (int mask : min_masks) {
        row0 += ((mask & 1) ? '1' : '0');
        row1 += ((mask & 2) ? '1' : '0');
    }

    cout << row0 << endl << row1 << endl;

    cout << max_total << endl;

    vector<int> max_masks;
    cur_key = max_key;
    for (int j = k - 1; j >= 0; j--) {
        max_masks.push_back(get<2>(cur_key));
        if (j > 0) {
            if (j == k - 1) {
                cur_key = dp_max_all[k - 1].at(cur_key).parent_key;
            }
            else {
                cur_key = dp_max_all[j].at(cur_key).parent_key;
            }
        }
    }

    reverse(max_masks.begin(), max_masks.end());

    row0 = "";
    row1 = "";
    for (int mask : max_masks) {
        row0 += ((mask & 1) ? '1' : '0');
        row1 += ((mask & 2) ? '1' : '0');
    }

    cout << row0 << endl << row1 << endl;
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
