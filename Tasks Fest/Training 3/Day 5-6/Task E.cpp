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

vector<int> color;
vector<vector<int>> g;
vector<map<int, int>> transfusion;

int DFS(int u, int p) {
    int ans = 0;

    for (int v : g[u]) {
        if (v != p) {
            ans += DFS(v, u);
        }
    }

    if (g[u].size() == 1 && u != 0) {
        transfusion[u][color[u]] = 1;
        return ans;
    }

    int big_v = -1;
    int sz_v = -1;
    for (int v : g[u]) {
        if (v != p) {
            if ((int)transfusion[v].size() > sz_v) {
                big_v = v;
                sz_v = (int)transfusion[v].size();
            }
        }
    }
    
    for (int v : g[u]) {
        ans += transfusion[v][color[u]];
        transfusion[v][color[u]] = 0;
    }

    transfusion[big_v][color[u]] = 1;

    for (int v : g[u]) {
        if (v == p) {
            continue;
        }

        if (v == big_v) {
            continue;
        }

        for (auto& [c, k] : transfusion[v]) {
            ans += k * transfusion[big_v][c];
            transfusion[big_v][c] += k;
        }
    }

    swap(transfusion[u], transfusion[big_v]);

    return ans;
}

void Solve() {
    int n; cin >> n;

    color.clear();
    g.clear();
    transfusion.clear();

    color.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> color[i];
        --color[i];
    }

    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    transfusion.resize(n);

    cout << DFS(0, 0) << '\n';
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
