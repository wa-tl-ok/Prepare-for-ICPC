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

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using max_heap = priority_queue<T>;

#define BIT(n) (1LL << (n))
#define HAS_BIT(x, n) (((x) >> (n)) & 1)
#define SET_BIT(x, n) ((x) | BIT(n))

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

class Dinic {
public:
    struct Edge {
        int u, v, flow, cap, u_id, v_id, ru_id, rv_id;
    };

    Dinic(int n_) {
        n = n_;
        g.resize(n);
    }

    void add_edge(int u, int v, int c) {
        Edge a = { u, v, 0, c, u, g[u].size(), v, g[v].size() };
        Edge b = { v, u, 0, 0, v, g[v].size(), u, g[u].size() };

        g[u].push_back(a);
        g[v].push_back(b);
    }

    int max_flow(int s_, int t_) {
        s = s_;
        t = t_;

        int FLOW = 0;

        while (bfs()) {
            while (true) {
                vis.resize(n);
                for (int i = 0; i < n; i++) {
                    vis[i] = false;
                }

                int p = dfs(s, inf);

                if (p == 0) {
                    break;
                }
                else {
                    FLOW += p;
                }
            }
        }

        return FLOW;
    }

private:
    int n, s, t;
    vector<vector<Edge>> g;

    vector<int> level;

    bool bfs() {
        level.resize(n);
        for (int i = 0; i < n; i++) {
            level[i] = -1;
        } level[s] = 0;

        vector<int> sloy1 = { s };
        vector<int> sloy2 = {};

        while (sloy1.size() > 0) {
            for (int u : sloy1) {
                for (auto& e : g[u]) {
                    int v = e.v;

                    if (level[v] == -1 && e.flow < e.cap) {
                        level[v] = level[u] + 1;
                        sloy2.push_back(v);
                    }
                }
            }
            sloy1 = sloy2;
            sloy2 = {};
        }

        return level[t] != -1;
    }

    vector<bool> vis;

    int dfs(int u, int flow) {
        vis[u] = true;

        if (u == t) {
            return flow;
        }

        for (auto& E : g[u]) {
            if (E.flow < E.cap) {
                int v = E.v;

                if (vis[v] == true) {
                    continue;
                }

                if (level[v] == level[u] + 1) {
                    int p = dfs(v, min(flow, E.cap - E.flow));

                    if (p > 0) {
                        g[E.u_id][E.v_id].flow += p;
                        g[E.ru_id][E.rv_id].flow -= p;

                        return p;
                    }
                }
            }
        }

        return 0;
    }
};

void Solve() {
    int n, k, m;
    cin >> n >> k >> m;

    Dinic D(n + 1);
    for (int i = 1; i <= k; i++) {
        D.add_edge(0, i, inf);
    }

    for (int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        D.add_edge(u, v, c);
    }

    cout << D.max_flow(0, n);
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
    freopen("task.in", "r", stdin);
    freopen("task.out", "w", stdout);
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
