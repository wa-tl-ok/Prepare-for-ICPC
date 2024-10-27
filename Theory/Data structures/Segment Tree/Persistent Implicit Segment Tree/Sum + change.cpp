class PersistentImplicitSegmentTree {
public:
    PersistentImplicitSegmentTree(int size) : n(size) {
        roots.push_back(nullptr);
    }

    void change(int pos, int val) {
        Node* newRoot = updatePoint(roots.back(), 0, n - 1, pos, val);
        roots.push_back(newRoot);
    }

    int query_v(int version, int l, int r) {
        return queryRange(roots[version], 0, n - 1, l, r);
    }

private:
    struct Node {
        int sum;
        Node* left;
        Node* right;

        Node() : sum(0), left(nullptr), right(nullptr) {}
        Node(Node* left, Node* right, int sum) : left(left), right(right), sum(sum) {}
    };

    vector<Node*> roots;
    int n;

    Node* updatePoint(Node* node, int l, int r, int pos, int val) {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            return new Node(nullptr, nullptr, val);
        }

        int mid = l + (r - l) / 2;
        Node* newNode = new Node(*node);

        if (pos <= mid) {
            newNode->left = updatePoint(node->left, l, mid, pos, val);
        }
        else {
            newNode->right = updatePoint(node->right, mid + 1, r, pos, val);
        }

        newNode->sum = (newNode->left ? newNode->left->sum : 0) + (newNode->right ? newNode->right->sum : 0);

        return newNode;
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
