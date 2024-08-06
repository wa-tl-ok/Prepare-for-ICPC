#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <functional>
#include <chrono>
#include <cassert>

using namespace std;

class LinkCutTree {
public:
    struct Node {
        int val;
        int low_sum;
        int add;

        bool rev;
        int sz;

        Node* l;
        Node* r;
        Node* p;

        Node(int value) :
            val(value), low_sum(value), add(0),
            rev(false),
            sz(1),
            l(nullptr), r(nullptr), p(nullptr) {}

        bool isroot() {
            if (p == nullptr) {
                return true;
            }
            if (p->l != this && p->r != this) {
                return true;
            }
            return false;
        }

        void apply(int v) {
            val += v;
            low_sum += v * sz;
            add += v;
        }

        void push() {
            if (rev) {
                rev = false;
                swap(l, r);

                if (l != nullptr) {
                    l->rev = !l->rev;
                }
                if (r != nullptr) {
                    r->rev = !r->rev;
                }
            }
            if (add != 0) {
                if (l != nullptr) {
                    l->apply(add);
                }
                if (r != nullptr) {
                    r->apply(add);
                }

                add = 0;
            }
        }

        void pull() {
            low_sum = val + get_low_sum(l) + get_low_sum(r);
            sz = 1 + get_size(l) + get_size(r);
        }

        static int get_low_sum(Node* root) {
            if (root == nullptr) {
                return 0;
            }
            else {
                return root->low_sum;
            }
        }

        static int get_size(Node* root) {
            if (root == nullptr) {
                return 0;
            }
            else {
                return root->sz;
            }
        }
    };

    LinkCutTree(int n) {
        for (int i = 0; i < n; i++) {
            Add(i + 1, 0);
        }
    }

    LinkCutTree(const vector<int> a) {
        for (int i = 0; i < (int)a.size(); i++) {
            Add(i + 1, a[i]);
        }
    }

    Node* Add(int ind, int value) {
        Node* newNode = new Node(value);
        nodes[ind] = newNode;
        return newNode;
    }

    Node* Get(int value) {
        if (nodes.count(value)) {
            return nodes[value];
        }
        else {
            return nullptr;
        }

    }

