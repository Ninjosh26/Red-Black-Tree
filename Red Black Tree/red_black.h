#ifndef RED_BLACK_H
#define RED_BLACK_H
#include <iostream>
#include <queue>
#include <string>

template <class T>
class Red_Black_Tree {
    private:
        enum class Color {Red, Black};

        struct Node {
            T value;
            Node* left_child;
            Node* right_child;
            Color color;

            Node(T value = T(), Node* left_child = nullptr, Node* right_child = nullptr, Color color = Color::Red)
             : value{value}, left_child{left_child}, right_child{right_child}, color{color} {}
            Node(Node& other)
             : value{other.value}, left_child{nullptr}, right_child{nullptr}, color{other.color} {}
        };

        std::string color_string(Color c) {
            switch(c) {
                case Color::Red:
                    return "Red";
                default:
                    return "Black";
            }
        }

        Node* _root;
        size_t _size;

        // Recursive helper function for copying a tree
        Node* copyHelper(Node* otherRoot) {
            if (otherRoot == nullptr) {
                return nullptr;
            }

            Node* left = copyHelper(otherRoot->left_child);
            Node* right = copyHelper(otherRoot->right_child);

            return new Node(otherRoot->value, left, right, otherRoot->color);

        }

        // Recursive helper function for deleting a tree
        void deleteHelper(Node* node) {
            if (node == nullptr) {
                return;
            }

            if (node->left_child != nullptr) {
                deleteHelper(node->left_child);
                node->left_child = nullptr;
            }

            if (node->right_child != nullptr) {
                deleteHelper(node->right_child);
                node->right_child = nullptr;
            }

            delete node;
        }

        // Recursive helper function for inserting a new node into a tree
        void insertHelper(Node* node, T& value) {
            if (value < node->value) { // If less than current node, move left
                if (node->left_child == nullptr) {
                    node->left_child = new Node(std::move(value));
                } else {
                    insertHelper(node->left_child, value);
                }
            } else if (value > node->value) { // If more than current node, move right
                if (node->right_child == nullptr) {
                    node->right_child = new Node(std::move(value));
                } else {
                    insertHelper(node->right_child, value);
                }
            } else {
                throw std::runtime_error("This number is already in the tree");
            }
        }

        // Function for a right rotation
        Node* rightRotation(Node* root) {
            Node* temp = root->left_child->right_child;
            Node* newRoot = root->left_child;

            root->left_child->right_child = root;
            root->left_child = temp;

            return newRoot;
        }

        // Function for a left rotation
        Node* leftRotation(Node* root) {
            Node* temp = root->right_child->left_child;
            Node* newRoot = root->right_child;

            root->right_child->left_child = root;
            root->right_child = temp;

            return newRoot;
        }

        // Function for recoloring a node and its children
        void recolor(Node* root) {
            root->color = Color::Red;
            root->left_child->color = Color::Black;
            root->right_child->color = Color::Black;
        }

        // Recursive helper function for rebalancing a tree
        Node* rebalanceHelper(Node* node) {

            // No rebalancing if nullptr
            if (node == nullptr) {
                return nullptr;
            }

            // Assign left child to rebalanced left subtree
            node->left_child = rebalanceHelper(node->left_child);

            // Assign right child to rebalanced right subtree
            node->right_child = rebalanceHelper(node->right_child);

            if (node->left_child != nullptr && node->left_child->left_child != nullptr) {

                if (node->left_child->color == Color::Red && node->left_child->left_child->color == Color::Red) {

                    if (node->right_child != nullptr && node->right_child->color == Color::Red) { // Uncle is red (recolor)
                        recolor(node);

                        return node;
                    } else { // Right rotation
                        Node* newRoot = rightRotation(node);
                        newRoot->color = Color::Black;
                        node->color = Color::Red;

                        return newRoot;
                    }
                }
            } 
            
            if (node->left_child != nullptr && node->left_child->right_child != nullptr) {
                if (node->left_child->color == Color::Red && node->left_child->right_child->color == Color::Red) {
                    if (node->right_child != nullptr && node->right_child->color == Color::Red) { // Uncle is red (recolor)
                        recolor(node);

                        return node;
                    } else { // Double right rotation
                        node->left_child = leftRotation(node->left_child);
                        Node* newRoot = rightRotation(node);
                        node->color = Color::Red;
                        newRoot->color = Color::Black;

                        return newRoot;
                    }
                }
            } 
            
            if (node->right_child != nullptr && node->right_child->right_child != nullptr) {

                if (node->right_child->color == Color::Red && node->right_child->right_child->color == Color::Red) {

                    if (node->left_child != nullptr && node->left_child->color == Color::Red) { // Uncle is red (recolor)
                        recolor(node);

                        return node;
                    } else { // Left rotation
                        Node* newRoot = leftRotation(node);
                        newRoot->color = Color::Black;
                        node->color = Color::Red;

                        return newRoot;
                    }
                }
            } 
            
            if (node->right_child != nullptr && node->right_child->left_child != nullptr) {
                if (node->right_child->color == Color::Red && node->right_child->left_child->color == Color::Red) {
                    if (node->left_child != nullptr && node->left_child->color == Color::Red) { // Uncle is red (recolor)
                        recolor(node);

                        return node;
                    } else { // Double left rotation
                        node->right_child = rightRotation(node->right_child);
                        Node* newRoot = leftRotation(node);
                        node->color = Color::Red;
                        newRoot->color = Color::Black;

                        return newRoot;
                    }
                }
            }

            // If no changes need to be made, return the subtree
            return node;
        }

