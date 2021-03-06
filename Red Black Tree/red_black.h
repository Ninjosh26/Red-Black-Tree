#ifndef RED_BLACK_H
#define RED_BLACK_H
#include <iostream>
#include <queue>
#include <string>
#include <utility> // for std::pair

// This class describes a self-balancing binary tree using red-black balancing techniques.
// The tree holds key-value pairs, and thus can function like a dictionary (without deletion currently)
template <typename K, typename V, typename Comparator = std::less<K>>
class Red_Black_Tree {
    public:
        using key_type = K;
        using value_type = V;
        using key_compare = Comparator;
        using pair = std::pair<key_type, value_type>;

    private:
        // Color type to describe if a node is black or red
        enum class Color {Red, Black};

        // Node for Red-Black Tree
        struct RB_Node {
            pair value;
            RB_Node* left_child;
            RB_Node* right_child;
            Color color;

            RB_Node(pair value = pair(), RB_Node* left_child = nullptr, RB_Node* right_child = nullptr, Color color = Color::Red)
             : value{value}, left_child{left_child}, right_child{right_child}, color{color} {}
            RB_Node(RB_Node& other)
             : value{other.value}, left_child{nullptr}, right_child{nullptr}, color{other.color} {}
        };

        // Converts enum Color to a string
        std::string color_string(Color c) {
            switch(c) {
                case Color::Red:
                    return "Red";
                default:
                    return "Black";
            }
        }





        //////////////////////
        // Member Variables //
        //////////////////////

        RB_Node* _root;
        size_t _size;
        key_compare comp;





        //////////////////////////////
        // PRIVATE HELPER FUNCTIONS //
        //////////////////////////////

        // Recursive helper function for copying a tree
        RB_Node* copyHelper(RB_Node* otherRoot) {
            if (otherRoot == nullptr) {
                return nullptr;
            }

            RB_Node* left = copyHelper(otherRoot->left_child);
            RB_Node* right = copyHelper(otherRoot->right_child);

            return new RB_Node(otherRoot->value, left, right, otherRoot->color);

        }

