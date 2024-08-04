//https://codeforces.com/contest/342/problem/E

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

using namespace std;

struct SplayNode {
    int value;

    SplayNode* left;
    SplayNode* right;

    SplayNode* parent;
    SplayNode* path_parent;

    SplayNode(int value) :
        value(value),
        left(nullptr), right(nullptr),
        parent(nullptr), path_parent(nullptr) {}

    void rotate() {
        SplayNode* p = parent;
        bool isRightChild = (p->right == this);

        if (p->parent) {
            if (p->parent->right == p) {
                p->parent->right = this;
            }
            else {
                p->parent->left = this;
            }
            parent = p->parent;
        }
        else {
            parent = nullptr;
        }

        if (isRightChild) {
            p->right = left;
            if (left) {
                left->parent = p;
            }
            left = p;
        }
        else {
            p->left = right;
            if (right) {
                right->parent = p;
            }
            right = p;
        }

        p->parent = this;
        path_parent = p->path_parent;
    }

    void splay() {
        while (parent) {
            if (parent->parent) {
                if ((parent->right == this) == (parent->parent->right == parent)) {
                    parent->rotate();
                }
                else {
                    rotate();
                }
            }
            rotate();
        }
    }
};

class LinkCutTree {
public:
    LinkCutTree(int size) : nodes(size) {
        for (int i = 0; i < size; ++i) {
            nodes[i] = new SplayNode(i);
        }
    }

    ~LinkCutTree() {
        for (SplayNode* node : nodes) {
            delete node;
        }
    }

    void link(int par_idx, int child_idx) {
        SplayNode* par = nodes[par_idx];
        SplayNode* child = nodes[child_idx];

        access(child);
        access(par);

        child->left = par;
        if (par) {
            par->parent = child;
        }
    }

    void cut(int node_idx) {
        SplayNode* node = nodes[node_idx];
        access(node);

        if (node->left) {
            node->left->parent = nullptr;
            node->left = nullptr;
        }
    }

    SplayNode* find_root(int node_idx) {
        SplayNode* node = nodes[node_idx];
        access(node);

        while (node->left) {
            node = node->left;
        }

        access(node);
        return node;
    }

    int lca(int u_idx, int v_idx) {
        SplayNode* u = nodes[u_idx];
        SplayNode* v = nodes[v_idx];

        if (find_root(u_idx) != find_root(v_idx)) {
            return -1;
        }

        access(u);
        SplayNode* lca_node = access(v);

        if (lca_node) {
            return lca_node->value;
        }
        else {
            return -1;
        }
    }

private:
    vector<SplayNode*> nodes;

    SplayNode* access(SplayNode* node) {
        node->splay();

        if (node->right) {
            node->right->path_parent = node;
            node->right->parent = nullptr;
        }

        node->right = nullptr;
        SplayNode* par = node;

        while (node->path_parent) {
            par = node->path_parent;
            par->splay();

            if (par->right) {
                par->right->path_parent = par;
                par->right->parent = nullptr;
            }

            par->right = node;

            if (node) {
                node->parent = par;
            }

            node->path_parent = nullptr;
            node->splay();
        }

        return par;
    }
};

vector<set<int>> graph;
vector<int> tree;
vector<int> parent;
int cnt;

int find_centroid(int u, int p) {
    for (auto v : graph[u]) {
        if (v != p) {
            if (tree[v] > cnt) {
                return find_centroid(v, u);
            }
        }
    }
    return u;
}

void dfs_decompose(int u, int p) {
    tree[u] = 1;
    cnt += 1;

    for (auto v : graph[u]) {
        if (v != p) {
            dfs_decompose(v, u);
            tree[u] += tree[v];
        }
    }
}

void decompose(int u, int p = -1) {
    cnt = 0;
    dfs_decompose(u, p);
    cnt /= 2;

    int center = find_centroid(u, p);
    parent[center] = p;

    for (auto v : graph[center]) {
        if (v != p) {
            graph[v].erase(center);
            decompose(v, center);
        }
    }

    graph[center].clear();
}

vector<int> depth;

void dfs(int u, int p, LinkCutTree& lct) {
    for (auto v : graph[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            lct.link(u, v);
            dfs(v, u, lct);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q; cin >> n >> q;

    graph.resize(n);
    LinkCutTree lct(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    depth.resize(n);
    for (int i = 0; i < n; i++) {
        depth[i] = 0;
    }
    dfs(0, 0, lct);

    vector<int> go(n);
    for (int i = 0; i < n; i++) {
        go[i] = depth[i];
    }

    tree.resize(n);
    for (int i = 0; i < n; i++) {
        tree[i] = 0;
    }
    parent.resize(n);
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
    decompose(0);

    while (q > 0) {
        int type, v;
        cin >> type >> v;
        --v;

        if (type == 1) {
            int u = v;

            while (u != -1) {
                go[u] = min(go[u], depth[u] + depth[v] - 2 * depth[lct.lca(u, v)]);
                u = parent[u];
            }
        }
        else {
            int u = v;
            int answer = 1e9;

            while (u != -1) {
                answer = min(answer, depth[u] + depth[v] - 2 * depth[lct.lca(u, v)] + go[u]);
                u = parent[u];
            }

            cout << answer << endl;
        }

        --q;
    }

    return 0;
}
