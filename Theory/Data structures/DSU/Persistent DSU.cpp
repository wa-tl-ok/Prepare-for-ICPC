struct Persistent_DSU {
    struct Trio {
        int x;
        int y;
        int sz;
    };

    vector<int> head;
    vector<int> rang;
    vector<Trio> condition;

    Persistent_DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }
    }

    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return Find(head[x]);
    }

    bool Union(int x, int y) {
        x = Find(x);
        y = Find(y);

        if (x == y) {
            return false;
        }

        if (rang[x] > rang[y]) {
            swap(x, y);
        }

        rang[y] += rang[x];
        head[x] = y;

        condition.push_back({ x, y, rang[x] });

        return true;
    }

    void Back(int k) {
        for (int i = 0; i < k; i++) {
            auto T = condition[condition.size() - 1];

            int x = T.x;
            int y = T.y;
            int sz = T.sz;

            head[x] = x;
            rang[y] -= sz;

            condition.pop_back();
        }
    }
};
