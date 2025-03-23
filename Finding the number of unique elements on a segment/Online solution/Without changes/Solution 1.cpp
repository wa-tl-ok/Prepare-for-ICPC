class SegmentTree2D {
private:
    struct Node {
        map<int, Node*> children;
        int value = 0;
    };

    Node* root;

    void update(Node*& node, int x, int y, int val, int xLeft, int xRight, int yLeft, int yRight) {
        if (!node) {
            node = new Node();
        }

        if (xLeft == xRight && yLeft == yRight) {
            node->value += val;
            return;
        }

        int midX = (xLeft + xRight) / 2;
        int midY = (yLeft + yRight) / 2;

        if (x <= midX) {
            if (y <= midY) {
                update(node->children[0], x, y, val, xLeft, midX, yLeft, midY);
            }
            else {
                update(node->children[1], x, y, val, xLeft, midX, midY + 1, yRight);
            }
        }
        else {
            if (y <= midY) {
                update(node->children[2], x, y, val, midX + 1, xRight, yLeft, midY);
            }
            else {
                update(node->children[3], x, y, val, midX + 1, xRight, midY + 1, yRight);
            }
        }

        node->value = 0;
        for (auto& [_, child] : node->children) {
            if (child) {
                node->value += child->value;
            }
        }
    }

    int query(Node* node, int x1, int y1, int x2, int y2, int xLeft, int xRight, int yLeft, int yRight) {
        if (!node || x1 > xRight || x2 < xLeft || y1 > yRight || y2 < yLeft) {
            return 0;
        }

        if (x1 <= xLeft && xRight <= x2 && y1 <= yLeft && yRight <= y2) {
            return node->value;
        }

        int midX = (xLeft + xRight) / 2;
        int midY = (yLeft + yRight) / 2;

        int sum = 0;
        sum += query(node->children[0], x1, y1, x2, y2, xLeft, midX, yLeft, midY);
        sum += query(node->children[1], x1, y1, x2, y2, xLeft, midX, midY + 1, yRight);
        sum += query(node->children[2], x1, y1, x2, y2, midX + 1, xRight, yLeft, midY);
        sum += query(node->children[3], x1, y1, x2, y2, midX + 1, xRight, midY + 1, yRight);

        return sum;
    }

public:
    SegmentTree2D() { root = nullptr; }

    void update(int x, int y, int value) {
        update(root, x, y, value, 0, inf, 0, inf);
    }

    int query(int x1, int y1, int x2, int y2) {
        return query(root, x1, y1, x2, y2, 0, inf, 0, inf);
    }
};

class PersistentImplicitSegmentTree {
public:
    PersistentImplicitSegmentTree(int size) : n(size) {
        roots.push_back(nullptr);
    }

    void plus(int pos, int val) {
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
            return new Node(nullptr, nullptr, node->sum + val);
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

void Solve(int n, vector<int> a, int q, vector<pair<int, int>> Q) {
    for (int i = n; i < 3 * n; i++) {
        a.push_back(a[i - n]);
    }

    PersistentImplicitSegmentTree PST_to_left(inf);

    map<int, int> last_id;
    for (int i = 0; i < 3 * n; i++) {
        last_id[a[i]] = -1;
    }

    vector<int> last(3 * n);
    for (int i = 0; i < 3 * n; i++) {
        if (i >= n && i < 2 * n) {
            PST_to_left.plus(last_id[a[i]], 1);
        }

        last[i] = 1'000'000 - last_id[a[i]];
        last_id[a[i]] = i;
    }

    PersistentImplicitSegmentTree PST_to_right(inf);

    map<int, int> future_id;
    for (int i = 0; i < 3 * n; i++) {
        future_id[a[i]] = 3 * n;
    }

    vector<int> future(3 * n);
    for (int i = 3 * n - 1; i >= 0; i--) {
        if (i >= n && i < 2 * n) {
            PST_to_right.plus(future_id[a[i]], 1);
        }

        future[i] = future_id[a[i]];
        future_id[a[i]] = i;
    }

    vector<int> X;
    for (int i = n; i < 2 * n; i++) {
        X.push_back(last[i]);
    }

    vector<int> Y;
    for (int i = n; i < 2 * n; i++) {
        Y.push_back(future[i]);
    }

    vector<pair<int, int>> points;
    for (int i = 0; i < n; i++) {
        points.push_back({ X[i], Y[i] });
    }

    SegmentTree2D ST;
    for (auto p : points) {
        ST.update(p.first, p.second, 1);
    }

    vector<int> ANS;

    for (int i = 0; i < q; i++) {
        int l, r;

        l = Q[i].first;
        r = Q[i].second;

        --l; l += n;
        --r; r += n;

        int min_X = 1'000'000 - l;
        int min_Y = r;

        int ans = ST.query(min_X + 1, min_Y + 1, inf, inf);

        ans = ans - (PST_to_left.query_v(n, -inf, l - 1) - PST_to_left.query_v(r + 1 - n, -inf, l - 1)) -
            (PST_to_right.query_v(n, r + 1, inf) - PST_to_right.query_v(2 * n - l, r + 1, inf));

        ANS.push_back(ans);
    }

    for (int i = 0; i < q; i++) {
        cout << ANS[i] << '\n';
    }
}
