class SegmentTree2D {
private:
    vector<vector<int>> tree;
    int n, m;

    void update(int x, int y, int val, int nodeX, int nodeY, int xLeft, int xRight, int yLeft, int yRight) {
        if (xLeft == xRight && yLeft == yRight) {
            tree[nodeX][nodeY] += val;
            return;
        }

        int midX = (xLeft + xRight) / 2;
        int midY = (yLeft + yRight) / 2;

        if (x <= midX) {
            if (y <= midY) {
                update(x, y, val, nodeX * 2 + 1, nodeY * 2 + 1, xLeft, midX, yLeft, midY);
            }
            else {
                update(x, y, val, nodeX * 2 + 1, nodeY * 2 + 2, xLeft, midX, midY + 1, yRight);
            }
        }
        else {
            if (y <= midY) {
                update(x, y, val, nodeX * 2 + 2, nodeY * 2 + 1, midX + 1, xRight, yLeft, midY);
            }
            else {
                update(x, y, val, nodeX * 2 + 2, nodeY * 2 + 2, midX + 1, xRight, midY + 1, yRight);
            }
        }

        tree[nodeX][nodeY] =
            tree[nodeX * 2 + 1][nodeY * 2 + 1] +
            tree[nodeX * 2 + 1][nodeY * 2 + 2] +
            tree[nodeX * 2 + 2][nodeY * 2 + 1] +
            tree[nodeX * 2 + 2][nodeY * 2 + 2];
    }

    int query(int x1, int y1, int x2, int y2, int nodeX, int nodeY, int xLeft, int xRight, int yLeft, int yRight) {
        if (x1 > xRight || x2 < xLeft || y1 > yRight || y2 < yLeft) {
            return 0;
        }

        if (x1 <= xLeft && xRight <= x2 && y1 <= yLeft && yRight <= y2) {
            return tree[nodeX][nodeY];
        }

        int midX = (xLeft + xRight) / 2;
        int midY = (yLeft + yRight) / 2;

        int sum = 0;
        sum += query(x1, y1, x2, y2, nodeX * 2 + 1, nodeY * 2 + 1, xLeft, midX, yLeft, midY);
        sum += query(x1, y1, x2, y2, nodeX * 2 + 1, nodeY * 2 + 2, xLeft, midX, midY + 1, yRight);
        sum += query(x1, y1, x2, y2, nodeX * 2 + 2, nodeY * 2 + 1, midX + 1, xRight, yLeft, midY);
        sum += query(x1, y1, x2, y2, nodeX * 2 + 2, nodeY * 2 + 2, midX + 1, xRight, midY + 1, yRight);

        return sum;
    }

public:
    SegmentTree2D(int n, int m) : n(n), m(m) {
        int sizeX = 4 * n;
        int sizeY = 4 * m;
        tree.resize(sizeX, vector<int>(sizeY, 0));
    }

    void update(int x, int y, int value) {
        update(x, y, value, 0, 0, 0, n - 1, 0, m - 1);
    }

    int query(int x1, int y1, int x2, int y2) {
        return query(x1, y1, x2, y2, 0, 0, 0, n - 1, 0, m - 1);
    }
};
