class Eertree {
public:
    struct Node {
        int len; // Palindrome length
        int count; // Number of palindromes

        Node* link;
        map<char, Node*> next;

        Node(int length) : 
            len(length), 
            count(0), 
            link(nullptr) {}
    };

    Eertree() {
        root_odd = new Node(-1);
        root_even = new Node(0);

        root_odd->link = root_odd;
        root_even->link = root_odd;

        last = root_even;

        states.push_back(root_odd);
        states.push_back(root_even);
    }

    Eertree(string s) {
        root_odd = new Node(-1);
        root_even = new Node(0);

        root_odd->link = root_odd;
        root_even->link = root_odd;

        last = root_even;

        states.push_back(root_odd);
        states.push_back(root_even);

        for (int i = 0; i < (int)s.size(); i++) {
            go(s[i], i, s);
        }
    }

    void go(char c, int pos, const string& s) {
        Node* cur = last;

        while (true) {
            int i = pos - cur->len - 1;

            if (i >= 0 && s[i] == c) {
                break;
            }

            cur = cur->link;
        }

        if (cur->next.count(c)) {
            last = cur->next[c];
            last->count++;
        }
        else {
            Node* clone = new Node(cur->len + 2);
            states.push_back(clone);

            cur->next[c] = clone;

            last = clone;
            last->count = 1;

            if (clone->len == 1) {
                clone->link = root_even;
            }
            else {
                cur = cur->link;

                while (true) {
                    int i = pos - cur->len - 1;

                    if (i >= 0 && s[i] == c) {
                        break;
                    }

                    cur = cur->link;
                }

                clone->link = cur->next[c];
            }
        }
    }

private:
    Node* root_even;
    Node* root_odd;

    Node* last;

    vector<Node*> states;
};
