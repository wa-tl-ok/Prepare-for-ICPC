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

pair<vector<int>, vector<int>> get_pref(vector<int>& a) {
    vector<int> chet_pref(a.size());
    vector<int> nechet_pref(a.size());

    int s = 0;
    for (int i = 0; i < a.size(); i++) {
        s += a[i];

        if (s % 2 == 0) {
            chet_pref[0] += 1;
        }
        else {
            nechet_pref[0] += 1;
        }
    }

    for (int i = 1; i < a.size(); i++) {
        if (a[i - 1] == 0) {
            chet_pref[i] = (chet_pref[i - 1] - 1);
            nechet_pref[i] = nechet_pref[i - 1];
        }
        else {
            chet_pref[i] = (nechet_pref[i - 1] - 1);
            nechet_pref[i] = chet_pref[i - 1];
        }
    }

    return { chet_pref, nechet_pref };
}

pair<vector<int>, vector<int>> get_suff(vector<int>& a) {
    vector<int> chet_suff(a.size());
    vector<int> nechet_suff(a.size());

    int s = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        s += a[i];

        if (s % 2 == 0) {
            chet_suff[a.size() - 1] += 1;
        }
        else {
            nechet_suff[a.size() - 1] += 1;
        }
    }

    for (int i = a.size() - 2; i >= 0; i--) {
        if (a[i + 1] == 0) {
            chet_suff[i] = (chet_suff[i + 1] - 1);
            nechet_suff[i] = nechet_suff[i + 1];
        }
        else {
            chet_suff[i] = (nechet_suff[i + 1] - 1);
            nechet_suff[i] = chet_suff[i + 1];
        }
    }

    return { chet_suff, nechet_suff };
}

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> A(32);
    for (int i = 0; i < 32; i++) {
        A[i].resize(n);
    }

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < n; j++) {
            if (a[j] & (1 << i)) {
                A[i][j] = 1;
            }
        }
    }

    int ans = 0;

    vector<vector<int>> chet_pref(32);
    vector<vector<int>> nechet_pref(32);

    for (int i = 0; i < 32; i++) {
        pair<vector<int>, vector<int>> P = get_pref(A[i]);

        chet_pref[i] = P.first;
        nechet_pref[i] = P.second;
    }

    vector<vector<int>> chet_suff(32);
    vector<vector<int>> nechet_suff(32);

    for (int i = 0; i < 32; i++) {
        pair<vector<int>, vector<int>> P = get_suff(A[i]);

        chet_suff[i] = P.first;
        nechet_suff[i] = P.second;
    }

    for (int i = 0; i < n; i++) {
        int main_bit = -1;

        for (int j = 0; j < 32; j++) {
            if (a[i] & (1 << j)) {
                main_bit = j;
            }
        }

        int c_l = 0;
        int n_l = 0;

        if (i == 0) {
            c_l = 1;
            n_l = 0;
        }
        else {
            c_l = chet_suff[main_bit][i - 1] + 1;
            n_l = nechet_suff[main_bit][i - 1];
        }

        int c_r = 0;
        int n_r = 0;

        if (i == n - 1) {
            c_r = 1;
            n_r = 0;
        }
        else {
            c_r = chet_pref[main_bit][i + 1] + 1;
            n_r = nechet_pref[main_bit][i + 1];
        }

        ans += c_l * n_r + n_l * c_r;
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
