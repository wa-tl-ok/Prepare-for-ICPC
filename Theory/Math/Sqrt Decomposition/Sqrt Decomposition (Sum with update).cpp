class SqrtDecomposition {
public:
    SqrtDecomposition(const vector<int>& a) {
        n = a.size();
        block_size = sqrt(n) + 1;
        blocks.resize(block_size, 0);
        lazy.resize(block_size, { 0, 0 });
        vec = a;

        for (int i = 0; i < n; ++i) {
            blocks[i / block_size] += a[i];
        }
    }

    int query(int l, int r) {
        int sum = 0;
        int start_block = l / block_size;
        int end_block = r / block_size;

        if (start_block == end_block) {
            apply_lazy(start_block);
            for (int i = l; i <= r; ++i) {
                sum += vec[i];
            }
        }
        else {
            int end_L = (start_block + 1) * block_size - 1;
            int start_R = end_block * block_size;

            apply_lazy(start_block);
            for (int i = l; i <= end_L; ++i) {
                sum += vec[i];
            }

            for (int block = start_block + 1; block < end_block; ++block) {
                if (lazy[block].second) {
                    sum += lazy[block].first * block_size;
                }
                else {
                    sum += blocks[block] + lazy[block].first * block_size;
                }
            }

            apply_lazy(end_block);
            for (int i = start_R; i <= r; ++i) {
                sum += vec[i];
            }
        }

        return sum;
    }

    void plus(int l, int r, int value) {
        int start_block = l / block_size;
        int end_block = r / block_size;

        if (start_block == end_block) {
            apply_lazy(start_block);
            for (int i = l; i <= r; ++i) {
                vec[i] += value;
                blocks[start_block] += value;
            }
        }
        else {
            int end_L = (start_block + 1) * block_size - 1;
            int start_R = end_block * block_size;

            apply_lazy(start_block);
            for (int i = l; i <= end_L; ++i) {
                vec[i] += value;
                blocks[start_block] += value;
            }

            for (int block = start_block + 1; block < end_block; ++block) {
                lazy[block].first += value;
            }

            apply_lazy(end_block);
            for (int i = start_R; i <= r; ++i) {
                vec[i] += value;
                blocks[end_block] += value;
            }
        }
    }

    void change(int l, int r, int value) {
        int start_block = l / block_size;
        int end_block = r / block_size;

        if (start_block == end_block) {
            apply_lazy(start_block);
            for (int i = l; i <= r; ++i) {
                vec[i] = value;
            }
            rebuild_block(start_block);
        }
        else {
            int end_L = (start_block + 1) * block_size - 1;
            int start_R = end_block * block_size;

            apply_lazy(start_block);
            for (int i = l; i <= end_L; ++i) {
                vec[i] = value;
            }
            rebuild_block(start_block);

            for (int block = start_block + 1; block < end_block; ++block) {
                lazy[block] = { value, 1 };
            }

            apply_lazy(end_block);
            for (int i = start_R; i <= r; ++i) {
                vec[i] = value;
            }
            rebuild_block(end_block);
        }
    }

private:
    int n;
    int block_size;
    vector<int> blocks;
    vector<pair<int, int>> lazy;
    vector<int> vec;

    void apply_lazy(int block) {
        if (lazy[block].second) {
            for (int i = block * block_size; i < (block + 1) * block_size && i < n; ++i) {
                vec[i] = lazy[block].first;
            }
            blocks[block] = lazy[block].first * block_size;
            lazy[block] = { 0, 0 };
        }
        else if (lazy[block].first != 0) {
            for (int i = block * block_size; i < (block + 1) * block_size && i < n; ++i) {
                vec[i] += lazy[block].first;
            }
            blocks[block] += lazy[block].first * block_size;
            lazy[block].first = 0;
        }
    }

    void rebuild_block(int block) {
        blocks[block] = 0;
        for (int i = block * block_size; i < (block + 1) * block_size && i < n; ++i) {
            blocks[block] += vec[i];
        }
    }
};
