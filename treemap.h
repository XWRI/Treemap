#ifndef TREEMAP_H_
#define TREEMAP_H_

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <exception>

template <typename K, typename V>
class Treemap {
 public:
  //
  // @@@ The class's public API below should _not_ be modified @@@
  //

  // * Capacity
  // Returns number of key-value mappings in map --O(1)
  size_t Size();
  // Returns true if map is empty --O(1)
  bool Empty();

  // * Modifiers
  // Insert @key in map --O(log N) on average
  void Insert(const K &key, const V &value);
  // Remove @key from map --O(log N) on average
  void Remove(const K &key);

  // * Lookup
  // Return value corresponding to @key --O(log N) on average
  const V& Get(const K &key);

  // Return greatest key less than or equal to @key --O(log N) on average
  const K& FloorKey(const K &key);
  // Return least key greater than or equal to @key --O(log N) on average
  const K& CeilKey(const K &key);

  // Return whether @key is found in map --O(log N) on average
  bool ContainsKey(const K& key);
  // Return whether @value is found in map --O(N)
  bool ContainsValue(const V& value);

  // Return max key in map --O(log N) on average
  const K& MaxKey();
  // Return min key in map --O(log N) on average
  const K& MinKey();

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  struct Node {
    K key;
    V value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };
  std::unique_ptr<Node> root;
  unsigned int cur_size = 0;

  // Private constants
  // ...To be completed (if any)...

  // Private methods
  void Insert(std::unique_ptr<Node> &n, const K &key, const V &value);
  void Remove(std::unique_ptr<Node> &n, const K &key);
  const K& FloorKey(std::unique_ptr<Node> &n, const K &key);
  const K& CeilKey(std::unique_ptr<Node> &n, const K &key);
  bool ContainsValue(Node *n, const K& key);
  const K& Max(Node *n);
  const K& Min(Node *n);
};

//
// Your implementation of the class should be located below
//

template <typename K, typename V>
size_t Treemap<K, V>::Size() {
  return cur_size;
}

template <typename K, typename V>
bool Treemap<K, V>::Empty() {
  return(!cur_size);  //  The tree is empty when the size is 0
}

template <typename K, typename V>
void Treemap<K, V>::Insert(std::unique_ptr<Node> &n,
                           const K &key, const V &value) {
  //  Finds the correct position to insert the key
  if (n == nullptr) {
    n = std::unique_ptr<Node>(new Node{key, value});

  //  Moves to the left if the inserted key
  //  is smaller than the current key
  } else if (key < n->key) {
      Insert(n->left, key, value);

  //  Moves to the right if the inserted key
  //  is greater than the current key
  } else if (key > n->key) {
      Insert(n->right, key, value);

  //  Reports error when same key inserted
  } else {
      throw std::invalid_argument("Duplicate key");
  }
}

template <typename K, typename V>
void Treemap<K, V>::Insert(const K &key, const V &value) {
    Insert(root, key, value);
    cur_size++;
}

template <typename K, typename V>
void Treemap<K, V>::Remove(std::unique_ptr<Node> &n, const K &key) {
  //  Checks and report if the tree is empty
  if (n == nullptr)
    throw std::underflow_error("Empty tree");

  //  Finds the node to be removed
  //  Moves to the left if the removed key
  //  is smaller than the current key
  if (key < n->key) {
    Remove(n->left, key);

  //  Moves to the right if the removed key
  //  is greater than the current key
  } else if (key > n->key) {
    Remove(n->right, key);

  //  Finds the Node
  } else {
    //  If the removed node has two children
    if (n->left && n->right) {
      n->key = Min(n->right.get());
      n->value = Get(Min(n->right.get()));
      Remove(n->right, n->key);
    } else {
      n = std::move((n->left) ? n->left : n->right);
    }
  }
}

template <typename K, typename V>
void Treemap<K, V>::Remove(const K &key) {
  Remove(root, key);
  cur_size--;
}

template <typename K, typename V>
const V& Treemap<K, V>::Get(const K &key) {
  //  Checks if the key to be looked for is in the tree
  if (!ContainsKey(key))
    throw std::invalid_argument("Invalid key");

  Node *n = root.get();

  //  Finds the node contains the input key
  while (n != nullptr) {
    if (key == n->key)
      break;

    //  Moves to the left if the input key
    //  is smaller than the current key
    if (key < n->key)
      n = n->left.get();

    //  Moves to the right if the input key
    //  is greater than the current key
    else
      n = n->right.get();
  }
  return n->value;
}

