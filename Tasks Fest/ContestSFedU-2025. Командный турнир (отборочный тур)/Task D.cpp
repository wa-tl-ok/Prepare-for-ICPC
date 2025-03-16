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

#pragma GCC optimize("Ofast") 
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

const int MAXN = 200005;
const int LOG = 20;

vector<pair<int, int>> graph[MAXN];
int parent[MAXN][LOG];
int max_weight[MAXN][LOG];
int depth[MAXN];
int n, m;

void dfs(int v, int p, int w) {
    parent[v][0] = p;
    max_weight[v][0] = w;
    depth[v] = depth[p] + 1;

    for (auto& edge : graph[v]) {
        int u = edge.first;
        int weight = edge.second;
        if (u != p) {
            dfs(u, v, weight);
        }
    }
}

void prepare() {
    for (int j = 1; j < LOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (parent[i][j - 1] != -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
                max_weight[i][j] = max(max_weight[i][j - 1], max_weight[parent[i][j - 1]][j - 1]);
            }
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    int max_edge = 0;

    for (int j = LOG - 1; j >= 0; --j) {
        if (depth[parent[u][j]] >= depth[v]) {
            max_edge = max(max_edge, max_weight[u][j]);
            u = parent[u][j];
        }
    }

    if (u == v) {
        return max_edge;
    }

    for (int j = LOG - 1; j >= 0; --j) {
        if (parent[u][j] != parent[v][j]) {
            max_edge = max(max_edge, max_weight[u][j]);
            max_edge = max(max_edge, max_weight[v][j]);

            u = parent[u][j];
            v = parent[v][j];
        }
    }

    max_edge = max(max_edge, max_weight[u][0]);
    max_edge = max(max_edge, max_weight[v][0]);

    return max_edge;
}

void Solve() {
    cin >> n >> m;

    for (int i = 0; i < n - 1; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        graph[u].emplace_back(v, c);
        graph[v].emplace_back(u, c);
    }

    dfs(1, 0, 0);
    prepare();

    int total_cost = 0;
    vector<int> cities(m);
    for (int i = 0; i < m; ++i) {
        cin >> cities[i];
    }

    for (int i = 0; i < m - 1; ++i) {
        int u = cities[i];
        int v = cities[i + 1];

        total_cost += lca(u, v);
    }

    total_cost += lca(cities[m - 1], cities[0]);

    cout << total_cost;
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
