class BitwiseSegmentTree {
public:
    BitwiseSegmentTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    void update_and(int l, int r, int val) {
        update_and(1, 0, n - 1, l, r, val);
    }

    void update_or(int l, int r, int val) {
        update_or(1, 0, n - 1, l, r, val);
    }

    int query_max(int l, int r) {
        return query_max(1, 0, n - 1, l, r);
    }

    int query_min(int l, int r) {
        return query_min(1, 0, n - 1, l, r);
    }

    int query_sum(int l, int r) {
        return query_sum(1, 0, n - 1, l, r);
    }

private:
    struct Node {
        int all_or, all_and, lz_or, lz_and, lz_xor, max, min, sum;

        Node() : all_or(0), all_and((1 << 20) - 1), lz_or(0), lz_and((1 << 20) - 1), lz_xor(0), 
            max(0), min((1 << 20) - 1), sum(0) {}

        void apply_and(int val) {
            if (val == (1 << 20) - 1) {
                return;
            }

            all_or &= val; all_and &= val; lz_or &= val; lz_and &= val; max &= val; min &= val; sum &= val;
        }

        void apply_or(int val) {
            if (val == 0) {
                return;
            }

            all_or |= val; all_and |= val; lz_or |= val;  lz_and |= val; max |= val; min |= val; sum |= val;
        }

        static Node merge(const Node& node_1, const Node& node_2) {
            Node new_node;

            new_node.max = Max(node_1.max, node_2.max);
            new_node.min = Min(node_1.min, node_2.min);
            new_node.sum = Sum(node_1.sum, node_2.sum);

            new_node.all_or = node_1.all_or | node_2.all_or;
            new_node.all_and = node_1.all_and & node_2.all_and;

            return new_node;
        }

        static int Max(int a, int b) {
            return (a > b) ? a : b;
        }

        static int Min(int a, int b) {
            return (a < b) ? a : b;
        }

        static int Sum(int a, int b) {
            return a + b;
        }
    };

    static int Max(int a, int b) {
        return (a > b) ? a : b;
    }

    static int Min(int a, int b) {
        return (a < b) ? a : b;
    }

    static int Sum(int a, int b) {
        return a + b;
    }

    vector<Node> tree;
    int n;

    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[v].all_and = a[l]; tree[v].all_or = a[l]; tree[v].max = a[l]; tree[v].min = a[l]; tree[v].sum = a[l];
        }
        else {
            int mid = (l + r) / 2;

            build(2 * v, l, mid, a);
            build(2 * v + 1, mid + 1, r, a);

            tree[v] = Node::merge(tree[2 * v], tree[2 * v + 1]);
        }
    }

    void push_down(int v, int l, int r) {
        if (l == r) {
            return;
        }

        if (tree[v].lz_and != (1 << 20) - 1) {
            tree[2 * v].apply_and(tree[v].lz_and);
            tree[2 * v + 1].apply_and(tree[v].lz_and);
            tree[v].lz_and = (1 << 20) - 1;
        }
        if (tree[v].lz_or != 0) {
            tree[2 * v].apply_or(tree[v].lz_or);
            tree[2 * v + 1].apply_or(tree[v].lz_or);
            tree[v].lz_or = 0;
        }
    }

    void update_and(int v, int l, int r, int const_l, int const_r, int val) {
        push_down(v, l, r);

        if (const_l > r || const_r < l) {
            return;
        }

        if (const_l <= l && r <= const_r && ((tree[v].all_and ^ tree[v].all_or) & ~val) == 0) {
            tree[v].apply_and(val);
            return;
        }

        int mid = (l + r) / 2;

        update_and(2 * v, l, mid, const_l, const_r, val);
        update_and(2 * v + 1, mid + 1, r, const_l, const_r, val);

        tree[v] = Node::merge(tree[2 * v], tree[2 * v + 1]);
    }

    void update_or(int v, int l, int r, int const_l, int const_r, int val) {
        push_down(v, l, r);

        if (const_l > r || const_r < l) {
            return;
        }

        if (const_l <= l && r <= const_r && ((tree[v].all_and ^ tree[v].all_or) & val) == 0) {
            tree[v].apply_or(val);
            return;
        }

        int mid = (l + r) / 2;

        update_or(2 * v, l, mid, const_l, const_r, val);
        update_or(2 * v + 1, mid + 1, r, const_l, const_r, val);

        tree[v] = Node::merge(tree[2 * v], tree[2 * v + 1]);
    }

    int query_max(int v, int l, int r, int const_l, int const_r) {
        push_down(v, l, r);

        if (const_l > r || const_r < l) {
            return 0;
        }

        if (const_l <= l && r <= const_r) {
            return tree[v].max;
        }

        int mid = (l + r) / 2;

        int Left = query_max(2 * v, l, mid, const_l, const_r);
        int Right = query_max(2 * v + 1, mid + 1, r, const_l, const_r);

        return Max(Left, Right);
    }

    int query_min(int v, int l, int r, int const_l, int const_r) {
        push_down(v, l, r);

        if (const_l > r || const_r < l) {
            return (1 << 20) - 1;
        }

        if (const_l <= l && r <= const_r) {
            return tree[v].min;
        }

        int mid = (l + r) / 2;

        int Left = query_min(2 * v, l, mid, const_l, const_r);
        int Right = query_min(2 * v + 1, mid + 1, r, const_l, const_r);

        return Min(Left, Right);
    }

    int query_sum(int v, int l, int r, int const_l, int const_r) {
        push_down(v, l, r);

        if (const_l > r || const_r < l) {
            return 0;
        }

        if (const_l <= l && r <= const_r) {
            return tree[v].sum;
        }

        int mid = (l + r) / 2;

        int Left = query_sum(2 * v, l, mid, const_l, const_r);
        int Right = query_sum(2 * v + 1, mid + 1, r, const_l, const_r);

        return Sum(Left, Right);
    }
};