    bool Check_connected(int x_ind, int y_ind) {
        Node* x = Get(x_ind);
        Node* y = Get(y_ind);

        if (!x || !y) {
            return false;
        }

        expose(x);
        expose(y);

        if (x->p != nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    void Link(int x_ind, int y_ind) {
        Node* x = Get(x_ind);
        Node* y = Get(y_ind);

        if (!x || !y) {
            return;
        }

        if (!Check_connected(x_ind, y_ind)) {
            make_root(x);
            x->p = y;
        }
    }

    void Cut(int x_ind, int y_ind) {
        Node* x = Get(x_ind);
        Node* y = Get(y_ind);

        if (!x || !y) {
            return;
        }

        make_root(x);
        expose(y);

        if (y->r == x && x->l == nullptr) {
            y->r->p = nullptr;
            y->r = nullptr;
        }
    }

    int Query(int from_ind, int to_ind) {
        Node* from = Get(from_ind);
        Node* to = Get(to_ind);

        if (!from || !to) {
            return 0;
        }

        make_root(from);
        expose(to);

        return Node::get_low_sum(to);
    }

    void Modify(int from_ind, int to_ind, int Q) {
        Node* from = Get(from_ind);
        Node* to = Get(to_ind);

        if (!from || !to) {
            return;
        }

        make_root(from);
        expose(to);

        to->apply(Q);
    }

private:
    struct custom_hash {
        static uint64_t splitmix64(uint64_t x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        size_t operator()(uint64_t x) const {
            static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + FIXED_RANDOM);
        }
    };

    unordered_map<int, Node*, custom_hash> nodes;

    void connect(Node* ch, Node* p, int is_left_child) {
        if (ch != nullptr) {
            ch->p = p;
        }
        if (is_left_child != 2) {
            if (is_left_child) {
                p->l = ch;
            }
            else {
                p->r = ch;
            }
        }
    }

    void rotate(Node* x) {
        Node* p = x->p;
        Node* g = p->p;

        bool isRoot_p = p->isroot();

        if (x == p->l) {
            connect(x->r, p, 1);
            connect(p, x, 0);
        }
        else {
            connect(x->l, p, 0);
            connect(p, x, 1);
        }

        if (isRoot_p == 1) {
            connect(x, g, 2);
        }
        else {
            if (p == g->l) {
                connect(x, g, 1);
            }
            else {
                connect(x, g, 0);
            }
        }

        p->pull();
    }

    void splay(Node* x) {
        while (!x->isroot()) {
            Node* p = x->p;
            Node* g = p->p;

            if (p->isroot() == false) {
                g->push();
            }

            p->push();
            x->push();

            if (p->isroot() == false) {
                if ((x == p->l) == (p == g->l)) {
                    rotate(p);
                }
                else {
                    rotate(x);
                }
            }

            rotate(x);
        }

        x->push();
        x->pull();
    }

    Node* expose(Node* x) {
        Node* z = nullptr;
        Node* y = x;

        while (y != nullptr) {
            splay(y);

            y->l = z;
            z = y;
            y = y->p;
        }

        splay(x);
        return z;
    }

    void make_root(Node* x) {
        expose(x);

        if (x->rev == true) {
            x->rev = false;
        }
        else {
            x->rev = true;
        }
    }
};

int main() {
    LinkCutTree T(5);

    T.Link(1, 2);
    T.Link(1, 3);
    T.Link(3, 4);
    T.Link(3, 5);

    T.Modify(1, 1, 1);
    T.Modify(2, 2, 2);
    T.Modify(3, 3, 3);
    T.Modify(4, 4, 4);
    T.Modify(5, 5, 5);

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

    assert(T.Query(1, 1) == 1);
    assert(T.Query(1, 2) == 3);
    assert(T.Query(1, 3) == 4);
    assert(T.Query(1, 4) == 8);
    assert(T.Query(1, 5) == 9);
    assert(T.Query(2, 2) == 2);
    assert(T.Query(2, 3) == 6);
    assert(T.Query(2, 4) == 10);
    assert(T.Query(2, 5) == 11);
    assert(T.Query(3, 3) == 3);
    assert(T.Query(3, 4) == 7);
    assert(T.Query(3, 5) == 8);
    assert(T.Query(4, 4) == 4);
    assert(T.Query(4, 5) == 12);
    assert(T.Query(5, 5) == 5);

    T.Cut(1, 3);

    assert(T.Query(1, 1) == 1);
    assert(T.Query(1, 2) == 3);
    assert(T.Query(2, 2) == 2);
    assert(T.Query(3, 3) == 3);
    assert(T.Query(3, 4) == 7);
    assert(T.Query(3, 5) == 8);
    assert(T.Query(4, 4) == 4);
    assert(T.Query(4, 5) == 12);
    assert(T.Query(5, 5) == 5);

    T.Link(1, 3);

    assert(T.Query(1, 1) == 1);
    assert(T.Query(1, 2) == 3);
    assert(T.Query(1, 3) == 4);
    assert(T.Query(1, 4) == 8);
    assert(T.Query(1, 5) == 9);
    assert(T.Query(2, 2) == 2);
    assert(T.Query(2, 3) == 6);
    assert(T.Query(2, 4) == 10);
    assert(T.Query(2, 5) == 11);
    assert(T.Query(3, 3) == 3);
    assert(T.Query(3, 4) == 7);
    assert(T.Query(3, 5) == 8);
    assert(T.Query(4, 4) == 4);
    assert(T.Query(4, 5) == 12);
    assert(T.Query(5, 5) == 5);

    T.Modify(4, 1, 1);
    T.Modify(5, 1, 2);

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

    assert(T.Query(1, 1) == 4);
    assert(T.Query(1, 2) == 6);
    assert(T.Query(1, 3) == 10);
    assert(T.Query(1, 4) == 15);
    assert(T.Query(1, 5) == 17);
    assert(T.Query(2, 2) == 2);
    assert(T.Query(2, 3) == 12);
    assert(T.Query(2, 4) == 17);
    assert(T.Query(2, 5) == 19);
    assert(T.Query(3, 3) == 6);
    assert(T.Query(3, 4) == 11);
    assert(T.Query(3, 5) == 13);
    assert(T.Query(4, 4) == 5);
    assert(T.Query(4, 5) == 18);
    assert(T.Query(5, 5) == 7);

    cout << "OK!";

    return 0;
}
