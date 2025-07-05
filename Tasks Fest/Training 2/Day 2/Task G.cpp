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

bool check(string& s, int k) {
    vector<int> a(26);
    for (int i = 0; i < k; i++) {
        a[s[i] - 'a'] += 1;
    }

    int FIX = s.size() - k;

    if (k < s.size() / 2) {
        int l = s.size() / 2 - 1;
        int r = s.size() / 2;

        while (l >= k) {
            if (s[l] != s[r]) {
                return false;
            }

            --l;
            ++r;
        }

        FIX = k;
    }

    for (int i = s.size() - 1; i > s.size() - FIX - 1; i--) {
        a[s[i] - 'a'] -= 1;
    }

    for (int i = 0; i < 26; i++) {
        if (a[i] < 0) {
            return false;
        }
    }

    return true;
}

int get(string& s) {
    int l = 0;
    int r = s.size();

    while (l + 1 != r) {
        int m = (l + r) / 2;

        if (check(s, m) == true) {
            r = m;
        }
        else {
            l = m;
        }
    }

    return r;
}

void Solve() {
    string s; cin >> s;

    int l = 0;
    int r = s.size() - 1;

    while (s[l] == s[r]) {
        ++l;
        --r;

        if (l > r) {
            cout << 0 << '\n';
            return;
        }
    }

    string S = "";
    for (int i = l; i <= r; i++) {
        S += s[i];
    }

    int m1 = get(S);
    reverse(S.begin(), S.end());
    int m2 = get(S);

    cout << min(m1, m2) << '\n';
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
