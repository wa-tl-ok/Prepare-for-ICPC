class Treap {
public:
    struct Node {
        int x, y;
        int cnt;

        int min;
        int max;
        int sum;

        Node* left;
        Node* right;

        Node(int x) : x(x), y(rand()), cnt(1), min(x), max(x), sum(x),
            left(nullptr), right(nullptr) {}
    };

    Treap() : root(nullptr) {
        srand(static_cast<unsigned>(time(0)));
    }

    void insert(int pos, int x) {
        Node* new_node = new Node(x);
        Node* a;
        Node* b;

        split(root, a, b, pos);

        merge(a, new_node, root);
        merge(root, b, root);
    }

    int queryMin(int i, int j) {
        Node* a;
        Node* b;
        Node* c;

        split(root, a, b, i - 1);
        split(b, b, c, j - i + 1);

        int result = getMin(b);

        merge(a, b, root);
        merge(root, c, root);

        return result;
    }

    int queryMax(int i, int j) {
        Node* a;
        Node* b;
        Node* c;

        split(root, a, b, i - 1);
        split(b, b, c, j - i + 1);

        int result = getMax(b);

        merge(a, b, root);
        merge(root, c, root);

        return result;
    }

    int querySum(int i, int j) {
        Node* a;
        Node* b;
        Node* c;

        split(root, a, b, i - 1);
        split(b, b, c, j - i + 1);

        int result = getSum(b);

        merge(a, b, root);
        merge(root, c, root);

        return result;
    }

private:
    Node* root;

    int cnt(Node* a) {
        if (a) {
            return a->cnt;
        }
        else {
            return 0;
        }
    }

    int getMin(Node* a) {
        if (a) {
            return a->min;
        }
        else {
            return INT_MAX;
        }
    }

    int getMax(Node* a) {
        if (a) {
            return a->max;
        }
        else {
            return INT_MIN;
        }
    }

    int getSum(Node* a) {
        if (a) {
            return a->sum;
        }
        else {
            return 0;
        }
    }

    void upd(Node* a) {
        if (a) {
            a->cnt = 1 + cnt(a->left) + cnt(a->right);
            a->min = min(a->x, min(getMin(a->left), getMin(a->right)));
            a->max = max(a->x, max(getMax(a->left), getMax(a->right)));
            a->sum = a->x + getSum(a->left) + getSum(a->right);
        }
    }

    void merge(Node* l, Node* r, Node*& a) {
        if (!l) {
            a = r;
        }
        else if (!r) {
            a = l;
        }
        else if (l->y > r->y) {
            merge(l->right, r, l->right);
            a = l;
        }
        else {
            merge(l, r->left, r->left);
            a = r;
        }
        upd(a);
    }

    void split(Node* a, Node*& l, Node*& r, int pos) {
        if (!a) {
            l = nullptr;
            r = nullptr;
            return;
        }
        if (pos <= cnt(a->left)) {
            split(a->left, l, a->left, pos);
            r = a;
        }
        else {
            split(a->right, a->right, r, pos - cnt(a->left) - 1);
            l = a;
        }
        upd(a);
    }
};
