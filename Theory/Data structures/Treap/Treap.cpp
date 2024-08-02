class Treap {
public:
    struct Node {
        int x, y;

        Node* left;
        Node* right;

        Node(int x, int y) :
            x(x), y(y),
            left(nullptr), right(nullptr) {}
    };

    Treap() : root(nullptr) { std::srand(std::time(0)); }

    void Add(int x) {
        root = insert(root, x, rand());
    }

    void Del(int x) {
        root = delete_key(root, x);
    }

    bool Find(int x) {
        return exists(root, x);
    }

    void Print() const {
        printInOrder(root);
        cout << endl;
    }

private:
    Node* root;

    pair<Node*, Node*> split(Node* a, int k) {
        if (!a) {
            return { nullptr, nullptr };
        }

        if (a->x < k) {
            pair<Node*, Node*> lr = split(a->right, k);

            Node* l = lr.first;
            Node* r = lr.second;

            a->right = l;

            return { a, r };
        }
        else {
            pair<Node*, Node*> lr = split(a->left, k);

            Node* l = lr.first;
            Node* r = lr.second;

            a->left = r;

            return { l, a };
        }
    }

    Node* merge(Node* a, Node* b) {
        if (!a) {
            return b;
        }
        if (!b) {
            return a;
        }
        if (a->y > b->y) {
            a->right = merge(a->right, b);
            return a;
        }
        else {
            b->left = merge(a, b->left);
            return b;
        }
    }

    Node* insert(Node* a, int x, int y) {
        Node* new_node = new Node(x, y);

        pair<Node*, Node*> lr = split(root, x);

        Node* l = lr.first;
        Node* r = lr.second;

        return merge(merge(l, new_node), r);
    }

    Node* delete_key(Node* a, int x) {
        if (!a) {
            return nullptr;
        }

        pair<Node*, Node*> split1 = split(a, x + 1);
        Node* less_or_equal = split1.first;
        Node* greater = split1.second;

        pair<Node*, Node*> split2 = split(less_or_equal, x);
        Node* less = split2.first;
        Node* equal = split2.second;

        Node* merged = merge(less, greater);

        delete equal;
        return merged;
    }

    bool exists(Node* a, int x) {
        if (!a) {
            return false;
        }
        if (a->x == x) {
            return true;
        }
        if (x < a->x) {
            return exists(a->left, x);
        }
        else {
            return exists(a->right, x);
        }
    }

    void printInOrder(Node* node) const {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << node->x << " ";
            printInOrder(node->right);
        }
    }
};
