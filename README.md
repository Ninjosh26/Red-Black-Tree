# Red-Black-Tree
This is a templated Red Black Tree I have written in C++. I wanted to try creating a red-black, self-balancing binary search tree on my own. This repository will detail my progress. 

## The functionality I have written so far:
  1. `enum class Color`
     * Red
     * Black
  2. `struct Node`
     * `T value`
     * `Node* left_child`
     * `Node* right_child` 
     * `Color color`
     * Constructor with default values
     * Copy Constructor
  3. `std::string color_string(Color c)`
     - Converts enum `Color` to a string
  4. `class Red_Black_Tree`
     * `Node* root`
     * `size_t _size`
     
     #### private:
        | Function                                       | Description                                                      |
        |------------------------------------------------|------------------------------------------------------------------|
        | `Node* copyHelper(Node* otherRoot)`            | Recursive helper function for copying a tree                     |
        | `void deleteHelper(Node* node)`                | Recursive helper function for deleting a tree                    |
        | `void insertHelper(Node* node, T& value)`      | Recursive helper function for inserting a new node into a tree   |
        | `Node* rightRotation(Node* root)`              | Perform a right rotation around `Node* root`                     |
        | `Node* leftRotation(Node* root)`               | Perform a left rotation around `Node* root`                      |
        | `void recolor(Node* root)`                     | Recolor `Node* root` and its children                            |
        | `Node* rebalanceHelper(Node* node)`            | Recursive helper function for rebalancing a tree                 |
        | `void rebalance()`                             | Function for rebalancing a tree. Color root black if not already |
        | `Node* findHelper(Node* node, const T& value)` | Recursive helper function for finding a value in a tree          | 
     
     #### public:
        | Function                                            | Description                                             |
        |-----------------------------------------------------|---------------------------------------------------------|
        | `bool empty()`                                      | True if list is empty                                   |
        | `void clear()`                                      | Makes a tree empty                                      |
        | `Red_Black_Tree()`                                  | Default Constructor                                     |
        | `Red_Black_Tree(T value)`                           | Constructs a new tree with `value` as the root          |
        | `Red_Black_Tree(Red_Black_Tree& other)`             | Copy Constructor                                        |
        | `Red_Black_Tree(Red_Black_Tree&& other)`            | Move Constructor                                        |
        | `~Red_Black_Tree()`                                 | Destructor                                              |
        | `Red_Black_Tree& operator=(Red_Black_Tree& other)`  | Copy Assignment                                         |
        | `Red_Black_Tree& operator=(Red_Black_Tree&& other)` | Move Assignment                                         |
        | `bool is_in_tree(const T& value)`                   | Returns true if the value is in the tree                |
        | `void insert(T& value)`                             | Insert value into tree and rebalance                    |
        | `void print_level_by_level(std::ostream& out)`      | Prints a tree level-by-level using a BFS algorithm      |
   
   5. `std::ostream& operator<<(std::ostream& out, Red_Black_Tree<T>& rbt)`
      - Print function for tree (Uses `print_level_by_level`)
  
## I plan to add:
  1. A remove function
  2. Preorder, inorder, and postorder prints
  3. Input operator to create tree from a file
  4. Key, value pairs
