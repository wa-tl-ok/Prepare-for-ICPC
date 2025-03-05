class Aho_Corasick {
public:
    struct TrieNode {
        map<char, TrieNode*> children;
        TrieNode* parent;

        bool term;

        TrieNode() :
            parent(nullptr),
            term(false) {}

        int num = 0;
    };

    int NUM = 0;

    Aho_Corasick() {
        root = new TrieNode();
        for (char c = 'a'; c <= 'z'; ++c) {
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
};