        // Recursive helper function for deleting a tree
        void deleteHelper(RB_Node* node) {
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
        void insertHelper(RB_Node* node, const pair& x) {
            if (x.first == node->value.first) {
                node->value = x;
            } else if (comp(x.first, node->value.first)) { // If less than current node, move left
                if (node->left_child == nullptr) {
                    node->left_child = new RB_Node(x);
                } else {
                    insertHelper(node->left_child, x);
                }
            } else { // If more than current node, move right
                if (node->right_child == nullptr) {
                    node->right_child = new RB_Node(x);
                } else {
                    insertHelper(node->right_child, x);
                }
            }
        }

        // Recursive helper function for inserting a new node into a tree
        void insertHelper(RB_Node* node, pair&& x) {
            if (x.first == node->value.first) {
                node->value = std::move(x);
            } else if (comp(x.first, node->value.first)) { // If less than current node, move left
                if (node->left_child == nullptr) {
                    node->left_child = new RB_Node(std::move(x));
                } else {
                    insertHelper(node->left_child, std::move(x));
                }
            } else { // If more than current node, move right
                if (node->right_child == nullptr) {
                    node->right_child = new RB_Node(std::move(x));
                } else {
                    insertHelper(node->right_child, std::move(x));
                }
            }
        }

        // Recursive helper function for finding a value
        RB_Node* findHelper(RB_Node* node, const key_type& x) {
            if (node == nullptr) {
                return nullptr;
            }

            if (node->value.first == x) { // If at correct node, return it
                return node;
            } else if (comp(x, node->value.first)) { // If current node is greater, go left
                return findHelper(node->left_child, x);
            } else { // Otherwise, go right
                return findHelper(node->right_child, x);
            }
        }

        const RB_Node* findHelper(const RB_Node* node, const key_type& x) const {
            if (node == nullptr) {
                return nullptr;
            }

            if (node->value.first == x) { // If at correct node, return it
                return node;
            } else if (comp(x, node->value.first)) { // If current node is greater, go left
                return findHelper(node->left_child, x);
            } else { // Otherwise, go right
                return findHelper(node->right_child, x);
            }
        }

        // Traversal printing helpers
        void preorder(std::ostream& out, RB_Node* n) {
            if (!n) { return; }

            out << "(" << n->value.first << ", " << n->value.second << ")[" << color_string(n->color) << "] " << std::endl;
            preorder(out, n->left_child);
            preorder(out, n->right_child);
        }

        void inorder(std::ostream& out, RB_Node* n) {
            if (!n) { return; }

            inorder(out, n->left_child);
            out << "(" << n->value.first << ", " << n->value.second << ")[" << color_string(n->color) << "] " << std::endl;
            inorder(out, n->right_child);
        }

        void postorder(std::ostream& out, RB_Node* n) {
            if (!n) { return; }

            postorder(out, n->left_child);
            postorder(out, n->right_child);
            out << "(" << n->value.first << ", " << n->value.second << ")[" << color_string(n->color) << "] " << std::endl;
        }





        //////////////////////////////////
        // FUNCTIONS USED FOR BALANCING //
        //////////////////////////////////

        // Function for a right rotation
        RB_Node* rightRotation(RB_Node* root) {
            RB_Node* temp = root->left_child->right_child;
            RB_Node* newRoot = root->left_child;

            root->left_child->right_child = root;
            root->left_child = temp;

            return newRoot;
        }

        // Function for a left rotation
        RB_Node* leftRotation(RB_Node* root) {
            RB_Node* temp = root->right_child->left_child;
            RB_Node* newRoot = root->right_child;

            root->right_child->left_child = root;
            root->right_child = temp;

            return newRoot;
        }

        // Function for recoloring a node and its children
        void recolor(RB_Node* root) {
            root->color = Color::Red;
            root->left_child->color = Color::Black;
            root->right_child->color = Color::Black;
        }

        // Recursive helper function for rebalancing a tree
        RB_Node* rebalanceHelper(RB_Node* node) {

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
                        RB_Node* newRoot = rightRotation(node);
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
                        RB_Node* newRoot = rightRotation(node);
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
                        RB_Node* newRoot = leftRotation(node);
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
                        RB_Node* newRoot = leftRotation(node);
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
        Red_Black_Tree(pair value): _root{value}, _size(1) {}

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

        // Returns the number of nodes in the tree
        size_t size() { return _size; }
        size_t count() { return _size; }

        // Insert value into tree
        void insert(const pair& x) {
            if (_root == nullptr) { // Add root if tree is empty
                _root = new RB_Node(x);
                _root->color = Color::Black;

            } else { // Insert and rebalance
                insertHelper(_root, x);
                rebalance();
            }

            _size++;
        }

        // Insert value into tree
        void insert(pair&& x) {
            if (_root == nullptr) { // Add root if tree is empty
                _root = new RB_Node(std::move(x));
                _root->color = Color::Black;

            } else { // Insert and rebalance
                insertHelper(_root, std::move(x));
                rebalance();
            }

            _size++;
        }

        // Returns true if value is in tree
        bool contains(const key_type& x) const {
            return findHelper(_root, x) != nullptr;
        }

        // Find a value in the tree with a given key
        value_type& find(const key_type& key) { return findHelper(_root, key )->value.second; }
        const value_type& find(const key_type& key) const { return findHelper(_root, key)->value.second; }

        // Bracket access operator
        value_type& operator[](const key_type& key) { return findHelper(_root, key )->value.second; }
        const value_type& operator[](const key_type& key) const { return findHelper(_root, key)->value.second; }

        // Tree printing based on traversals
        std::ostream& print_preorder(std::ostream& out) { 
            preorder(out, _root); 
            return out;
        }
        std::ostream& print_inorder(std::ostream& out) { 
            inorder(out, _root); 
            return out;
        }
        std::ostream& print_postorder(std::ostream& out) { 
            postorder(out, _root);
            return out;
        }

        /* Prints a tree level-by-level in the format:
        
               3                  
              / \                 3[color]
             2   5         =>     2[color] 5[color] 
            /   / \               1[color] X 4[color] 6[color]
           1   4   6 

           null children are repesented by X's in non-empty levels
        */
       /*
        void print_level_by_level(std::ostream& out) {
            if (_root == nullptr) {
                return;
            }

            std::queue<RB_Node*> q;
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
                    RB_Node* temp = q.front();

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
        */

        void print_level_by_level(std::ostream& out) {
            if (_root == nullptr) {
                return;
            }

            std::queue<RB_Node*> q; // This queue contains elements from a level and its children
            q.push(_root);
            size_t elementsInLevel = 1; // Elements in the current level
            bool nonNullChild = false;

            while (elementsInLevel > 0) {
                RB_Node* n = q.front();
                q.pop();
                elementsInLevel--;

                if (n) {
                    out << "(" << n->value.first << ", " << n->value.second << ")[" << color_string(n->color) << "] ";
                    q.push(n->left_child);
                    q.push(n->right_child);

                    if (n->left_child || n->right_child) {
                        nonNullChild = true;
                    }
                } else {
                    out << "X ";
                    q.push(nullptr); // Descendants of empty node
                    q.push(nullptr);
                }

                if (elementsInLevel == 0) { // Reached the end of the level
                    if (nonNullChild) { // The next level is non-empty
                        out << std::endl;
                        nonNullChild = false;
                        elementsInLevel = q.size();
                    }
                }
            }
        }
};

// Ouput operator for tree
template <typename K, typename V, typename Comparator = std::less<K>>
std::ostream& operator<<(std::ostream& out, Red_Black_Tree<K, V, Comparator>& rbt) {
    rbt.print_level_by_level(out);

    return out;
} 

#endif