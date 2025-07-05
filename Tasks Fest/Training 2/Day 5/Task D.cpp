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
    vector<int> ans;

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    multiset<int> mxe;
    for (int i = 0; i < n; i++) {
        mxe.insert(a[i]);
    }

    vector<int> sorted_a = a;
    sort(all(sorted_a));

    multiset<int> mxr;
    for (int i = 1; i < n; i++) {
        mxr.insert(abs(sorted_a[i] - sorted_a[i - 1]));
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int p, v; cin >> p >> v; --p;

        if (n == 1) {
            a[p] = v;
            ans.push_back(a[0]);
        }
        else if (n == 2) {
            a[p] = v;
            ans.push_back(max(a[0], a[1]) + abs(a[0] - a[1]));
        }
        else {
            if (mxe.find(a[p]) == mxe.begin()) {
                auto it = mxe.begin();
                auto it_future = it; ++it_future;
                mxr.erase(mxr.find(abs(*it - *it_future)));
            }
            else if (mxe.find(a[p]) == --mxe.end()) {
                auto it = mxe.end(); --it;
                auto it_pred = it; --it_pred;
                mxr.erase(mxr.find(abs(*it - *it_pred)));
            }
            else {
                auto it = mxe.find(a[p]);
                if (it == mxe.begin()) ++it;
                if (it == (--mxe.end())) --it;

                auto it_pred = it; --it_pred;
                auto it_future = it; ++it_future;

                mxr.erase(mxr.find(abs(*it - *it_pred)));
                mxr.erase(mxr.find(abs(*it - *it_future)));
                mxr.insert(abs(*it_pred - *it_future));
            }

            mxe.erase(mxe.find(a[p]));

            auto itr = mxe.upper_bound(v);

            if (itr == mxe.end()) {
                auto it = mxe.end(); --it;
                mxr.insert(abs(v - *it));
            }
            else if (itr == mxe.begin()) {
                auto it = mxe.begin();
                mxr.insert(abs(v - *it));
            }
            else {
                auto itl = itr; --itl;

                mxr.erase(mxr.find(abs(*itl - *itr)));
                mxr.insert(abs(v - *itl));
                mxr.insert(abs(v - *itr));
            }

            mxe.insert(v);

            auto it1 = mxe.end(); --it1;
            auto it2 = mxr.end(); --it2;
            ans.push_back(*it1 + *it2);
            a[p] = v;
        }
    }

    PRINT(ans);
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
