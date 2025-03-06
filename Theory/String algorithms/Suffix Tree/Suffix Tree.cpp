class Suffix_Tree {
public:
    struct Node {
        map<char, Node*> to;
        Node* link;

        int len;
        int fpos;

        Node(int fpos_, int len_) : 
            link(nullptr), 
            
            len(len_), 
            fpos(fpos_) {}
    };

    Suffix_Tree(string s) {
        S = "";
        N = 0;

        root = new Node(0, INF);
        root->link = root;

        node = root;
        pos = 0;

        for (int i = 0; i < s.size(); i++) {
            add_letter(s[i]);
        }
    }

private:
    const int INF = 1e18;

    string S;
    int N;

    Node* root;

    Node* node;
    int pos;

    vector<Node*> NODES;

    void add_letter(char c) {
        S += c;
        ++N;

        pos++;

        Node* last = root;

        while (pos > 0) {
            go_edge();
            char edge = S[N - pos];

            if (!node->to.count(edge)) {
                Node* leaf = new Node(N - pos, INF);
                node->to[edge] = leaf;

                if (last != root) {
                    last->link = node;
                }

                last = root;

                NODES.push_back(leaf);
            }
            else {
                if (node->to[edge]->fpos + pos - 1 < S.size() && S[node->to[edge]->fpos + pos - 1] == c) {
                    if (last != root) {
                        last->link = node;
                    }
                    return;
                }

                Node* split = new Node(node->to[edge]->fpos, pos - 1);

                split->to[c] = new Node(N - 1, INF);
                split->to[S[node->to[edge]->fpos + pos - 1]] = node->to[edge];

                node->to[edge]->fpos += pos - 1;
                node->to[edge]->len -= pos - 1;

                last->link = split;

                node->to[edge] = split;
                last = split;

                NODES.push_back(split->to[c]);
                NODES.push_back(split);
            }

            if (node == root) {
                pos--;
            }
            else {
                node = node->link;
            }
        }
    }

    void go_edge() {
        while (node->to.count(S[N - pos]) && pos > node->to[S[N - pos]]->len) {
            node = node->to[S[N - pos]];
            pos -= node->len;
        }
    }
};
