#include <iostream> 
#include <algorithm> 
#include <cmath> 
#include <vector> 
#include <queue> 
#include <deque> 
#include <array> 
#include <list> 
#include <stack> 
#include <set> 
#include <unordered_set> 
#include <map> 
#include <unordered_map> 
#include <string> 
#include <cstring> 
#include <random> 
#include <bitset> 
#include <functional> 
#include <iomanip> 

using namespace std;

#define int long long

struct edge {
    int u;
    int v;
    int c;
};

struct Query {
    int type;
    
    int u;
    int v;

    int id;
};

void Solve() {
    vector<int> ANS;

    int N, M, Q; 
    cin >> N >> M >> Q;

    map<int, edge> id;
    map<int, bool> vis;

    for (int i = 1; i <= M; i++) {
        int u, v, c; 
        cin >> u >> v >> c;

        --u;
        --v;

        edge e; 
        e.u = u; 
        e.v = v; 
        e.c = c;

        id[i] = e;
        vis[i] = true;
    }

    vector<Query> q;

    for (int i = 0; i < Q; i++) {
        int type; cin >> type;

        if (type == 1) {
            int ind; cin >> ind;
            vis[ind] = false;

            Query Q;

            Q.type = 1;
            
            Q.u = -1;
            Q.v = -1;

            Q.id = ind;

            q.push_back(Q);
        }
        else {
            int u, v; 
            cin >> u >> v;

            --u;
            --v;

            Query Q;

            Q.type = 2;
            
            Q.u = u;
            Q.v = v;

            Q.id = -1;

            q.push_back(Q);
        }
    }
    
    reverse(q.begin(), q.end());

    vector<vector<int>> DIST(N);
    for (int i = 0; i < N; i++) {
        DIST[i].resize(N);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                DIST[i][j] = 0;
            }
            else {
                DIST[i][j] = 1e18;
            }
        }
    }

    for (int i = 1; i <= M; i++) {
        if (vis[i] == true) {
            DIST[id[i].u][id[i].v] = id[i].c;
            DIST[id[i].v][id[i].u] = id[i].c;
        }
    }

    for (int v = 0; v < N; v++) {
        for (int u = 0; u < N; u++) {
            for (int k = 0; k < N; k++) {
                if (DIST[u][v] + DIST[v][k] < DIST[u][k]) {
                    DIST[u][k] = DIST[u][v] + DIST[v][k];
                }
            }
        }
    }

    for (auto& Q : q) {
        if (Q.type == 1) {
            int ID = Q.id;

            int u = id[ID].u;
            int v = id[ID].v;
            int c = id[ID].c;

            DIST[u][v] = min(DIST[u][v], c);
            DIST[v][u] = min(DIST[v][u], c);

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    DIST[i][j] = min(DIST[i][u] + DIST[u][j], DIST[i][j]);
                    DIST[i][j] = min(DIST[i][v] + DIST[v][j], DIST[i][j]);

                    DIST[j][i] = min(DIST[j][u] + DIST[u][i], DIST[j][i]);
                    DIST[j][i] = min(DIST[j][v] + DIST[v][i], DIST[j][i]);
                }
            }
        }
        else {
            int u = Q.u;
            int v = Q.v;

            if (DIST[u][v] == 1e18) {
                ANS.push_back(-1);
            }
            else {
                ANS.push_back(DIST[u][v]);
            }
        }
    }

    reverse(ANS.begin(), ANS.end());

    for (auto p : ANS) {
        cout << p << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

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

    return 0;
}
