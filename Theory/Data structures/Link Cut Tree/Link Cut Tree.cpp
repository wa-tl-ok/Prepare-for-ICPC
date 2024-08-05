class LinkCutTree {
public:
    struct Node {
        int ch[2] = { 0, 0 };
        int p = 0;
        int self = 0;
        int path_max = -2e9;
        int path_min = 2e9;
        int path_sum = 0;
        int sub = 0;
        int vir = 0;
        bool flip = 0;
    };

    LinkCutTree(int n) : T(n + 1) {}

    void Link(int u, int v) {
        reroot(u);
        access(v);

        T[u].p = v;
        T[v].vir += T[u].sub;

        pull(v);
    }

    void Cut(int u, int v) {
        reroot(u);
        access(v);

        T[u].p = 0;
        T[v].ch[0] = 0;

        pull(v);
    }

    int LCA(int u, int v) {
        if (u == v) {
            return u;
        }

        access(u);
        int ret = access(v);

        if (T[u].p) {
            return ret;
        }
        else {
            return 0;
        }
    }

    int Subtree(int u, int v) {
        reroot(v);
        access(u);
        return T[u].vir + T[u].self;
    }

    int Max_query(int u, int v) {
        reroot(u);
        access(v);
        return T[v].path_max;
    }

    int Min_query(int u, int v) {
        reroot(u);
        access(v);
        return T[v].path_min;
    }

    int Sum_query(int u, int v) {
        reroot(u);
        access(v);
        return T[v].path_sum;
    }

    void Plus(int u, int x) {
        access(u);
        T[u].self += x;
        pull(u);
    }
private:
    vector<Node> T;

    void push(int x) {
        if (!x || !T[x].flip) {
            return;
        }

        int l = T[x].ch[0];
        int r = T[x].ch[1];

        T[l].flip ^= 1;
        T[r].flip ^= 1;

        swap(T[x].ch[0], T[x].ch[1]);

        T[x].flip = 0;
    }

    void pull(int x) {
        int l = T[x].ch[0];
        int r = T[x].ch[1];

        push(l);
        push(r);

        T[x].path_max = max({ T[x].self, T[l].path_max, T[r].path_max });
        T[x].path_min = min({ T[x].self, T[l].path_min, T[r].path_min });
        T[x].path_sum = T[x].self + T[l].path_sum + T[r].path_sum;
        T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
    }

    void splay(int x) {
        auto set = [&](int x, int d, int y) {
            T[x].ch[d] = y;
            T[y].p = x;

            pull(x);
        };

        auto dir = [&](int x) {
            int p = T[x].p;

            if (!p) {
                return -1;
            }

            if (T[p].ch[0] == x) {
                return 0;
            }
            else if (T[p].ch[1] == x) {
                return 1;
            }
            else {
                return -1;
            }
        };

        auto rotate = [&](int x) {
            int xp, xpp, dx, dy, ch;

            xp = T[x].p;
            xpp = T[T[x].p].p;

            dx = dir(x);
            dy = dir(xp);

            ch = T[x].ch[!dx];

            set(xp, dx, ch);
            set(x, !dx, xp);

            if (dy != -1) {
                set(xpp, dy, x);
            }

            T[x].p = xpp;
        };

        push(x);

        while (dir(x) != -1) {
            int dx, dy, y, z;

            y = T[x].p;
            z = T[y].p;

            push(z);
            push(y);
            push(x);

            dx = dir(x);
            dy = dir(y);

            if (dy != -1) {
                if (dx != dy) {
                    rotate(x);
                }
                else {
                    rotate(y);
                }
            }

            rotate(x);
        }
    }

    int access(int x) {
        int u = x;
        int v = 0;

        while (u) {
            splay(u);

            T[u].vir += T[T[u].ch[1]].sub;
            T[u].vir -= T[v].sub;
            T[u].ch[1] = v;

            pull(u);

            v = u;
            u = T[u].p;
        }

        return splay(x), v;
    }

    void reroot(int x) {
        access(x);
        T[x].flip ^= 1;
        push(x);
    }
};
