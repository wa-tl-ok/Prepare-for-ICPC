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

class TREE {
public:
    TREE(int size) : n(size), timer(0), count_edges(0),
        SegmentTree_sum(size) {

        g.resize(n);

        S.resize(n);
        P.resize(n);

        tin.resize(n);
        tout.resize(n);

        head.resize(n);

        vis.resize(n);

        last_ind.resize(n);

        if (n == 1) {
            DECOMPOSE();
        }
    }

    void Add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);

        ++count_edges;

        if (count_edges == n - 1) {
            DECOMPOSE();
        }
    }

    void DECOMPOSE() {
        HLD_Decompose();

        int N = (int)g.size();

        visited.resize(N);
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        parent.resize(N);
        for (int i = 0; i < N; i++) {
            parent[i] = 0;
        }

        function<void(int, int)> dfs = [&](int u, int p) {
            visited[u] = true;
            parent[u] = p;
            for (int v : g[u]) {
                if (!visited[v]) {
                    dfs(v, u);
                }
            }
        };

        dfs(0, 0);

        depth.resize(N);
        for (int i = 0; i < N; i++) {
            depth[i] = 0;
        }

        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        vector<int> sloy1 = { 0 };
        visited[0] = true;

        while (sloy1.size() > 0) {
            vector<int> sloy2;

            for (auto u : sloy1) {
                for (auto v : g[u]) {
                    if (visited[v] == false) {
                        visited[v] = true;
                        depth[v] = depth[u] + 1;
                        sloy2.push_back(v);
                    }
                }
            }

            sloy1 = sloy2;
        }
    }

    void HLD_Decompose(int root = 0) {
        sizes(root);
        head[root] = root;
        hld(root);
    }

    void change(int u, int v, int value) {
        while (!Check(head[u], v)) {
            SegmentTree_sum.change(tin[head[u]], tin[u], value);
            u = P[head[u]];
        }

        while (!Check(head[v], u)) {
            SegmentTree_sum.change(tin[head[v]], tin[v], value);
            v = P[head[v]];
        }

        if (!Check(u, v)) {
            swap(u, v);
        }

        SegmentTree_sum.change(tin[u], tin[v], value);
    }

    int Get_sum(int u, int v) {
        int ans = 0;

        while (!Check(head[u], v)) {
            ans += SegmentTree_sum.query(tin[head[u]], tin[u]);
            u = P[head[u]];
        }

        while (!Check(head[v], u)) {
            ans += SegmentTree_sum.query(tin[head[v]], tin[v]);
            v = P[head[v]];
        }

        if (!Check(u, v)) {
            swap(u, v);
        }

        return ans + SegmentTree_sum.query(tin[u], tin[v]);
    }

