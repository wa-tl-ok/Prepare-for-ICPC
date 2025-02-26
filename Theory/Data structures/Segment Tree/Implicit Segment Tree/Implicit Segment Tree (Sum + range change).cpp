class ImplicitSegmentTree {
public:
    ImplicitSegmentTree(int size) : n(size), root(nullptr) {}
 
    void change(int const_l, int const_r, int val) {
        root = updateRange(root, 0, n - 1, const_l, const_r, val);
    }
 
    int query(int const_l, int const_r) {
        return queryRange(root, 0, n - 1, const_l, const_r);
    }
 
private:
    struct Node {
        int sum;
        int lazy;
 
        Node* left;
        Node* right;
 
        Node() : sum(0), lazy(0), left(nullptr), right(nullptr) {}
    };
 
    Node* root;
    int n;
 
    void propagate(Node* node, int l, int r) {
        if (!node || node->lazy == -1) {
            return;
        }
 
        node->sum = node->lazy * (r - l + 1);
 
        if (l != r) {
            if (!node->left) {
                node->left = new Node();
            }
 
            if (!node->right) {
                node->right = new Node();
            }
 
            node->left->lazy = node->lazy;
            node->right->lazy = node->lazy;
        }
 
        node->lazy = -1;
    }
 
    Node* updateRange(Node* node, int l, int r, int const_l, int const_r, int val) {
        if (!node) {
            node = new Node();
        }
 
        propagate(node, l, r);
 
        if (const_l > r || const_r < l) {
            return node;
        }
 
        if (const_l <= l && r <= const_r) {
            node->lazy = val;
            propagate(node, l, r);
 
            return node;
        }
 
        int mid = l + (r - l) / 2;
 
        node->left = updateRange(node->left, l, mid, const_l, const_r, val);
        node->right = updateRange(node->right, mid + 1, r, const_l, const_r, val);
 
        node->sum = 0;
        if (node->left) {
            node->sum += node->left->sum;
        }
        if (node->right) {
            node->sum += node->right->sum;
        }
 
        return node;
    }
 
    int queryRange(Node* node, int l, int r, int const_l, int const_r) {
        if (!node) {
            return 0;
        }
 
        propagate(node, l, r);
 
        if (const_l > r || const_r < l) {
            return 0;
        }
 
        if (const_l <= l && r <= const_r) {
            return node->sum;
        }
 
        int mid = l + (r - l) / 2;
 
        int leftSum = queryRange(node->left, l, mid, const_l, const_r);
        int rightSum = queryRange(node->right, mid + 1, r, const_l, const_r);
 
        return leftSum + rightSum;
    }
};