template <typename K, typename V>
const K& Treemap<K, V>::FloorKey(std::unique_ptr<Node> &n, const K &key) {
  //  Checks and reports if the tree is empty
  if (!n)
    throw std::underflow_error("Empty tree");

  if (n->key == key)
    return n->key;

  //  Finds the greatest key that is smaller than the input key
  //  Moves to the left if the current key
  //  is greater than the input key
  if (n->key > key) {
    //  No value in the tree is smaller than the input key
    if (!(n->left))
      throw std::out_of_range("Key out of range");

    return FloorKey(n->left, key);

  //  Further compares the descendents of the current node
  //  if the current key is smaller than the input key
  } else {
      if (n->right && n->right->key <= key)
        return FloorKey(n->right, key);
      else if (n->right && n->right->key > key
               && n->right->left && n->right->left->key <= key)
        return FloorKey(n->right->left, key);
      else if (n->right && n->right->key > key
               && n->right->left && n->right->left->key > key
               && n->right->left->left && n->right->left->left->key <= key)
        return FloorKey(n->right->left->left, key);
      else
       return n->key;
  }
}

template <typename K, typename V>
const K& Treemap<K, V>::FloorKey(const K &key) {
  return FloorKey(root, key);
}

template <typename K, typename V>
const K& Treemap<K, V>::CeilKey(std::unique_ptr<Node> &n, const K &key) {
  //  Checks and reports if the tree is empty
  if (!n)
    throw std::underflow_error("Empty tree");

  if (n->key == key)
    return n->key;

  //  Finds the smallest key that is greater the input key
  //  Moves to the right if the current key
  //  is smaller than the input key
  if (n->key < key) {
    //  No value in the tree is greater than the input key
    if (!(n->right))
      throw std::out_of_range("Key out of range");

    return CeilKey(n->right, key);

  //  Further compares the descendents of the current node
  //  if the current key is greater than the input key
  } else {
      if (n->left &&  n->left->key >= key)
        return CeilKey(n->left, key);
      else if (n->left && n->left->key < key
               && n->left->right && n->left->right->key >= key)
        return CeilKey(n->left->right, key);
      else if (n->left && n->left->key < key
               && n->left->right && n->left->right->key < key
               && n->left->right->right && n->left->right->right->key >= key)
        return CeilKey(n->left->right->right, key);
      else
        return n->key;
  }
}

template <typename K, typename V>
const K& Treemap<K, V>::CeilKey(const K &key) {
  return CeilKey(root, key);
}

template <typename K, typename V>
bool Treemap<K, V>::ContainsKey(const K& key) {
  Node *n = root.get();

  //  Finds the key in the tree
  while (n) {
    if (key == n->key)
      return true;

    //  Moves to the left if the input key
    //  is smaller than the current key
    if (key < n->key)
      n = n->left.get();

    //  Moves to the right if the input key
    //  is greater than the current key
    else
      n = n->right.get();
  }
  return false;
}

template <typename K, typename V>
bool Treemap<K, V>::ContainsValue(Node *n, const K& value) {
     //  Finds the value in the tree
     if (n->value == value)
       return true;

     if (n->right) {
       return ContainsValue(n->right.get(), value);
     }
     if (n->left) {
       return ContainsValue(n->left.get(), value);
    }
    return false;
}

template <typename K, typename V>
bool Treemap<K, V>::ContainsValue(const V& value) {
  return ContainsValue(root.get(), value);
}

template <typename K, typename V>
const K& Treemap<K, V>::Max(Node *n) {
  if (n->right)
    return Max(n->right.get());
  else
    return n->key;
}

template <typename K, typename V>
const K& Treemap<K, V>::MaxKey() {
  return Max(root.get());
}

template <typename K, typename V>
const K& Treemap<K, V>::Min(Node *n) {
  if (n->left)
    return Min(n->left.get());
  else
    return n->key;
}

template <typename K, typename V>
const K& Treemap<K, V>::MinKey() {
  return Min(root.get());
}




#endif  // TREEMAP_H_