private:
    class SEGMENT_TREE_SUM {
    public:
        SEGMENT_TREE_SUM(int size) {
            n = size;
            int p = 1;
            while (p < n) {
                p *= 2;
            }

            tree.assign(p * 2, 0);
            lazy.assign(p * 2, { 0, false });

            n = p;
        }

        SEGMENT_TREE_SUM(const vector<int>& a) {
            n = (int)a.size();
            int p = 1;
            while (p < n) {
                p *= 2;
            }

            tree.assign(p * 2, 0);
            lazy.assign(p * 2, { -1, false });

            n = p;

            for (int i = 0; i < (int)a.size(); ++i) {
                updateRange(1, 0, n - 1, i, i, a[i], false);
            }
        }

        void plus(int const_l, int const_r, int val) {
            updateRange(1, 0, n - 1, const_l, const_r, val, true);
        }

        void change(int const_l, int const_r, int val) {
            updateRange(1, 0, n - 1, const_l, const_r, val, false);
        }

        int query(int const_l, int const_r) {
            return queryRange(1, 0, n - 1, const_l, const_r);
        }
    private:
        vector<int> tree;
        vector<pair<int, bool>> lazy;
        int n;

        void propagate(int node, int l, int r) {
            if (lazy[node].second) {
                if (lazy[node].first != -1) {
                    tree[node] += lazy[node].first * (r - l + 1);
                    if (l != r) {
                        lazy[2 * node].first += lazy[node].first;
                        lazy[2 * node].second = true;
                        lazy[2 * node + 1].first += lazy[node].first;
                        lazy[2 * node + 1].second = true;
                    }
                }
            }
            else {
                if (lazy[node].first != -1) {
                    tree[node] = lazy[node].first * (r - l + 1);
                    if (l != r) {
                        lazy[2 * node] = lazy[node];
                        lazy[2 * node + 1] = lazy[node];
                    }
                }
            }
            lazy[node] = { -1, false };
        }

        void updateRange(int node, int l, int r, int const_l, int const_r, int val, bool isAddition) {
            propagate(node, l, r);
            if (l > r || l > const_r || r < const_l) {
                return;
            }
            if (l >= const_l && r <= const_r) {
                if (isAddition) {
                    tree[node] += val * (r - l + 1);
                    if (l != r) {
                        lazy[2 * node].first += val;
                        lazy[2 * node].second = true;
                        lazy[2 * node + 1].first += val;
                        lazy[2 * node + 1].second = true;
                    }
                }
                else {
                    tree[node] = val * (r - l + 1);
                    if (l != r) {
                        lazy[2 * node] = { val, false };
                        lazy[2 * node + 1] = { val, false };
                    }
                }
                return;
            }

            int mid = (l + r) / 2;

            updateRange(2 * node, l, mid, const_l, const_r, val, isAddition);
            updateRange(2 * node + 1, mid + 1, r, const_l, const_r, val, isAddition);

            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }

        int queryRange(int node, int l, int r, int const_l, int const_r) {
            if (l > r || l > const_r || r < const_l) {
                return 0;
            }

            propagate(node, l, r);

            if (l >= const_l && r <= const_r) {
                return tree[node];
            }

            int mid = (l + r) / 2;

            int p1 = queryRange(2 * node, l, mid, const_l, const_r);
            int p2 = queryRange(2 * node + 1, mid + 1, r, const_l, const_r);

            return p1 + p2;
        }
    };

    int n, timer, count_edges;
    vector<vector<int>> g;
    vector<int> S, P, tin, tout, head, vis, nodes, last_ind, parent, visited, depth;

    SEGMENT_TREE_SUM SegmentTree_sum;

    void sizes(int v, int p = -1) {
        S[v] = 1;
        P[v] = p;

        for (int& u : g[v]) {
            if (u == p) {
                continue;
            }

            sizes(u, v);
            S[v] += S[u];

            if (S[u] > S[g[v][0]]) {
                swap(u, g[v][0]);
            }
        }
    }

    void hld(int v, int p = -1) {
        tin[v] = timer++;

        for (int u : g[v]) {
            if (u == p) {
                continue;
            }

            if (u == g[v][0]) {
                head[u] = head[v];
            }
            else {
                head[u] = u;
            }

            hld(u, v);
        }

        tout[v] = timer;
    }

    bool Check(int a, int b) {
        return tin[a] <= tin[b] && tin[b] < tout[a];
    }

public:
    int FIND(vector<int> a) {
        int d = 0;
        int v = 0;

        for (auto u : a) {
            if (depth[u] > d) {
                d = depth[u];
                v = u;
            }
        }

        return v;
    }

    void Solve(vector<int> a) {
        change(parent[FIND(a)], 0, 1);

        string ans = "YES";
        for (int i = 0; i < (int)a.size(); i++) {
            if (Get_sum(parent[a[i]], parent[a[i]]) == 0) {
                ans = "NO";
            }
        }

        change(parent[FIND(a)], 0, 0);

        cout << ans << '\n';
    }
};

void Solve() {
    int n, q; cin >> n >> q;
    TREE tree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        tree.Add_edge(u, v);
    }

    for (int qq = 0; qq < q; qq++) {
        int m; cin >> m;
        vector<int> a(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i];
            --a[i];
        }
        tree.Solve(a);
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
