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

    Dinic(int n_) : n(n_) {
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

private:
    const int INF = 1e18;

    int n, s, t;

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
