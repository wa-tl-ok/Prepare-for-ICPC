class FenwickTree {
public:
    FenwickTree(int n) : size(n) {
        tree1.resize(n + 2, 0);
        tree2.resize(n + 2, 0);
    }

    void plus(int l, int r, int x) {
        ++l;
        ++r;

        add(tree1, l, x);
        add(tree1, r + 1, -x);

        add(tree2, l, x * (l - 1));
        add(tree2, r + 1, -x * r);
    }

    int query(int l, int r) const {
        ++l;
        ++r;

        return range_query(r) - range_query(l - 1);
    }

private:
    vector<int> tree1, tree2;
    int size;

    void add(vector<int>& tree, int ind, int x) {
        while (ind <= size) {
            tree[ind] += x;
            ind += ind & -ind;
        }
    }

    int prefix_query(const vector<int>& tree, int ind) const {
        int sum = 0;
        while (ind > 0) {
            sum += tree[ind];
            ind -= ind & -ind;
        }
        return sum;
    }

    int range_query(int ind) const {
        return prefix_query(tree1, ind) * ind - prefix_query(tree2, ind);
    }
};
