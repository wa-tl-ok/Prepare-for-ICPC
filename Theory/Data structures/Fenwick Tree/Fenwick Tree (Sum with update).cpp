class FenwickTree {
public:
    FenwickTree(int n) : size(n) {
        tree.resize(n + 1, 0);
    }

    void update(int ind, long long x) {
        ++ind;
        while (ind <= size) {
            tree[ind] += x;
            ind += ind & -ind;
        }
    }

    long long query(int ind) const {
        long long sum = 0;

        while (ind > 0) {
            sum += tree[ind];
            ind -= ind & -ind;
        }

        return sum;
    }

    long long range_query(int l, int r) const {
        ++l;
        ++r;
        return query(r) - query(l - 1);
    }
private:
    vector<long long> tree;
    int size;
};
