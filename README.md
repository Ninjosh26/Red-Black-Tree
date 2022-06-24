# Red-Black-Tree
This is a templated Red Black Tree I have written in C++. I wanted to try creating a red-black, self-balancing binary search tree on my own. This repository will detail my progress. The red_black_original.h contains the original functionality without key-value pairs. The current red_balck.h has key-value functionality.

## The functionality I have written so far:
  1. Template: `Red_Black_Tree<K, V, Comparator>`
     * `K` - The type of keys used in the tree
     * `V` - The type of values in the tree
     * `Comparator` - How the keys are compared in the tree (Defaulted to std::less)
  2. Aliases:
     * `key_type` - The type of the keys used to organize the tree (Keys should be unique)
     * `value_type` - The type of the values stored in the structure
     * `key_compare` - The comparator used to balance the BST
     * `pair` - The pair type consisting of (`key_type`, `value_type`)
  2. `enum class Color`
     * Red
     * Black
  3. `struct RB_Node`
     * `pair value`
     * `RB_Node* left_child`
     * `RB_Node* right_child` 
     * `Color color`
     * Constructor with default values
     * Copy Constructor
  4. `std::string color_string(Color c)`
     - Converts enum `Color` to a string
  5. `class Red_Black_Tree`
     * `RB_Node* root`
     * `size_t _size`
     * `key_compare comp` - Instance of the comparator for the tree
     
     #### private:
        | Function                                                                  | Description                                                          |
        |---------------------------------------------------------------------------|----------------------------------------------------------------------|
        | `RB_Node* copyHelper(Node* otherRoot)`                                    | Recursive helper function for copying a tree                         |
        | `void deleteHelper(RB_Node* node)`                                        | Recursive helper function for deleting a tree                        |
        | `void insertHelper(RB_Node* node, const pair& x)`                         | Recursive helper function for inserting a new const pair into a tree |
        | `void insertHelper(RB_Node* node, pair&& x)`                              | Recursive helper function for inserting a moved pair into a tree     |
        | `RB_Node* findHelper(RB_Node* node, const key_type& x)`                   | Recursive helper for finding a node in a non-const setting           |
        | `const RB_Node* findHelper(const RB_Node* node, const key_type& x) const` | Recursive helper for finding a node in a const setting               |
        | `void preorder(std::ostream& out, RB_Node* n)`                            | Recursive helper for preorder traversal                              |
        | `void inorder(std::ostream& out, RB_Node* n)`                             | Recursive helper for inorder traversal                               |
        | `void postorder(std::ostream& out, RB_Node* n)`                           | Recursive helper for postorder traversal                             |
        | `RB_Node* rightRotation(RB_Node* root)`                                   | Perform a right rotation around `RB_Node* root`                      |
        | `RB_Node* leftRotation(RB_Node* root)`                                    | Perform a left rotation around `RB_Node* root`                       |
        | `void recolor(RB_Node* root)`                                             | Recolor `RB_Node* root` and its children                             |
        | `RB_Node* rebalanceHelper(RB_Node* node)`                                 | Recursive helper function for rebalancing a tree                     |
        | `void rebalance()`                                                        | Function for rebalancing a tree. Color root black if not already     |
     
     #### public:
        | Function                                            | Description                                                  |
        |-----------------------------------------------------|--------------------------------------------------------------|
        | `bool empty()`                                      | True if list is empty                                        |
        | `void clear()`                                      | Makes a tree empty                                           |
        | `Red_Black_Tree()`                                  | Default Constructor                                          |
        | `Red_Black_Tree(pair value)`                        | Constructs a new tree with `value` as the root               |
        | `Red_Black_Tree(Red_Black_Tree& other)`             | Copy Constructor                                             |
        | `Red_Black_Tree(Red_Black_Tree&& other)`            | Move Constructor                                             |
        | `~Red_Black_Tree()`                                 | Destructor                                                   |
        | `Red_Black_Tree& operator=(Red_Black_Tree& other)`  | Copy Assignment                                              |
        | `Red_Black_Tree& operator=(Red_Black_Tree&& other)` | Move Assignment                                              |
        | `size_t size()`                                     | Returns the number of nodes in the tree                      |
        | `size_t count()`                                    | Returns the number of nodes in the tree                      |
        | `void insert(const pair& x)`                        | Insert const key-value pair into tree and rebalance          |
        | `void insert(pair&& x)`                             | Insert moved key-value pair into tree and rebalance          |
        | `bool contains(const key_type& x) const`            | Returns true if a node with the key is in the tree           |
        | `value_type& find(const key_type& key)`             | Return a reference to the value with a given key             |
        | `const value_type& find(const key_type& key) const` | Return a const reference to the value with a given key       |
        | `value_type& operator[](const key_type& key)`       | Bracket access for refernce to value with given key          |
        | `const value_type& operator[](const key_type& key)` | Bracket access for const reference to value with given key   |
        | `std::ostream& print_preorder(std::ostream& out)`   | Print preorder traversal to given stream with DFS algorithm  |
        | `std::ostream& print_inorder(std::ostream& out)`    | Print inorder traversal to given stream with DFS algorithm   |
        | `std::ostream& print_postorder(std::ostream& out)`  | Print postorder traversal to given stream with DFS algorithm |
        | `void print_level_by_level(std::ostream& out)`      | Prints a tree level-by-level using a BFS algorithm           |
   
   6. `std::ostream& operator<<(std::ostream& out, Red_Black_Tree<T>& rbt)`
      - Print function for tree (Uses `print_level_by_level`)
  
## I plan to add:
  1. A remove function
  2. Input operator to create tree from a file
