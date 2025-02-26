class ImplicitSegmentTree {
public:
    ImplicitSegmentTree(int size) : n(size), root(nullptr) {}

    void plus(int pos, int val) {
        root = updatePoint(root, 0, n - 1, pos, val);
    }

    int query(int const_l, int const_r) {
        return queryRange(root, 0, n - 1, const_l, const_r);
    }

private:
    struct Node {
        int sum;
        Node* left;
        Node* right;

        Node() : sum(0), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    Node* updatePoint(Node* node, int l, int r, int pos, int val) {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            node->sum += val;
            return node;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            node->left = updatePoint(node->left, l, mid, pos, val);
        }
        else {
            node->right = updatePoint(node->right, mid + 1, r, pos, val);
        }

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
