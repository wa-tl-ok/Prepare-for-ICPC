class SplayTree {
public:
    struct Node {
        int data;

        Node* leftChild;
        Node* rightChild;

        Node(int data) : 
            data(data), 
            leftChild(nullptr), rightChild(nullptr) {}
    };

    SplayTree() : root(nullptr) {}

    void add(int data) {
        root = Insert(root, data);
    }

    void del(int data) {
        root = Delete(root, data);
    }

    bool find(int data) {
        if (root == nullptr) {
            return false;
        }
        Node* preroot = splay(root, data);
        if (preroot != nullptr) {
            root = preroot;
        }
        return root->data == data;
    }

private:
    Node* root;

    Node* rightRotate(Node* x) {
        Node* y = x->leftChild;
        x->leftChild = y->rightChild;
        y->rightChild = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->rightChild;
        x->rightChild = y->leftChild;
        y->leftChild = x;
        return y;
    }

    Node* splay(Node* root, int data) {
        if (root == nullptr || root->data == data) {
            return root;
        }

        if (root->data > data) {
            if (root->leftChild == nullptr) {
                return root;
            }

            if (root->leftChild->data > data) {
                root->leftChild->leftChild = splay(root->leftChild->leftChild, data);
                root = rightRotate(root);
            }
            else if (root->leftChild->data < data) {
                root->leftChild->rightChild = splay(root->leftChild->rightChild, data);

                if (root->leftChild->rightChild != nullptr) {
                    root->leftChild = leftRotate(root->leftChild);
                }
            }

            if (root->leftChild == nullptr) {
                return root;
            }
            else {
                return rightRotate(root);
            }
        }
        else {
            if (root->rightChild == nullptr) {
                return root;
            }

            if (root->rightChild->data > data) {
                root->rightChild->leftChild = splay(root->rightChild->leftChild, data);

                if (root->rightChild->leftChild != nullptr) {
                    root->rightChild = rightRotate(root->rightChild);
                }
            }
            else if (root->rightChild->data < data) {
                root->rightChild->rightChild = splay(root->rightChild->rightChild, data);
                root = leftRotate(root);
            }

            if (root->rightChild == nullptr) {
                return root;
            }
            else {
                return leftRotate(root);
            }
        }
    }

    Node* Insert(Node* root, int data) {
        if (root == nullptr) {
            return new Node(data);
        }

        root = splay(root, data);

        if (root->data == data) {
            return root;
        }

        Node* newNode = new Node(data);

        if (root->data > data) {
            newNode->rightChild = root;
            newNode->leftChild = root->leftChild;

            root->leftChild = nullptr;
        }
        else {
            newNode->leftChild = root;
            newNode->rightChild = root->rightChild;

            root->rightChild = nullptr;
        }

        return newNode;
    }

    Node* Delete(Node* root, int data) {
        Node* temp;

        if (root == nullptr) {
            return nullptr;
        }

        root = splay(root, data);

        if (data != root->data) {
            return root;
        }

        if (root->leftChild == nullptr) {
            temp = root;
            root = root->rightChild;
        }
        else {
            temp = root;
            root = splay(root->leftChild, data);
            root->rightChild = temp->rightChild;
        }

        delete temp;

        return root;
    }
};
