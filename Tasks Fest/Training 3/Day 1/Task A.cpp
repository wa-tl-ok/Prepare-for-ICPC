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

vector<int> cut(vector<int> a, int l, int r) {
    vector<int> ans;
    for (int i = l; i <= r; i++) {
        ans.push_back(a[i]);
    }
    return ans;
}

vector<int> get(vector<int> a) {
    int MX = 0;
    int mn_pref = 0; int cur1 = 0;
    for (int i = 0; i < a.size(); i++) {
        cur1 += a[i];
        mn_pref = min(mn_pref, cur1);
        MX = max(MX, cur1 - mn_pref);
    }

    int MN = 0;
    int mx_pref = 0; int cur2 = 0;
    for (int i = 0; i < a.size(); i++) {
        cur2 += a[i];
        mx_pref = max(mx_pref, cur2);
        MN = min(MN, cur2 - mx_pref);
    }

    vector<int> ans;
    for (int i = MN; i <= MX; i++) {
        ans.push_back(i);
    }

    return ans;
}

int mxpref(vector<int> a) {
    int ans = 0;
    int cur = 0;
    for (int i = 0; i < a.size(); i++) {
        cur += a[i];
        ans = max(ans, cur);
    }
    return ans;
}

int mnpref(vector<int> a) {
    int ans = 0;
    int cur = 0;
    for (int i = 0; i < a.size(); i++) {
        cur += a[i];
        ans = min(ans, cur);
    }
    return ans;
}

int SUM(vector<int> a) {
    int ans = 0;
    for (int i = 0; i < a.size(); i++) {
        ans += a[i];
    }
    return ans;
}

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int x = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] != -1 && a[i] != 1) {
            x = a[i];
            a[i] = 0;
        }
    }

    if (x == 0) {
        vector<int> ans = get(a);
        cout << ans.size() << '\n';
        PRINT(ans);
    }
    else {
        int ind = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 0) {
                ind = i;
            }
        }

        vector<int> L = get(cut(a, 0, ind - 1));
        vector<int> R = get(cut(a, ind + 1, n - 1));

        int MX = mxpref(cut(a, ind, n - 1)) + (SUM(cut(a, 0, ind)) - mnpref(cut(a, 0, ind)));
        int MN = mnpref(cut(a, ind, n - 1)) + (SUM(cut(a, 0, ind)) - mxpref(cut(a, 0, ind)));

        vector<int> M;
        for (int i = MN; i <= MX; i++) {
            M.push_back(i + x);
        }

        set<int> ANS;
        for (auto q : L) {
            ANS.insert(q);
        }
        for (auto q : R) {
            ANS.insert(q);
        }
        for (auto q : M) {
            ANS.insert(q);
        }

        cout << ANS.size() << '\n';
        PRINT(ANS);
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
