class TOP_SORT {
public:
    TOP_SORT(vector<vector<int>>& g) {
        int n = (int)g.size();

        int m = 0;
        for (int u = 0; u < n; u++) {
            m += (int)g[u].size();
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
    }

    vector<int> Get_top_sort() {
        return top_sort;
    }

private:
    vector<int> top_sort;

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
};
