class FenwickTree3D {
public:
    FenwickTree3D(int size) : size(size) {
        field.assign(size + 1, vector<vector<int>>(size + 1, vector<int>(size + 1, 0)));
    }

    void plus(int x, int y, int z, int value) {
        for (int i = x + 1; i <= size; i += i & -i) {
            for (int j = y + 1; j <= size; j += j & -j) {
                for (int k = z + 1; k <= size; k += k & -k) {
                    field[i][j][k] += value;
                }
            }
        }
    }

    void change(int x, int y, int z, ll value) {
        value = value - field[x][y][z];
        for (int i = x + 1; i <= size; i += i & -i) {
            for (int j = y + 1; j <= size; j += j & -j) {
                for (int k = z + 1; k <= size; k += k & -k) {
                    field[i][j][k] += value;
                }
            }
        }
    }

    int query(int x, int y, int z) const {
        int sum = 0;
        for (int i = x + 1; i > 0; i -= i & -i) {
            for (int j = y + 1; j > 0; j -= j & -j) {
                for (int k = z + 1; k > 0; k -= k & -k) {
                    sum += field[i][j][k];
                }
            }
        }
        return sum;
    }

    int range_query(int x1, int y1, int z1, int x2, int y2, int z2) const {
        return query(x2, y2, z2)
            - (x1 > 0 ? query(x1 - 1, y2, z2) : 0)
            - (y1 > 0 ? query(x2, y1 - 1, z2) : 0)
            - (z1 > 0 ? query(x2, y2, z1 - 1) : 0)
            + (x1 > 0 && y1 > 0 ? query(x1 - 1, y1 - 1, z2) : 0)
            + (x1 > 0 && z1 > 0 ? query(x1 - 1, y2, z1 - 1) : 0)
            + (y1 > 0 && z1 > 0 ? query(x2, y1 - 1, z1 - 1) : 0)
            - (x1 > 0 && y1 > 0 && z1 > 0 ? query(x1 - 1, y1 - 1, z1 - 1) : 0);
    }

private:
    vector<vector<vector<int>>> field;
    int size;
};
