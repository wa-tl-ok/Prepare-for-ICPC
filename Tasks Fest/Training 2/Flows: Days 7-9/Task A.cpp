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

class Dinic {
public:
    struct Edge {
        int u, v, flow, cap, u_id, v_id, ru_id, rv_id;

        /*
            u --------------------> v
               F = flow; C = cap

            g[u_id][v_id] = Edge;
            g[ru_id][rv_id] = Reverse(Edge);
        */
    };

    Dinic(int n_, int nodes_) : n(n_), nodes(nodes_) {
        g.resize(n);
    }

    void add_edge(int u, int v, int cap) {
        Edge a = { u, v, 0, cap, u, (int)(g[u]).size(), v, (int)(g[v]).size() };
        Edge b = { v, u, 0, 0, v, (int)(g[v]).size(), u, (int)(g[u]).size() };

        g[u].push_back(a);
        g[v].push_back(b);
    }

    int max_flow(int s_, int t_) {
        s = s_;
        t = t_;

        int flow = 0;

        while (bfs()) {
            while (true) {
                vis.resize(n);
                for (int i = 0; i < n; i++) {
                    vis[i] = false;
                }

                int p = dfs(s, INF);

                if (p == 0) {
                    break;
                }
                else {
                    flow += p;
                }
            }
        }

        return flow;
    }

    void print() {
        vector<vector<int>> A(nodes);
        for (int i = 0; i < nodes; i++) {
            A[i].resize(nodes);
        }
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                A[i][j] = 0;
            }
        }

        for (auto& v : g) {
            for (auto& e : v) {
                int u = e.u;
                int v = e.v;
                
                if (u >= 1 && u <= nodes * 2 && v >= 1 && v <= nodes * 2) {
                    if (u > nodes) {
                        u -= nodes;
                    }
                    if (v > nodes) {
                        v -= nodes;
                    }
                    A[v - 1][u - 1] = abs(e.flow);
                }
            }
        }

        for (int u = 0; u < nodes; u++) {
            for (int v = 0; v < nodes; v++) {
                cout << A[u][v] << ' ';
            } cout << '\n';
        }
    }

private:
    const int INF = 1e18;

    int n, s, t;
    int nodes;

    vector<int> level;
    vector<vector<Edge>> g;

    bool bfs() {
        level.resize(n);
        for (int i = 0; i < n; i++) {
            level[i] = -1;
        }

        level[s] = 0;

        queue<int> q;
        q.push(s);

        while (q.size() > 0) {
            int u = q.front();
            q.pop();

            for (auto& E : g[u]) {
                int v = E.v;

                if (level[v] == -1 && E.flow < E.cap) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }

        return level[t] != -1;
    }

    vector<int> vis;

    int dfs(int u, int flow) {
        vis[u] = true;

        if (u == t) {
            return flow;
        }

        for (auto& E : g[u]) {
            if (E.flow < E.cap) {
                int v = E.v;

                if (level[v] == level[u] + 1 && vis[v] == false) {
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
    int n, m; cin >> n >> m;

    vector<int> a(n + 1); int SA = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; SA += a[i];
    }

    vector<int> b(n + 1); int SB = 0;
    for (int i = 1; i <= n; i++) {
        cin >> b[i]; SB += b[i];
    }

    Dinic net(2 * n + 2, n);

    for (int v = 1; v <= n; v++) {
        net.add_edge(0, v, a[v]);
    }

    for (int u = 1; u <= n; u++) {
        net.add_edge(u, u + n, inf);
    }

    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        net.add_edge(v, u + n, inf);
        net.add_edge(u, v + n, inf);
    }

    for (int u = n + 1; u <= 2 * n; u++) {
        net.add_edge(u, 2 * n + 1, b[u - n]);
    }

    int FLOW = net.max_flow(0, 2 * n + 1);

    if (FLOW == SB && SA == SB) {
        cout << "YES" << '\n';
        net.print();
    }
    else {
        cout << "NO" << '\n';
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
