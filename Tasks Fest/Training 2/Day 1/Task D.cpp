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

bool Comp(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
}

void Solve() {
    int n, k; cin >> n >> k;
    int ans = 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    if (k == 0) {
        int s = 0;
        for (int i = 0; i < n; i++) {
            if (b[i] - a[i] > 0) {
                s += b[i] - a[i];
            }
        }
        cout << s << '\n';
        return;
    }

    vector<pair<int, int>> ab;
    for (int i = 0; i < n; i++) {
        ab.push_back({ a[i], b[i] });
    }

    sort(ab.begin(), ab.end(), Comp);

    a.clear();
    for (int i = 0; i < n; i++) {
        if (ab[i].first < ab[i].second) {
            a.push_back(ab[i].first);
        }
    }

    b.clear();
    for (int i = 0; i < n; i++) {
        if (ab[i].first < ab[i].second) {
            b.push_back(ab[i].second);
        }
    }

    n = a.size();

    if (n <= k) {
        cout << 0 << '\n';
        return;
    }

    int sa = 0;
    vector<int> prefix_sum_a;
    for (int i = 0; i < n; i++) {
        sa += a[i];
        prefix_sum_a.push_back(sa);
    }

    int sb = 0;
    vector<int> prefix_sum_b;
    for (int i = 0; i < n; i++) {
        sb += b[i];
        prefix_sum_b.push_back(sb);
    }

    multiset<int> CUR;
    int MS = 0;
    for (int i = 0; i < k; i++) {
        CUR.insert(a[i]);
        MS += a[i];
    }

    for (int i = k; i < n; i++) {
        ans = max(ans, (prefix_sum_b[n - 1] - prefix_sum_b[i - 1]) - (prefix_sum_a[n - 1] - prefix_sum_a[i - 1]) - MS);

        if (a[i] < *(--CUR.end())) {
            MS -= *(--CUR.end());
            MS += a[i];

            CUR.erase(--CUR.end());
            CUR.insert(a[i]);
        }
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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
