class TRA {
public:
    struct TrieNode {
        map<char, TrieNode*> children;
        TrieNode* parent;

        bool term;

        int count;

        TrieNode() :
            parent(nullptr),
            term(false),
            count(0) {}

        int num = 0;
    };

    int NUM = 0;

    TRA() {
        root = new TrieNode();
        for (char c = 'a'; c <= 'b'; ++c) {
            alh.push_back(c);
        }
        A = (int)alh.size();
    }

    void add(const string& word) {
        TrieNode* current = root;

        root->num = 0;

        for (int i = 0; i < word.size(); i++) {
            char c = word[i];

            NUM += 1;

            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
                current->children[c]->parent = current;

                letter[{current, current->children[c]}] = c;
                letter[{current->children[c], current}] = c;
                sigma[{current, c}] = current->children[c];
            }

            current = current->children[c];

            current->num = NUM;
        }

        current->term = true;
    }

    void BUILD() {
        BUILD_TRA();
    }

private:
    TrieNode* root;

    int A;
    vector<char> alh;

    map<pair<TrieNode*, TrieNode*>, char> letter;

    map<TrieNode*, TrieNode*> suf_link;
    map<pair<TrieNode*, char>, TrieNode*> sigma;

    void BUILD_TRA() {
        queue<TrieNode*> Q; Q.push(root);

        while (Q.size() > 0) {
            TrieNode* current = Q.front(); Q.pop();

            if (current == root) {
                suf_link[current] = root;
            }
            else {
                char L = letter[{current, current->parent}];

                if (current->parent == root) {
                    suf_link[current] = root;
                }
                else {
                    suf_link[current] = sigma[{suf_link[current->parent], L}];
                }
            }
            for (char c : alh) {
                if (sigma[{current, c}] == nullptr) {
                    if (current == root) {
                        sigma[{current, c}] = root;
                    }
                    else {
                        sigma[{current, c}] = sigma[{suf_link[current], c}];
                    }
                }
            }

            for (auto c_v : current->children) {
                Q.push(c_v.second);
            }
        }
    }

public:
    /*
       Solving problem:
           Given a string T and a set of strings S [alh = {'a', 'b'}].
           For each string s from the set, determine:
           how many times it can be found as a substring in T?

           --- O(T.size() + TRA.size()) ---
    */

    TrieNode* now = nullptr;

    void go(char c) {
        if (now == nullptr) {
            now = root;
        }
        now = sigma[{now, c}];
        now->count += 1;
    }

    map<TrieNode*, vector<TrieNode*>> G;

    void solve() {
        for (auto u : suf_link) {
            if (u.second == root && u.first == root) {
                continue;
            }
            G[u.second].push_back(u.first);
        }
        dfs(root);
    }

    void dfs(TrieNode* u) {
        for (auto v : G[u]) {
            dfs(v);
            u->count += v->count;
        }
    }

    int find(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return 0;
            }
            current = current->children[c];
        }
        return current->count;
    }
};
