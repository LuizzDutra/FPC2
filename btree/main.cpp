#include <iostream>
#include <vector>
#include <initializer_list>

template <typename T>
class Node{
  public:
    T data;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
   
    static Node<T>* neo(T val){
      Node<T>* node = new(Node<T>);
      node->data = val;
      return node;
    }

}; 


template <typename T>
class Tree {
  public:
    Node<T>* root = nullptr;

    bool insert(T val){
      if (this->root == nullptr){
        root = Node<T>::neo(val);
        return true;
      }
      Node<T>* j = nullptr;
      Node<T>* i = this->root;

      while (i != nullptr){
        j = i;
        if(val < i->data){
          i = i->left;
        }else if(val > i->data){
          i = i->right;
        }else{
          //Duplicates not allowed
          return false;
        }
      }
      Node<T>* node = Node<T>::neo(val);
      node->parent = j;
      if(val < j->data){
        j->left = node;
      }else{
        j->right = node;
      }
      return true;
    }

    void insert(std::initializer_list<T> list){
      for (T i : list){
        this->insert(i);
      }
    }

    static Node<T>* search(Node<T>* node, T val){
      while (node != nullptr){
        if (val < node->data){
          node = node->left;
        }else if(val > node->data){
          node = node->right;
        }else{
          return node;
        }
      }
      return node;
    }

    Node<T>* search(T val){
      return Tree<T>::search(this->root, val);
    }

    static Node<T>* minimum(Node<T>* node){
      if(node == nullptr){
        return nullptr;
      }
      while (node->left != nullptr){
        node = node->left;
      }
      return node;
    }

    static Node<T>* maximum(Node<T>* node){
      if(node == nullptr){
        return nullptr;
      }
      while(node->right != nullptr){
        node = node->right;
      }
      return node;
    }

    static Node<T>* predecessor(Node<T>* node){
      if (node->left != nullptr){
        return Tree::maximum(node->left);
      }
      Node<T>* p = node->parent;
      while (p != nullptr && node == p->left){
        node = p;
        p = p->parent;
      }
      return p;
    }

    static Node<T>* successor(Node<T>* node){
      if (node->right != nullptr){
        return Tree::minimum(node->right);
      }
      Node<T>* p = node->parent;
      while (p != nullptr && node == p->right){
        node = p;
        p = p->parent;
      }
      return p;
    }

    void remove(Node<T>* del_node){
      Node<T>* node = nullptr;
      Node<T>* piv_node = nullptr;

      if (del_node->left == nullptr || del_node->right == nullptr){
        node = del_node;
      }else{
        node = Tree<T>::successor(del_node);
      }

      if (node->left != nullptr){
        piv_node = node->left;
      }else{
        piv_node = node->right;
      }
      if (piv_node != nullptr){piv_node->parent = node->parent;}

      if (node->parent == nullptr){
        this->root = piv_node;
      }else if (node == node->parent->left){
        node->parent->left = piv_node;
      }else{
        node->parent->right = piv_node;
      }

      if (node != del_node){
        del_node->data = node->data;
      }
      delete node;

    }

    static void traverse(Node<T>* node){
      if (node != nullptr){
        std::cout << node->data << "\n";
        traverse(node->left);
        traverse(node->right);
      }
    }

    void traverse(){
      Tree<T>::traverse(this->root);
    }

    static Tree<T>* from(std::initializer_list<T> list){
      Tree<T>* tree = new(Tree<T>);
      for (auto i : list){
        tree->insert(i);
      }
      return tree;
    }

    void free(){
      this->free_traversal(this->root);
      this->root = nullptr;
    }

    void free_traversal(Node<T>* node){
      if (node != nullptr){
        free_traversal(node->left);
        free_traversal(node->right);
        delete node;
      }
    }


};


int count_duplicates(std::vector<int> &vec){
  Tree<int>* tree = new(Tree<int>);

  size_t duplicate_count = 0;
  for(size_t i = 0; i < vec.size(); i++){
    if (!tree->insert(vec[i])){
      duplicate_count++;
    }
  }
  return duplicate_count;
}


template <typename T>
void print(T text){
  std::cout << text << '\n';
}


int main(int argc, char* argv[]){
  std::vector<int> test = {10, 4, 3, 20, 10, 3, 5, 34, 3};
  std::cout << "Duplicates: " << count_duplicates(test) << "\n";

  print("Slide delete example tree");
  Tree<int>* tree = Tree<int>::from({15, 5, 16, 3, 12, 20, 10, 13, 18, 23, 6, 7});
  tree->traverse();
  std::cout << '\n'; 

  tree->remove(tree->search(5));
  print("Tree after deletion of 5");
  tree->traverse();
  print(' ');

  print("Arguments Tree");
  Tree<int>* arg_tree = new(Tree<int>);
  for (int i = 1; i < argc; i++){
    arg_tree->insert(atoi(argv[i]));
  }
  arg_tree->traverse();

  return 0;
}
