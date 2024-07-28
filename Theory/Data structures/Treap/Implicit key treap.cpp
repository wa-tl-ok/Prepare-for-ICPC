class Treap {
public:
    struct Node {
        int X;
        int Y;

        int cnt;

        int sum;
        int minVal;
        int maxVal;

        bool rev;

        Node* l;
        Node* r;

        Node(int v) :
            X(v), Y(rand()),
            cnt(1),
            sum(v), minVal(v), maxVal(v),
            rev(false),
            l(nullptr), r(nullptr) {}
    };

    Treap() : root(nullptr), size(0) {
        srand(static_cast<unsigned>(time(0)));
    }

    ~Treap() {
        Clear();
    }

    void Add(int p, int x) {
        if (p == -1) {
            p = size;
        }

        Node* newNode = new Node(x);

        Node* A, * B;
        split(root, A, B, p + 1);

        root = merge(merge(A, newNode), B);

        ++size;
    }

    void Rev(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        if (M) {
            M->rev ^= 1;
        }

        root = merge(merge(A, M), B);
    }

    int Sum(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        int result;
        if (M) {
            result = M->sum;
        }
        else {
            result = 0;
        }

        root = merge(merge(A, M), B);

        return result;
    }

    int Min(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        int result;
        if (M) {
            result = M->minVal;
        }
        else {
            result = 2e9;
        }

        root = merge(merge(A, M), B);

        return result;
    }

    int Max(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        int result;
        if (M) {
            result = M->maxVal;
        }
        else {
            result = -2e9;
        }

        root = merge(merge(A, M), B);

        return result;
    }

    void Upd(int p, int new_val) {
        ++p;

        Node* A, * B, * M;

        split(root, A, B, p);
        split(A, A, M, p - 1);

        if (M) {
            M->X = new_val;
            M->sum = new_val;
            M->minVal = new_val;
            M->maxVal = new_val;
        }

        root = merge(merge(A, M), B);
    }

    void Plus(int p, int x) {
        ++p;

        Node* A, * B, * M;

        split(root, A, B, p);
        split(A, A, M, p - 1);

        if (M) {
            M->X += x;
            M->sum += x;
            M->minVal += x;
            M->maxVal += x;
            
            updateNode(M);
        }

        root = merge(merge(A, M), B);
    }

    void Del(int pos) {
        ++pos;

        Node* A, * B, * M;

        split(root, A, B, pos);
        split(A, A, M, pos - 1);

        delete M;

        root = merge(A, B);
        --size;
    }

    void Clear() {
        clearTree(root);
        root = nullptr;
        size = 0;
    }

    void Print() {
        printTree(root);
        cout << endl;
    }

    int Size() {
        return size;
    }

private:
    Node* root;
    int size;

    int min(int a, int b) {
        if (a < b) {
            return a;
        }
        return b;
    }

    int max(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    }

    void push(Node* v) {
        if (v && v->rev) {
            v->rev = false;

            swap(v->l, v->r);

            if (v->l) {
                v->l->rev ^= true;
            }

            if (v->r) {
                v->r->rev ^= true;
            }
        }
    }

    void updateNode(Node* v) {
        if (v) {
            v->cnt = (v->l ? v->l->cnt : 0) + (v->r ? v->r->cnt : 0) + 1;
            v->sum = (v->l ? v->l->sum : 0) + (v->r ? v->r->sum : 0) + v->X;
            v->minVal = min(v->X, min(v->l ? v->l->minVal : 2e9, v->r ? v->r->minVal : 2e9));
            v->maxVal = max(v->X, max(v->l ? v->l->maxVal : -2e9, v->r ? v->r->maxVal : -2e9));
        }
    }

    void split(Node* v, Node*& A, Node*& B, int x, int now = 0) {
        if (!v) {
            A = nullptr;
            B = nullptr;
            return;
        }

        push(v);

        int cur = now + 1;
        if (v->l) {
            cur += v->l->cnt;
        }

        if (x < cur) {
            split(v->l, A, v->l, x, now);
            B = v;
        }
        else {
            int offset = now + 1;
            if (v->l) {
                offset += v->l->cnt;
            }

            split(v->r, v->r, B, x, offset);
            A = v;
        }

        updateNode(v);
    }

    Node* merge(Node* A, Node* B) {
        if (!A) {
            return B;
        }
        if (!B) {
            return A;
        }

        push(A);
        push(B);

        if (A->Y > B->Y) {
            A->r = merge(A->r, B);

            updateNode(A);

            return A;
        }
        else {
            B->l = merge(A, B->l);

            updateNode(B);

            return B;
        }
    }

    void clearTree(Node* A) {
        if (!A) {
            return;
        }

        clearTree(A->l);
        clearTree(A->r);

        delete A;
    }

    void printTree(Node* v) {
        if (!v) {
            return;
        }
        push(v);
        printTree(v->l);
        cout << v->X << " ";
        printTree(v->r);
    }
};
