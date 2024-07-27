class PersistentSegmentTree {
public:
    PersistentSegmentTree(const vector<int>& a) {
        n_ = (int)a.size();
        for (int i = 0; i < (int)a.size(); i++) {
            a_.push_back(a[i]);
        }

        T.push_back(new Node());
        T[0] = build(0, n_ - 1);
    }

    int sum(int l, int r) {
        return query(T[T.size() - 1], 0, n_ - 1, l, r);
    }

    void upd(int pos, int x) {
        int p = (int)T.size();
        T.push_back(new Node());
        T[p] = update(T[p - 1], 0, n_ - 1, pos, x);
    }

private:
    struct Node {
        int val;
        Node* l;
        Node* r;

        Node() : val(0), l(NULL), r(NULL) {}

        Node(Node* l, Node* r) : l(l), r(r) {
            val = l->val + r->val;
        }

        Node(int vi) : l(NULL), r(NULL) {
            this->val = vi;
        }
    };

    int n_;

    vector<int> a_;
    vector<Node*> T;

    Node* build(int l, int r) {
        if (l == r) {
            return new Node(a_[l]);
        }
        else {
            int mid = (l + r) / 2;
            return new Node(build(l, mid), build(mid + 1, r));
        }
    }

    Node* update(Node* t, int l, int r, int pos, int val) {
        if (l == r) {
            return new Node(val);
        }
        else {
            int mid = (l + r) / 2;
            if (pos <= mid) {
                return new Node(update(t->l, l, mid, pos, val), t->r);
            }
            else {
                return new Node(t->l, update(t->r, mid + 1, r, pos, val));
            }
        }
    }

    int query(Node* v, int l, int r, int const_l, int const_r) {
        if (l > const_r || r < const_l) {
            return 0;
        }

        if (l >= const_l && r <= const_r) {
            return v->val;
        }

        int mid = (l + r) / 2;

        int q1 = query(v->l, l, mid, const_l, const_r);
        int q2 = query(v->r, mid + 1, r, const_l, const_r);

        return q1 + q2;
    }
};
