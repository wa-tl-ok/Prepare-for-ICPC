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

void Solve() {
    int n; cin >> n;

    vector<pair<int, int>> D;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;

        int l = a - b;
        int r = a;

        D.push_back({ l, r });
    }

    sort(D.begin(), D.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) { 
        if (a.second < b.second) {
            return true;
        }
        else if (a.second == b.second) {
            return a.first < b.first;
        }
        else {
            return false;
        }
        });

    vector<int> DP(n);
    DP[0] = 1;

    vector<int> a;
    a.push_back(D[0].second);

    for (int i = 1; i < n; i++) {
        if (bs_ll(a, D[i].first) != -1) {
            DP[i] = DP[bs_ll(a, D[i].first)] + 1;
        }
        else {
            DP[i] = 1;
        }

        a.push_back(D[i].second);
    }

    int mx = 0;
    for (int i = 0; i < n; i++) {
        mx = max(mx, DP[i]);
    }

    cout << n - mx;
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
