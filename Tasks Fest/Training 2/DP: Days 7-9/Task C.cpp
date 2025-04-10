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

void Solve() {
    string s; cin >> s;
    string t; cin >> t;

    vector<bool> vis(26, false);
    for (int i = 0; i < s.size(); i++) {
        vis[s[i] - 'a'] = true;
    }

    for (int i = 0; i < t.size(); i++) {
        if (vis[t[i] - 'a'] == false) {
            cout << -1 << '\n';
            return;
        }
    }

    vector<vector<int>> POS(26);
    for (int i = 0; i < s.size(); i++) {
        POS[s[i] - 'a'].pb(i);
    }
    for (int i = 0; i < 26; i++) {
        POS[i].pb(1e18);
    }

    vector<int> base(26, -1);
    for (int i = 0; i < s.size(); i++) {
        if (base[s[i] - 'a'] == -1) {
            base[s[i] - 'a'] = i;
        }
    }

    vector<vector<int>> jump(s.size());
    for (int i = 0; i < s.size(); i++) {
        jump[i].resize(26);
    }

    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < 26; j++) {
            jump[i][j] = POS[j][bs_rl(POS[j], i)];
        }
    }

    int ans = 1; 
    int pos = 0;

    for (int i = 0; i < t.size(); i++) {
        if (pos == s.size()) {
            pos = 0;
            ++ans;
        }

        if (jump[pos][t[i] - 'a'] != 1e18) {
            pos = jump[pos][t[i] - 'a'] + 1;
        }
        else {
            pos = base[t[i] - 'a'] + 1;
            ++ans;
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
