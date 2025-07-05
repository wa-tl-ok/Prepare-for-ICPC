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

int n;
unordered_map<int, int> g;
unordered_map<int, vector<int>> rg;
unordered_map<int, int> term;
unordered_map<int, int> vis;
unordered_map<int, int> sz;
int p;
int q;

void dfs(int v) {
    vis[v] = 1;

    if (g[v] < 1 || g[v] > n) {
        term[v] = true;
        return;
    }

    if (vis[g[v]] == 1) {
        term[v] = term[g[v]];
        return;
    }

    dfs(g[v]);
    term[v] = term[g[v]];
}

void sz_find(int v) {
    vis[v] = 1;

    if (rg[v].size() == 0) {
        return;
    }

    for (int u : rg[v]) {
        if (vis[u] != 1) {
            sz_find(u);
            sz[v] += sz[u];
        }
    }
}

void DFS(int v) {
    q += sz[v];
    vis[v] = 1;
    if (g[v] < 1 || g[v] > n) {
        return;
    }
    else if (vis[g[v]] == 1) {
        return;
    }
    else {
        ++p;
        DFS(g[v]);
    }
}

void Solve() {
    g.clear();
    rg.clear();
    term.clear();
    vis.clear();
    sz.clear();

    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        int u = i; int v = i + a[i]; if (v < 1 || v > n) v = 0;
        g[u] = v; rg[v].push_back(u);
    }

    for (int u = 1; u <= n; u++) {
        if (vis[u] != 1) {
            dfs(u);
        }
    }

    int cnt_term = 0;
    for (auto [u, t] : term) {
        if (t == true) {
            ++cnt_term;
        }
    }

    if (term[1] == true) {
        for (int i = 1; i <= n; i++) {
            sz[i] = 1;
        } vis.clear();
        sz_find(0);

        vis.clear(); p = 1; q = 0; DFS(1);
        cout << (n * (2 * n + 1) - p * (n - cnt_term) - q) << '\n';
    }
    else {
        vis.clear(); p = 1; q = 0; DFS(1);
        cout << ((cnt_term + n + 1) * p) << '\n';
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
