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

//#define int               long long 
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

using namespace std;

class SCC_GRAPH {
public:
    SCC_GRAPH(vector<vector<int>>& g) {
        int n = (int)g.size() / 4;

        vector<vector<int>> r_g(4 * n);
        for (int u = 0; u < 4 * n; u++) {
            for (auto v : g[u]) {
                r_g[v].push_back(u);
            }
        }

        vector<int> vis(4 * n);
        for (int i = 0; i < 4 * n; i++) {
            vis[i] = false;
        }

        for (int u = 0; u < 4 * n; u++) {
            if (vis[u] == false) {
                dfs(u, g, vis);
            }
        }

        reverse(top_sort.begin(), top_sort.end());

        scc.resize(4 * n);
        for (int i = 0; i < 4 * n; i++) {
            scc[i] = -1;
        }

        for (int i = 0; i < 2 * n; i++) {
            if (scc[top_sort[i]] == -1) {
                ++color;
                Go(top_sort[i], r_g);
                ++color;
                Go(top_sort[i + 2 * n], r_g);
            }
        }

        N = color + 1;

        for (int u = 0; u < 2 * n; u++) {
            if (scc[u] == scc[u + 2 * n]) {
                Flag = false;
                return;
            }
        }

        vector<set<int>> GG(N);
        for (int u = 0; u < 4 * n; u++) {
            for (int v : g[u]) {
                if (scc[u] != scc[v]) {
                    GG[scc[u]].insert(scc[v]);
                }
            }
        }

        G.resize(N);
        for (int u = 0; u < N; u++) {
            for (auto v : GG[u]) {
                G[u].push_back(v);
            }
        }
    }

    int Get_N() {
        return N;
    }

    vector<vector<int>> Get_G() {
        return G;
    }

    vector<int> Get_scc() {
        return scc;
    }

    vector<int> Get_top_sort() {
        return top_sort;
    }

    bool FLAG() {
        return Flag;
    }

private:
    vector<vector<int>> G; int N;
    vector<int> top_sort;
    vector<int> scc; int color = -1;

    bool Flag = true; // Solve can be found

    void dfs(int v, vector<vector<int>>& g, vector<int>& vis) {
        vis[v] = true;
        for (auto u : g[v]) {
            if (vis[u] == true) {
                continue;
            }
            dfs(u, g, vis);
        }
        top_sort.push_back(v);
    }

    void Go(int v, vector<vector<int>>& r_g) {
        scc[v] = color;
        for (auto u : r_g[v]) {
            if (scc[u] == -1) {
                Go(u, r_g);
            }
        }
    }
};

void Solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(4 * n);

    function<void(int, int)> add = [&](int u, int v) {
        g[u].push_back(v);
    };

    /*
        add(u) if +
        add(u + 2 * n) if -
    */

    for (int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        --u; --v;
        add(u + 2 * n, v);
        add(u, v + 2 * n);
        add(v + 2 * n, u);
        add(v, u + 2 * n);
    }

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u; --v;
        add(u, v + 2 * n);
        add(v, u + 2 * n);
    }

    SCC_GRAPH Graph(g);

    if (Graph.FLAG() == false) {
        cout << -1;
        return;
    }

    int N = Graph.Get_N();
    vector<vector<int>> G = Graph.Get_G();
    vector<int> scc = Graph.Get_scc();
    vector<int> top_sort = Graph.Get_top_sort();

    map<int, vector<int>> Nodes_in_Comp;
    for (int i = 0; i < 4 * n; i++) {
        Nodes_in_Comp[scc[i]].push_back(i);
    }

    int Components = N;

    vector<int> vis_cond(Components, 0);
    vector<int> top_sort_cond;

    function<void(int)> dfs_cond = [&](int v) {
        vis_cond[v] = true;
        for (auto u : G[v]) {
            if (vis_cond[u] == true) {
                continue;
            }
            dfs_cond(u);
        }
        top_sort_cond.push_back(v);
    };

    for (int u = 0; u < Components; u++) {
        if (vis_cond[u] == false) {
            dfs_cond(u);
        }
    }

    vector<int> VIS(Components, false);

    for (int i = 0; i < Components; i++) {
        int u = top_sort_cond[i];
        int v = -1;
        if (u % 2 == 0) {
            v = u + 1;
        }
        else {
            v = u - 1;
        }
        if (VIS[v] == false) {
            VIS[u] = true;
        }
        else {
            VIS[u] = true;
            for (auto w : Nodes_in_Comp[u]) {
                if (w < 2 * n) {
                    cout << w + 1 << ' ';
                }
            }
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
