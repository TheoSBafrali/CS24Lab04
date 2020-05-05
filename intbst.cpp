// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
#include <limits>

// constructor sets up empty tree
IntBST::IntBST() : root(0) {}

// destructor deletes all nodes
IntBST::~IntBST() { clear(root); }

// recursive helper for destructor
void IntBST::clear(Node *n) {
  if (n) {
    clear(n->left);
    clear(n->right);
    delete n;
  }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
  // handle special case of empty tree first
  if (!root) {
    root = new Node(value);
    return true;
  }
  // otherwise use recursive helper
  return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
  if (value == n->info)
    return false;
  if (value < n->info) {
    if (n->left) {
      return insert(value, n->left);
    } else {
      n->left = new Node(value);
      n->left->parent = n;
      return true;
    }
  } else {
    if (n->right) {
      return insert(value, n->right);
    } else {
      n->right = new Node(value);
      n->right->parent = n;
      return true;
    }
  }
}

// print tree data pre-order
void IntBST::printPreOrder() const { printPreOrder(root); }

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
  if (n) {
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
  }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const { printInOrder(root); }
void IntBST::printInOrder(Node *n) const {
  if (n) {
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
  }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const { printPostOrder(root); }

void IntBST::printPostOrder(Node *n) const {
  if (n) {
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
  }
}

// return sum of values in tree
int IntBST::sum() const { return sum(root); }

// recursive helper for sum
int IntBST::sum(Node *n) const {
  if (n) {
    return sum(n->left) + sum(n->right) + n->info;
  } else {
    return 0;
  }
}

// return count of values
int IntBST::count() const { return count(root); }

// recursive helper for count
int IntBST::count(Node *n) const {
  if (n) {
    return count(n->left) + count(n->right) + 1;
  } else {
    return 0;
  }
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none
// exists Parameters: int value: the value to be found Node* n: the node to
// start with (for a recursive call) Whenever you call this method from
// somewhere else, pass it the root node as "n"
IntBST::Node *IntBST::getNodeFor(int value, Node *n) const {
  if (n) {
    if (n->info == value) {
      return n;
    } else if (n->info > value) {
      return getNodeFor(value, n->left);
    } else if (n->info < value) {
      return getNodeFor(value, n->right);
    }
  }
  return nullptr;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
  if (getNodeFor(value, this->root) != nullptr) {
    return true;
  }
  return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node *IntBST::getPredecessorNode(int value) const {
  int candidate = 0;
  IntBST::Node *n = this->root;
  while (n != nullptr) {
    if (n->info > candidate && n->info < value) {
      candidate = n->info;
    }
    if (n->info >= value) {
      n = n->left;
    } else {
      n = n->right;
    }
  }
  return getNodeFor(candidate, this->root);
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const {
  IntBST::Node *tmp = getPredecessorNode(value);
  if (tmp) {
    return tmp->info;
  }
  return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node *IntBST::getSuccessorNode(int value) const {
  int candidate = std::numeric_limits<int>::max();
  IntBST::Node *n = this->root;
  while (n != nullptr) {
    if (n->info < candidate && n->info > value) {
      candidate = n->info;
    }
    if (n->info <= value) {
      n = n->right;
    } else {
      n = n->left;
    }
  }
  return getNodeFor(candidate, this->root);
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const {
  IntBST::Node *tmp = getSuccessorNode(value);
  if (tmp) {
    return tmp->info;
  }
  return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not
// exist
bool IntBST::remove(int value) {
  IntBST::Node *rmv = getNodeFor(value, this->root);
  if (!rmv) {
    return false;
  }
  bool is_left;
  // if delete root, modify the 0 or 1 child cases
  if (!(rmv->parent)) {
    if (!(rmv->left) && rmv->right) {
      this->root = rmv->right;
      this->root->parent = nullptr;
      delete rmv;
      return true;
    } else if (!(rmv->right) && rmv->left) {
      this->root = rmv->left;
      this->root->parent = nullptr;
      delete rmv;
      return true;
    } else if (!(rmv->left) && !(rmv->right)) {
      this->root = nullptr;
      delete rmv;
      return true;
    }
  } else {
    is_left = (rmv->info < rmv->parent->info);
  }
 // if only rigt subtree...
 if (!(rmv->left) && rmv->right) {
     if(is_left) {
         (rmv->parent)->left = rmv->right;
     } else {
        (rmv->parent)->right = rmv->right;
     }
    (rmv->right)->parent = rmv->parent;
    delete rmv;
    return true;
    // if only left subtree
} else if (rmv->left && !(rmv->right)) {
    if(is_left) {
        (rmv->parent)->left = rmv->left;
    } else {
        (rmv->parent)->right = rmv->left;
    }
    (rmv->left)->parent = rmv->parent;
    delete rmv;
    return true;
    } else if (!(rmv->left) && !(rmv->right)) {
        if(is_left) {
            (rmv->parent)->left = nullptr;
        } else {
            (rmv->parent)->right = nullptr;
        }
        delete rmv;
        return true;
    } else {
    int repl_val = getSuccessor(value);
    if(repl_val == 0) {
        repl_val = getPredecessor(value);
    }
    remove(repl_val);
    rmv->info = repl_val;
  }
  return true;
}
