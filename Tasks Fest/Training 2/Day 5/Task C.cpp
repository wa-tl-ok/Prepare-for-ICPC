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

const int inf = 1e16;
const double eps = 1e-9;
const double PI = 3.141592653589793;

string alh = "abcdefghijklmnopqrstuvwxyz";
string ALH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class SegmentTree {
public:
    SegmentTree(int size) {
        n = size;
        int p = 1;
        while (p < n) {
            p *= 2;
        }

        tree.assign(p * 2, inf);
        lazy.assign(p * 2, { 0, false });

        n = p;
    }

    SegmentTree(const vector<int>& a) {
        n = (int)a.size();
        int p = 1;
        while (p < n) {
            p *= 2;
        }

        tree.assign(p * 2, inf);
        lazy.assign(p * 2, { 0, false });

        n = p;

        for (int i = 0; i < (int)a.size(); ++i) {
            updateRange(1, 0, n - 1, i, i, a[i], false);
        }
    }

    void plus(int const_l, int const_r, int val) {
        updateRange(1, 0, n - 1, const_l, const_r, val, true);
    }

    void change(int const_l, int const_r, int val) {
        updateRange(1, 0, n - 1, const_l, const_r, val, false);
    }

    int query(int const_l, int const_r) {
        return queryRange(1, 0, n - 1, const_l, const_r);
    }
private:
    vector<int> tree;
    vector<pair<int, bool>> lazy;
    int n;

    void propagate(int node, int l, int r) {
        if (lazy[node].second) {
            if (lazy[node].first != 0) {
                tree[node] += lazy[node].first;
                if (l != r) {
                    lazy[2 * node].first += lazy[node].first;
                    lazy[2 * node].second = true;
                    lazy[2 * node + 1].first += lazy[node].first;
                    lazy[2 * node + 1].second = true;
                }
            }
        }
        else {
            if (lazy[node].first != 0) {
                tree[node] = lazy[node].first;
                if (l != r) {
                    lazy[2 * node] = lazy[node];
                    lazy[2 * node + 1] = lazy[node];
                }
            }
        }
        lazy[node] = { 0, false };
    }

    void updateRange(int node, int l, int r, int const_l, int const_r, int val, bool isAddition) {
        propagate(node, l, r);
        if (l > r || l > const_r || r < const_l) {
            return;
        }
        if (l >= const_l && r <= const_r) {
            if (isAddition) {
                tree[node] += val;
                if (l != r) {
                    lazy[2 * node].first += val;
                    lazy[2 * node].second = true;
                    lazy[2 * node + 1].first += val;
                    lazy[2 * node + 1].second = true;
                }
            }
            else {
                tree[node] = val;
                if (l != r) {
                    lazy[2 * node] = { val, false };
                    lazy[2 * node + 1] = { val, false };
                }
            }
            return;
        }

        int mid = (l + r) / 2;

        updateRange(2 * node, l, mid, const_l, const_r, val, isAddition);
        updateRange(2 * node + 1, mid + 1, r, const_l, const_r, val, isAddition);

        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    int queryRange(int node, int l, int r, int const_l, int const_r) {
        if (l > r || l > const_r || r < const_l) {
            return inf;
        }

        propagate(node, l, r);

        if (l >= const_l && r <= const_r) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        int p1 = queryRange(2 * node, l, mid, const_l, const_r);
        int p2 = queryRange(2 * node + 1, mid + 1, r, const_l, const_r);

        return min(p1, p2);
    }
};

int bs_rl(vector<int>& arr, int target) {
    /*
        Find min index of number that >= target
    */
    if (arr[arr.size() - 1] < target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

int bs_lr(vector<int>& arr, int target) {
    /*
        Find max index of number that <= target
    */
    if (arr[0] > target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return right;
}

void Solve() {
    int n; cin >> n;
    vector<pair<int, int>> V;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        V.push_back({ a, b });
    }

    sort(V.begin(), V.end(), [](const auto& x, const auto& y) {
        if (y.ss > x.ss)
            return false;
        if (y.ss < x.ss)
            return true;
        return x.ff < y.ff;
        });

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = V[i].ff;
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = V[i].ss;
    }

    set<int> A;
    for (auto ai : a) {
        A.insert(ai);
    }

    unordered_map<int, int> cntA;
    for (auto ai : a) {
        cntA[ai] += 1;
    }

    unordered_map<int, int> pos;
    int tt = 0;
    for (auto ai : A) {
        pos[ai] = tt;
        tt += 1;
    }

    vector<int> sorted_a;
    for (auto ai : A) {
        sorted_a.push_back(ai);
    }

    SegmentTree ST(A.size());
    int t = 0;
    for (auto ai : A) {
        ST.plus(t, t, -ST.query(t, t) + abs(ai - b[0]));
        t += 1;
    }

    int m = -1;
    int ans = inf;

    for (int i = 0; i < n; i++) {
        if (i != 0) {
            m = max(m, a[i - 1]);

            ans = min(ans, abs(m - b[i]));

            int G1 = bs_rl(sorted_a, b[i - 1]);
            if (G1 != -1) {
                ST.plus(G1, A.size() - 1, b[i - 1] - b[i]);
            }

            int G2 = bs_lr(sorted_a, b[i]);
            if (G2 != -1) {
                ST.plus(0, G2, -(b[i - 1] - b[i]));
            }

            int L = b[i] + 1;
            int R = b[i - 1] - 1;

            if (L <= R) {
                int l = bs_rl(sorted_a, L);
                int r = bs_lr(sorted_a, R);

                if (l == -1) {
                    l = inf;
                }

                if (r == -1) {
                    r = sorted_a.size() - 1;
                }
                    
                if (l <= r) {
                    for (int j = l; j <= r; j++) {
                        int aj = sorted_a[j];
                        if (cntA[aj] > 0) {
                            ST.plus(pos[aj], pos[aj], -ST.query(pos[aj], pos[aj]) + abs(aj - b[i]));
                        }
                    }
                }
            }
        }

        int bi = b[i];

        cntA[a[i]] -= 1;
        if (cntA[a[i]] == 0) {
            int ai = a[i];
            ST.plus(pos[a[i]], pos[a[i]], -ST.query(pos[a[i]], pos[a[i]]) + inf);
            A.erase(A.find(a[i]));
        }

        while (A.size() > 0 && *A.begin() < m) {
            cntA[*A.begin()] = 0;
            if (cntA[*A.begin()] == 0) {
                int ai = *A.begin();
                ST.plus(pos[*A.begin()], pos[*A.begin()], inf);
                A.erase(A.begin());
            }
        }

        ans = min(ans, ST.query(0, sorted_a.size() - 1));
    }

    cout << ans << '\n';
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
