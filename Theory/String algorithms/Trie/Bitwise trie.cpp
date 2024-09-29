class Bitwise_trie {
public:
    struct TrieNode {
        int count;
        TrieNode* children[2];
        TrieNode* parent;

        TrieNode() : count(0), parent(nullptr) {
            children[0] = nullptr;
            children[1] = nullptr;
        }
    };

    Bitwise_trie() {
        root = new TrieNode();
    }

    void add(int num) {
        private_add(num);
    }

    void remove(int num) {
        private_remove(num);
    }

    int query(int num) {
        return private_query(num);
    }
private:
    TrieNode* root;

    void private_add(int num) {
        TrieNode* current = root;
        current->count++;

        for (int i = 31; i >= 0; i--) {
            bool bit = (num >> i) & 1;

            if (current->children[bit] == nullptr) {
                current->children[bit] = new TrieNode();
                current->children[bit]->parent = current;
            }

            current = current->children[bit];
            current->count++;
        }
    }

    void private_remove(int num) {
        TrieNode* current = root;
        current->count--;

        for (int i = 31; i >= 0; i--) {
            bool bit = (num >> i) & 1;
            TrieNode* child = current->children[bit];
            child->count--;

            if (child->count == 0) {
                delete child;
                current->children[bit] = nullptr;
                return;
            }

            current = child;
        }
    }

    int private_query(int num) {
        TrieNode* current = root;
        int maxXOR = 0;

        for (int i = 31; i >= 0; i--) {
            bool bit = (num >> i) & 1;
            bool oppositeBit = !bit;

            if (current->children[oppositeBit] != nullptr) {
                maxXOR |= (1 << i);
                current = current->children[oppositeBit];
            }
            else {
                current = current->children[bit];
            }
        }

        return maxXOR;
    }
};