        // Function for rebalancing a tree
        void rebalance() {
            // New root after rebalancing
            _root = rebalanceHelper(_root);

            // Root must be black
            if (_root->color != Color::Black) {
                _root->color = Color::Black;
            }
        }

        // Recursive helper function for finding a value
        Node* findHelper(Node* node, const T& value) {
            if (node == nullptr) {
                return nullptr;
            }

            if (node->value == value) { // If at correct node, return it
                return node;
            } else if (node->value > value) { // If current node is greater, go left
                return findHelper(node->left_child);
            } else { // Otherwise, go right
                return findHelper(node->right_child);
            }
        }

    public:
        // Checks if tree is empty
        bool empty() {
            return _size == 0;
        }

        // Makes tree empty
        void clear() {
            deleteHelper(_root);
            _root = nullptr;
            _size = 0;
        }

        // Default constructor
        Red_Black_Tree(): _root(nullptr), _size(0) {}

        // Create tree with root
        Red_Black_Tree(T value): _root{value}, _size(1) {}

        // Copy Constructor
        Red_Black_Tree(Red_Black_Tree& other): _root{nullptr}, _size(other._size) {
            _root = copyHelper(other._root);
        }

        // Move Constructor
        Red_Black_Tree(Red_Black_Tree&& other): _root(other._root), _size(other._size) {
            other._root = nullptr;
            other._size = 0;
        }

        // Destructor
        ~Red_Black_Tree() {
            clear();
        }

        // Copy Assignment
        Red_Black_Tree& operator=(Red_Black_Tree& other) {
            if (this == &other) {
                return *this;
            }
            
            if (!empty()) {
                clear();
            }

            _root = copyHelper(other._root);
            _size = other._size;

            return *this;
        }

        // Move Assignment
        Red_Black_Tree& operator=(Red_Black_Tree&& other) {
            if (this == &other) {
                return *this;
            }

            if (!empty()) {
                clear();
            }

            _root = other._root;
            _size = other._size;
            other._root = nullptr;
            other._size = 0;

            return *this;
        }

        // Insert value into tree
        void insert(T& value) {
            if (_root == nullptr) { // Add root if tree is empty
                _root = new Node(std::move(value));
                _root->color = Color::Black;

            } else { // Insert and rebalance
                insertHelper(_root, value);
                rebalance();
            }

            _size++;
        }

        // Returns true if value is in tree
        bool is_in_tree(const T& value) {
            return findHelper(_root, value) != nullptr;
        }

        void print_level_by_level(std::ostream& out) {
            if (_root == nullptr) {
                return;
            }

            std::queue<Node*> q;
            int node_per_level = 1;
            std::string level_print = "";
            bool done = false;

            // Add root to queue
            q.push(_root);

            // Print while there are nodes
            while (!q.empty() && !done) {
                
                // Print the appropriate nodes for the level
                for (int i = 0; i < node_per_level; i++) {
                    // Remover first node from queue
                    Node* temp = q.front();

                    if (temp == nullptr) { // X represents nullptr child
                        level_print += "X ";
                        q.push(nullptr);
                        q.push(nullptr);
                    } else { // print a node and its color
                        level_print += std::to_string(temp->value) + "[" + color_string(temp->color) + "] ";

                        // Add the node's left and right children to queue
                        q.push(temp->left_child);
                        q.push(temp->right_child);
                    }

                    // Remove the node from the queue when it is no longer needed
                    q.pop();
                }

                done = true;
                for (size_t i = 0; i < level_print.size(); i++) {
                    // If the level string does not contain only X's it should be printed
                    if (level_print.at(i) == '[') {
                        out << level_print << std::endl;
                        done = false;
                        break;
                    }
                }

                // Each level can contain twice as much nodes as the previous
                node_per_level *= 2;
                level_print = "";
            }
        }
};

template <class T>
std::ostream& operator<<(std::ostream& out, Red_Black_Tree<T>& rbt) {
    rbt.print_level_by_level(out);

    return out;
} 

#endif