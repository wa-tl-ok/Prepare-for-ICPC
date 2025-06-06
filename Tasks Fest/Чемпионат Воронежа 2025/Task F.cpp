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

struct Solver {
    struct Edge {
        int from, to;
        int cap;
        int flow;
    };

    vector<Edge> edges;
    vector<vector<int>> graph;
    int N;

    Solver(int n) : N(n) {
        graph.resize(n);
    }

    void add_edge(int u, int v, int cap, bool is_query_edge = false) {
        int edge_id = edges.size();
        edges.push_back({ u, v, cap, 0 });

        int rev_id = edges.size();
        edges.push_back({ v, u, 0, 0 });

        graph[u].push_back(edge_id);
        graph[v].push_back(rev_id);

        if (is_query_edge) {
            query_edge_map[edge_id] = query_counter++;
        }
    }

    int find_flow(int s) {
        int FLOW = 0;

        while (true) {
            vector<int> dist(N, -1);
            dist[s] = 0;

            queue<int> q;
            q.push(s);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int edge_id : graph[u]) {
                    Edge& e = edges[edge_id];
                    if (e.cap <= 0) {
                        continue;
                    }

                    if (dist[e.to] == -1) {
                        dist[e.to] = dist[u] + 1;
                        q.push(e.to);
                    }
                }
            }

            bool f = false;

            for (int l = 0; l < 26 && f == false; l++) {
                int h = D * 26 + 1 + l;

                if (dist[h] == -1) {
                    continue;
                }

                f = true;
                vector<int> ptr(N, 0);

                function<int(int, int)> dfs = [&](int u, int cur) {
                    if (u == h) {
                        return cur;
                    }

                    for (; ptr[u] < graph[u].size(); ptr[u]++) {
                        int edge_id = graph[u][ptr[u]];
                        Edge& e = edges[edge_id];

                        if (dist[e.to] != dist[u] + 1 || e.cap <= 0) {
                            continue;
                        }

                        int pushed = dfs(e.to, min(cur, e.cap));

                        if (pushed > 0) {
                            e.cap -= pushed;
                            e.flow += pushed;

                            edges[edge_id ^ 1].cap += pushed;
                            edges[edge_id ^ 1].flow -= pushed;

                            return pushed;
                        }
                    }

                    return 0LL;
                };

                int pushed = dfs(s, 1e9);

                while (pushed) {
                    FLOW += pushed;
                    pushed = dfs(s, 1e9);
                }
            }

            if (f == false) {
                break;
            }
        }

        return FLOW;
    }

    void build() {
        query_answers.resize(D, -1);
        int k = 1;

        for (int l = 0; l < 26; l++) {
            while (true) {
                vector<int> PN(N, -1);
                vector<int> PE(N, -1);
                vector<int> dist(N, -1);
                queue<int> q;

                dist[0] = 0;
                q.push(0);

                while (!q.empty()) {
                    int u = q.front();
                    q.pop();

                    for (int edge_id : graph[u]) {
                        Edge& e = edges[edge_id];
                        if (e.flow <= 0) {
                            continue;
                        }

                        if (dist[e.to] == -1) {
                            dist[e.to] = dist[u] + 1;

                            PN[e.to] = u;
                            PE[e.to] = edge_id;

                            q.push(e.to);
                        }
                    }
                }

                int h = D * 26 + 1 + l;

                if (dist[h] == -1) {
                    break;
                }

                bool f = false;
                int cur = h;

                while (cur != 0) {
                    int edge_id = PE[cur];

                    if (query_edge_map.count(edge_id)) {
                        int query_idx = query_edge_map[edge_id];
                        query_answers[query_idx] = k;
                        f = true;
                    }

                    edges[edge_id].flow--;
                    cur = PN[cur];
                }

                if (f == false) {
                    break;
                }

                k++;
            }
        }
    }

    int D;
    int query_counter = 0;
    unordered_map<int, int> query_edge_map;
    vector<int> query_answers;
    vector<pair<char, char>> queries;
};

void Solve() {
    string s; cin >> s;
    int n; cin >> n;

    Solver G(2 + (n + 1) * 26);
    G.D = n;

    for (int l = 0; l < 26; l++) {
        int cap = (l == s[0] - 'a') ? s.size() : 0;
        G.add_edge(0, 1 + l, cap);
    }

    for (int d = 0; d < n; d++) {
        char u, v; cin >> u >> v;
        G.queries.push_back({ u, v });

        int U = u - 'a';
        int V = v - 'a';
        int prev = d * 26 + 1;
        int next = (d + 1) * 26 + 1;

        for (int l = 0; l < 26; l++) {
            G.add_edge(prev + l, next + l, 100);
        }

        G.add_edge(prev + U, next + V, 1, true);
    }

    G.find_flow(0);
    G.build();

    for (int ans : G.query_answers) {
        cout << ans << '\n';
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
