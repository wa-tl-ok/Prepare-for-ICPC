class FenwickTree2D {
public:
    FenwickTree2D(int rows, int cols) : rows(rows), cols(cols) {
        field.assign(rows + 1, vector<int>(cols + 1, 0));
    }

    void plus(int x, int y, int value) {
        for (int i = x + 1; i <= rows; i += i & -i) {
            for (int j = y + 1; j <= cols; j += j & -j) {
                field[i][j] += value;
            }
        }
    }

    void change(int x, int y, int value) {
        int current = range_query(x, y, x, y);
        plus(x, y, value - current);
    }

    int query(int x, int y) const {
        int sum = 0;
        for (int i = x + 1; i > 0; i -= i & -i) {
            for (int j = y + 1; j > 0; j -= j & -j) {
                sum += field[i][j];
            }
        }
        return sum;
    }

    int range_query(int x1, int y1, int x2, int y2) const {
        return query(x2, y2)
            - (x1 > 0 ? query(x1 - 1, y2) : 0)
            - (y1 > 0 ? query(x2, y1 - 1) : 0)
            + (x1 > 0 && y1 > 0 ? query(x1 - 1, y1 - 1) : 0);
    }

private:
    vector<vector<int>> field;
    int rows, cols;
};
