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

int find_L(vector<int>& a, int cl, int cr) {
    if (a[a.size() - 1] < cl) {
        return inf;
    }

    int l = -1;
    int r = a.size();

    while (l + 1 != r) {
        int m = (l + r) / 2;

        if (a[m] < cl) {
            l = m;
        }
        else {
            r = m;
        }
    }

    return a[r];
}

int find_R(vector<int>& a, int cl, int cr) {
    if (a[0] > cr) {
        return -inf;
    }

    int l = -1;
    int r = a.size();

    while (l + 1 != r) {
        int m = (l + r) / 2;

        if (a[m] > cr) {
            r = m;
        }
        else {
            l = m;
        }
    }

    return a[l];
}

int get_L(map<int, vector<int>>& pos, vector<int>& px, int l, int r) {
    return find_L(pos[px[r]], l, r);
}

int get_R(map<int, vector<int>>& pos, vector<int>& px, int l, int r) {
    int v = -1;

    if (l == 0) {
        v = 0;
    }
    else {
        v = px[l - 1];
    }

    int R = -1;

    if (pos[0].size() > 0) {
        R = find_R(pos[v], l, r);
    }
    else {
        R = -inf;
    }

    return R;
}

void Solve() {
    int n, q; cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> px(n + 1);
    int x = 0;
    for (int i = 1; i <= n; i++) {
        x = x ^ a[i];
        px[i] = x;
    }

    map<int, vector<int>> pos;
    for (int i = 0; i <= n; i++) {
        pos[px[i]].push_back(i);
    }

    for (int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;

        if (get_L(pos, px, l, r) < get_R(pos, px, l, r)) {
            cout << "YES\n";
        }
        else {
            if (px[l - 1] == px[r]) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }

    cout << endl;
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
