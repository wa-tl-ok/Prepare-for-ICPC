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
