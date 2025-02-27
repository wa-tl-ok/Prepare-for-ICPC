class ImplicitSegmentTree {
public:
    ImplicitSegmentTree(int size) : n(size), root(nullptr) {}

    void change(int pos, int val) {
        root = updatePoint(root, 0, n - 1, pos, val);
    }

    int query(int left, int right) {
        return queryRange(root, 0, n - 1, left, right);
    }

private:
    struct Node {
        int minVal;
        Node* left;
        Node* right;

        Node() : minVal(std::numeric_limits<int>::max()), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    Node* updatePoint(Node* node, int l, int r, int pos, int val) {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            node->minVal = val;
            return node;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            node->left = updatePoint(node->left, l, mid, pos, val);
        }
        else {
            node->right = updatePoint(node->right, mid + 1, r, pos, val);
        }

        node->minVal = min(getMin(node->left), getMin(node->right));

        return node;
    }

    int queryRange(Node* node, int l, int r, int const_l, int const_r) {
        if (!node) {
            return std::numeric_limits<int>::max();
        }

        if (const_l > r || const_r < l) {
            return std::numeric_limits<int>::max();
        }

        if (const_l <= l && r <= const_r) {
            return node->minVal;
        }

        int mid = l + (r - l) / 2;

        return min(queryRange(node->left, l, mid, const_l, const_r),
            queryRange(node->right, mid + 1, r, const_l, const_r));
    }

    int getMin(Node* node) {
        return node ? node->minVal : std::numeric_limits<int>::max();
    }
};
