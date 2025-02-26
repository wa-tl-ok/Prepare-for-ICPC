class SuffixAutomaton {
public:
    struct Node {
        int len;
        Node* link;
        map<char, Node*> next;

        Node(int length) : len(length), link(nullptr) {}
    };

    SuffixAutomaton() {
        root = new Node(0);
        last = root;
        states.push_back(root);
    }

    void go(char c) {
        Node* cur = new Node(last->len + 1);
        states.push_back(cur);

        Node* p = last;
        while (p && !p->next.count(c)) {
            p->next[c] = cur;
            p = p->link;
        }

        if (!p) {
            cur->link = root;
        }
        else {
            Node* q = p->next[c];

            if (p->len + 1 == q->len) {
                cur->link = q;
            }
            else {
                Node* clone = new Node(p->len + 1);
                states.push_back(clone);

                clone->next = q->next;
                clone->link = q->link;

                while (p && p->next[c] == q) {
                    p->next[c] = clone;
                    p = p->link;
                }

                q->link = clone;
                cur->link = clone;
            }
        }

        last = cur;
    }

private:
    Node* root;
    Node* last;
    vector<Node*> states;
};
