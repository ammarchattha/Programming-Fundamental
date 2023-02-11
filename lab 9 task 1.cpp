#include <iostream>
using namespace std;

class node {
public:
  int data;
  node *left, *right;
  node(int data) {
    this->data = data;
    left = right = NULL;
  }
};

class BinarySearchTree {
private:
  // node class

  // private data members and methods
  node *root;
  int NoOfParents;
  int nodes;
  int h;
  node *Insert(node *root, int val);
  node *Delete(node *root, int data);
  node *InOrderTraversal(node *root);
  node *PreOrderTraversal(node *root);
  node *PostOrderTraversal(node *root);
  node *FindMax(node *root);
  int Parents(node *root);
  int Nodes(node *root, int height);
  int find_height(node *temp, int ans = 0);
  void find_siblings(node *temp, int val);
  bool find_ancestors(node *temp, int val);
  bool find_descendent(node *temp, int val, node *parent);

public:
  BinarySearchTree() {
    root = NULL;
    NoOfParents = 0;
    h = 0;
    nodes = 0;
  }
  void Insert(int val) { Insert(this->root, val); }

  void Delete(int val) { Delete(this->root, val); }
  void InOrderTraversal() { InOrderTraversal(this->root); }
  void PreOrderTraversal() { PreOrderTraversal(this->root); }
  void PostOrderTraversal() { PostOrderTraversal(this->root); }

  void NumberOfParents() {
    int res = Parents(this->root);
    cout << "Number of parents in bst are:  " << res << endl;
  }

  void NumberOfNodes(int height) {
    int res = Nodes(this->root, height);
    cout << "Number of nodes " << res << endl;
  }

  void FindSiblings(int val) { find_siblings(this->root, val); }

  void FindAncestor(int val) { find_ancestors(this->root, val); }

  void FindDescendent(int val) { find_descendent(this->root, val, NULL); }
};
int main() {
  BinarySearchTree tree1, tree2;

  tree1.Insert(50);
  tree1.Insert(17);
  tree1.Insert(72);
  tree1.Insert(12);
  tree1.Insert(23);
  tree1.Insert(54);
  tree1.Insert(76);
  tree1.Insert(9);
  tree1.Insert(14);
  tree1.Insert(19);
  tree1.Insert(67);

  cout << "In Order Print (left--Root--Right)" << endl;
  // tree1.InOrderTraversal();
  cout << "\n-----------------------" << endl;

  tree1.FindSiblings(54);
  cout<<"Ancestors: ";
  tree1.FindAncestor(23);
  cout<<endl<<"Descendent: ";
  tree1.FindDescendent(17);
  cout<<endl;
  return 0;
}

node *BinarySearchTree::Insert(node *r, int val) {
  if (r == NULL) {
    node *t = new node(val);
    if (r == root)
      root = t;
    else
      r = t;
  } else if (r->data == val) {
    cout << "Record already exist" << val;
  } else if (val < r->data) // insert on left s
    r->left = Insert(r->left, val);
  else if (val > r->data)
    r->right = Insert(r->right, val);
  return r;
}
node *BinarySearchTree::Delete(node *r, int data) {
  //    node * r= root1;
  if (r == NULL)
    return r;
  else if (data < r->data)
    r->left = Delete(r->left, data);
  else if (data > r->data)
    r->right = Delete(r->right, data);
  else {
    // No child
    if (r->right == NULL && r->left == NULL) {
      delete r;
      r = NULL;
      return r;
    }
    // One child on left
    else if (r->right == NULL) {
      node *temp = r;
      r = r->left;
      delete temp;
    }
    // One child on right
    else if (r->left == NULL) {
      node *temp = r;
      r = r->right;
      delete temp;
    }
    // two child
    else {
      node *temp = FindMax(root->left);
      root->data = temp->data;
      r->left = Delete(root->left, temp->data);
    }
  }
  return r;
}
node *BinarySearchTree::InOrderTraversal(node *r) {
  if (r == NULL)
    return NULL;
  // first recur on left child
  InOrderTraversal(r->left);
  // then print the data of node
  cout << " " << r->data << " -> ";
  // now recur on right child
  InOrderTraversal(r->right);
}

node *BinarySearchTree::FindMax(node *r) {
  while (r->right != NULL) {
    r = r->right;
  }
  return r;
}
node *BinarySearchTree::PreOrderTraversal(node *r) {
  if (r == NULL)
    return NULL;

  cout << " " << r->data << " -> ";
  PreOrderTraversal(r->left);
  PreOrderTraversal(r->right);
}
node *BinarySearchTree::PostOrderTraversal(node *r) {
  if (r == NULL)
    return NULL;
  PostOrderTraversal(r->left);
  PostOrderTraversal(r->right);
  cout << " " << r->data << " -> ";
}

int BinarySearchTree::Parents(node *temp) {
  // cout<<"Parent function"<<endl;
  if (temp == NULL) {
    return 0;
  }

  if (temp->left != NULL && temp->right != NULL) {
    NoOfParents++;
  }

  if (temp->left != NULL)
    Parents(temp->left);

  if (temp->right != NULL)
    Parents(temp->right);

  return NoOfParents;
}

void BinarySearchTree::find_siblings(node *temp, int val) {
  if (temp == NULL) {
    return;
  }

  find_siblings(temp->left, val);
  find_siblings(temp->right, val);

  if (temp->data == val) {
    if (temp->left != NULL)
      cout << val << " left sibling is " << temp->left->data << endl;
    if (temp->right != NULL)
      cout << val << " right sibling is " << temp->right->data << endl;
  }
}

bool BinarySearchTree::find_ancestors(node *temp, int val) {
  if (temp == NULL) {
    return false;
  }

  if(temp->data == val){
    return true;
  }

  if(
  find_ancestors(temp->left, val) || 
  find_ancestors(temp->right, val)){
    cout<<temp->data<<" ";
    return true;
  }
  return false;
}

bool BinarySearchTree::find_descendent(node *temp, int val, node *parent) {
  if (temp == NULL) {
    return false;
  }

  if(find_ancestors(temp->left, val) ||
  find_ancestors(temp->right, val)){
    cout<<temp->data<<" "; 
  }
  if(temp->data != val){
    return true;
  }
  return false;
}
