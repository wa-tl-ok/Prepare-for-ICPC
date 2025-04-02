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

int bs_ll(vector<int>& arr, int target) {
    /*
        Find max index of number in arr that < target
    */
    if (arr[0] >= target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] >= target) {
            right = mid - 1;
        }
        else {
            if (arr[mid + 1] >= target) {
                return mid;
            }
            left = mid + 1;
        }
    }
    return left;
}

int bs_rr(vector<int>& arr, int target) {
    /*
        Find min index of number that > target
    */
    if (arr[arr.size() - 1] <= target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] <= target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

void Solve() {
    vector<int> ALL = { 12, 13, 14, 23, 24, 34 };
    int n, q; cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;

        if (s == "BG") {
            a[i] = 12;
        }
        else if (s == "BR") {
            a[i] = 13;
        }
        else if (s == "BY") {
            a[i] = 14;
        }
        else if (s == "GR") {
            a[i] = 23;
        }
        else if (s == "GY") {
            a[i] = 24;
        }
        else {
            a[i] = 34;
        }
    }

    map<int, vector<int>> pos;
    for (int i = 0; i < n; i++) {
        pos[a[i]].push_back(i);
    }

    for (int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;

        --l;
        --r;

        if (l > r) {
            swap(l, r);
        }

        if (l == r) {
            cout << 0 << '\n';
            continue;
        }

        if (a[l] == 12 && a[r] == 34) {
            // Solve - ???
        }
        else if (a[l] == 13 && a[r] == 24) {
            // Solve - ???
        }
        else if (a[l] == 14 && a[r] == 23) {
            // Solve - ???
        }
        else if (a[l] == 23 && a[r] == 14) {
            // Solve - ???
        }
        else if (a[l] == 24 && a[r] == 13) {
            // Solve - ???
        }
        else if (a[l] == 34 && a[r] == 12) {
            // Solve - ???
        }
        else {
            cout << r - l << '\n';
            continue;
        }

        int ans = inf;

        int f = a[l];
        int s = a[r];

        for (auto p : ALL) {
            if (p != f && p != s && pos[p].size() > 0) {
                int Li = bs_ll(pos[p], l);

                if (Li != -1) {
                    ans = min(ans, abs(l - pos[p][Li]) + abs(pos[p][Li] - r));
                }

                int Ri = bs_rr(pos[p], l);

                if (Ri != -1) {
                    ans = min(ans, abs(l - pos[p][Ri]) + abs(pos[p][Ri] - r));
                }
            }
        }

        if (ans == inf) {
            cout << -1 << '\n';
        }
        else {
            cout << ans << '\n';
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
