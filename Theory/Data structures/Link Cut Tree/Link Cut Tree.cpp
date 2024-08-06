#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

    void Print() {
        for (int i = 0; i < (int)T.size(); i++) {
            cout << T[i].self << ' ';
        } cout << endl;
    }

    void Reroot(int x) {
        access(x);
        T[x].flip ^= 1;
        push(x);
    }

    void Link(int u, int v) {
        Reroot(u);
        access(v);

        T[u].p = v;
        T[v].vir += T[u].sub;

        pull(v);
    }

    void Cut(int u, int v) {
        Reroot(u);
        access(v);

        T[u].p = 0;
        T[v].ch[0] = 0;

        pull(v);
    }

    int Max_query(int u, int v) {
        Reroot(u);
        access(v);
        return T[v].path_max;
    }

    int Min_query(int u, int v) {
        Reroot(u);
        access(v);
        return T[v].path_min;
    }

    int Sum_query(int u, int v) {
        Reroot(u);
        access(v);
        return T[v].path_sum;
    }

    void Plus(int u, int x) {
        access(u);
        T[u].self += x;
        pull(u);
    }

    void PlusPath(int u, int v, int x) {
        // realization
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
};

#include <cassert>

int main() {
    LinkCutTree T(5);

    T.Link(1, 2);
    T.Link(1, 3);
    T.Link(3, 4);
    T.Link(3, 5);

    T.Plus(1, 1);
    T.Plus(2, 2);
    T.Plus(3, 3);
    T.Plus(4, 4);
    T.Plus(5, 5);

    T.Reroot(1);

    /*
                       /-\
                      | 1 | 1
                       \-/
                      /  \
                     /    \
                    /     /-\
                  /-\    | 2 | 2
                 | 3 | 3  \-/
                  \-/
                  / \
                 /   \
                /     \
               /      /-\
              /      | 4 | 4
             /        \-/
           /-\
          | 5 | 5
           \-/
    */

    assert(T.Sum_query(1, 1) == 1);
    assert(T.Sum_query(1, 2) == 3);
    assert(T.Sum_query(1, 3) == 4);
    assert(T.Sum_query(1, 4) == 8);
    assert(T.Sum_query(1, 5) == 9);
    assert(T.Sum_query(2, 2) == 2);
    assert(T.Sum_query(2, 3) == 6);
    assert(T.Sum_query(2, 4) == 10);
    assert(T.Sum_query(2, 5) == 11);
    assert(T.Sum_query(3, 3) == 3);
    assert(T.Sum_query(3, 4) == 7);
    assert(T.Sum_query(3, 5) == 8);
    assert(T.Sum_query(4, 4) == 4);
    assert(T.Sum_query(4, 5) == 12);
    assert(T.Sum_query(5, 5) == 5);

    T.Cut(1, 3);
    T.Reroot(1);
    T.Reroot(3);

    assert(T.Sum_query(1, 1) == 1);
    assert(T.Sum_query(1, 2) == 3);
    assert(T.Sum_query(2, 2) == 2);
    assert(T.Sum_query(3, 3) == 3);
    assert(T.Sum_query(3, 4) == 7);
    assert(T.Sum_query(3, 5) == 8);
    assert(T.Sum_query(4, 4) == 4);
    assert(T.Sum_query(4, 5) == 12);
    assert(T.Sum_query(5, 5) == 5);

    T.Link(1, 3);
    T.Reroot(1);

    assert(T.Sum_query(1, 1) == 1);
    assert(T.Sum_query(1, 2) == 3);
    assert(T.Sum_query(1, 3) == 4);
    assert(T.Sum_query(1, 4) == 8);
    assert(T.Sum_query(1, 5) == 9);
    assert(T.Sum_query(2, 2) == 2);
    assert(T.Sum_query(2, 3) == 6);
    assert(T.Sum_query(2, 4) == 10);
    assert(T.Sum_query(2, 5) == 11);
    assert(T.Sum_query(3, 3) == 3);
    assert(T.Sum_query(3, 4) == 7);
    assert(T.Sum_query(3, 5) == 8);
    assert(T.Sum_query(4, 4) == 4);
    assert(T.Sum_query(4, 5) == 12);
    assert(T.Sum_query(5, 5) == 5);

    T.PlusPath(4, 1, 1); T.Print(); // 0 2 2 4 5 5
    T.PlusPath(5, 1, 2); T.Print(); // 0 4 2 6 5 7
    
    /*
                       /-\
                      | 1 | 4
                       \-/
                      /  \
                     /    \
                    /     /-\
                  /-\    | 2 | 2
                 | 3 | 6  \-/
                  \-/
                  / \
                 /   \
                /     \
               /      /-\
              /      | 4 | 5
             /        \-/
           /-\
          | 5 | 7
           \-/
    */

    assert(T.Sum_query(1, 1) == 4);
    assert(T.Sum_query(1, 2) == 6);
    assert(T.Sum_query(1, 3) == 10);
    assert(T.Sum_query(1, 4) == 15);
    assert(T.Sum_query(1, 5) == 17);
    assert(T.Sum_query(2, 2) == 2);
    assert(T.Sum_query(2, 3) == 12);
    assert(T.Sum_query(2, 4) == 17);
    assert(T.Sum_query(2, 5) == 19);
    assert(T.Sum_query(3, 3) == 6);
    assert(T.Sum_query(3, 4) == 11);
    assert(T.Sum_query(3, 5) == 13);
    assert(T.Sum_query(4, 4) == 5);
    assert(T.Sum_query(4, 5) == 18);
    assert(T.Sum_query(5, 5) == 7);

    cout << "OK!";

    return 0;
}
