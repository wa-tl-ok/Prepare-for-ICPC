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

class SCC_GRAPH {
public:
    SCC_GRAPH(vector<vector<int>>& g) {
        int n = (int)g.size();

        int m = 0;
        for (int u = 0; u < n; u++) {
            m += (int)g[u].size();
        }

        set<pair<int, int>> edges;
        for (int u = 0; u < n; u++) {
            for (auto v : g[u]) {
                edges.insert({ u, v });
            }
        }

        vector<vector<int>> r_g(n);
        for (int u = 0; u < n; u++) {
            for (auto v : g[u]) {
                r_g[v].push_back(u);
            }
        }

        vector<int> vis(n);
        for (int i = 0; i < n; i++) {
            vis[i] = false;
        }

        for (int u = 0; u < n; u++) {
            if (vis[u] == false) {
                dfs(u, g, vis);
            }
        }

        reverse(top_sort.begin(), top_sort.end());

        scc.resize(n);
        for (int i = 0; i < n; i++) {
            scc[i] = -1;
        }

        for (int i = 0; i < n; i++) {
            if (scc[top_sort[i]] == -1) {
                ++color;
                Go(top_sort[i], r_g);
            }
        }

        vector<set<int>> GG(color + 1);

        for (auto p : edges) {
            int u = p.first;
            int v = p.second;

            if (scc[u] != scc[v]) {
                GG[scc[u]].insert(scc[v]);
            }
        }

        N = color + 1;

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

private:
    vector<vector<int>> G; int N;
    vector<int> top_sort;
    vector<int> scc; int color = -1;

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
    int n; cin >> n;

    vector<vector<int>> g(2 * n);

    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        char Type; cin >> Type;
        if (Type == '+') {
            g[u].push_back(v);
            g[v].push_back(u);
            g[u + n].push_back(v + n);
            g[v + n].push_back(u + n);
        }
        else if (Type == '-') {
            g[u].push_back(v + n);
            g[v].push_back(u + n);
        }
    }

    SCC_GRAPH scc_graph(g);

    int N = scc_graph.Get_N();
    vector<vector<int>> G = scc_graph.Get_G();
    vector<int> scc = scc_graph.Get_scc();

    set<int> ANS;

    for (int x = 0; x < n; x++) {
        if (scc[x] == scc[x + n]) {
            cout << "NO";
            return;
        }
        else {
            if (scc[x] > scc[x + n]) {
                ANS.insert(x);
            }
        }
    }

    cout << "YES" << '\n';
    cout << ANS.size() << '\n';
    for (auto p : ANS) {
        cout << p + 1 << ' ';
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
