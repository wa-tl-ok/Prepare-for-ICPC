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
