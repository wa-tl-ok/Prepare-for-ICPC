class Treap {
public:
    struct Node {
        int x, y;
        int count;
        int size;
        Node* left;
        Node* right;

        Node(int x, int y) :
            x(x), y(y), count(1), size(1),
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

    int Find_ll(int x) {
        ans_ll = -1;
        find_ll(root, x);
        return ans_ll;
    }

    int Find_lr(int x) {
        ans_lr = -1;
        find_lr(root, x);
        return ans_lr;
    }

    int Find_rl(int x) {
        ans_rl = -1;
        find_rl(root, x);
        return ans_rl;
    }

    int Find_rr(int x) {
        ans_rr = -1;
        find_rr(root, x);
        return ans_rr;
    }

    int Min_from_k_max_elems(int k) {
        int total_size = get_size(root);
        return Kth(total_size - k + 1);
    }

    int Max_from_k_min_elems(int k) {
        return Kth(k);
    }

private:
    Node* root;
    int ans_ll, ans_lr, ans_rl, ans_rr;

    int get_size(Node* a) {
        return a ? a->size : 0;
    }

    void update_size(Node* a) {
        if (a) {
            a->size = get_size(a->left) + get_size(a->right) + a->count;
        }
    }

    pair<Node*, Node*> split(Node* a, int k) {
        if (!a) {
            return { nullptr, nullptr };
        }
        if (a->x < k) {
            pair<Node*, Node*> lr = split(a->right, k);
            a->right = lr.first;
            update_size(a);
            return { a, lr.second };
        }
        else {
            pair<Node*, Node*> lr = split(a->left, k);
            a->left = lr.second;
            update_size(a);
            return { lr.first, a };
        }
    }

    Node* merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->y > b->y) {
            a->right = merge(a->right, b);
            update_size(a);
            return a;
        }
        else {
            b->left = merge(a, b->left);
            update_size(b);
            return b;
        }
    }

    Node* insert(Node* a, int x, int y) {
        pair<Node*, Node*> lr = split(a, x);
        Node* l = lr.first;
        Node* r = lr.second;

        if (l && l->x == x) {
            l->count++;
            update_size(l);
            return merge(l, r);
        }

        Node* new_node = new Node(x, y);
        return merge(merge(l, new_node), r);
    }

    Node* delete_key(Node* a, int x) {
        if (!a) return nullptr;

        if (a->x == x) {
            if (a->count > 1) {
                a->count--;
                update_size(a);
                return a;
            }
            else {
                return merge(a->left, a->right);
            }
        }

        if (x < a->x) {
            a->left = delete_key(a->left, x);
        }
        else {
            a->right = delete_key(a->right, x);
        }

        update_size(a);
        return a;
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

    void find_ll(Node* a, int x) {
        if (!a) return;
        if (a->x < x) {
            ans_ll = a->x;
            find_ll(a->right, x); 
        }
        else {
            find_ll(a->left, x); 
        }
    }

    void find_lr(Node* a, int x) {
        if (!a) return;
        if (a->x <= x) {
            ans_lr = a->x;
            find_lr(a->right, x);
        }
        else {
            find_lr(a->left, x); 
        }
    }

    void find_rl(Node* a, int x) {
        if (!a) return;
        if (a->x >= x) {
            ans_rl = a->x;
            find_rl(a->left, x); 
        }
        else {
            find_rl(a->right, x); 
        }
    }

    void find_rr(Node* a, int x) {
        if (!a) return;
        if (a->x > x) {
            ans_rr = a->x;
            find_rr(a->left, x); 
        }
        else {
            find_rr(a->right, x); 
        }
    }

    int Kth(int k) {
        Node* a = root;
        while (a) {
            int left_size = get_size(a->left);

            if (k <= left_size) {
                a = a->left;
            }
            else if (k <= left_size + a->count) {
                return a->x;
            }
            else {
                k -= left_size + a->count;
                a = a->right;
            }
        }
        return -1;
    }
};
