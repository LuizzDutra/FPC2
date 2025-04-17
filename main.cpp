#include <iostream>
#include <vector>

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

    bool insert(int val){
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
      if(node != nullptr && node->left != nullptr){
        return Tree<T>::maximum(node->left);
      }
      return nullptr;
    }

    static Node<T>* successor(Node<T>* node){
      if(node != nullptr && node->right != nullptr){
        return Tree<T>::minimum(node->right);
      }
      return nullptr;
    }

    static void traverse(Node<T>* node){
      if (node != nullptr){
        std::cout << node->data << "\n";
        traverse(node->left);
        traverse(node->right);
      }
    }

    static Tree<T>* from_vec(std::vector<T> &vec){
      Tree<T>* tree = new(Tree<T>);
      for(size_t i = 0; i < vec.size(); i++){
        tree->insert(vec[i]);
      }
      return tree;
    }

};


int find_duplicates(std::vector<int> &vec){
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


int main(){
  std::vector<int> test = {2, 3, 2, 5, 45, 23, 16, 5, -40, -2, 10, -50};
  std::cout << find_duplicates(test) << "\n";
  Tree<int>* tree = Tree<int>::from_vec(test);
  Tree<int>::traverse(tree->root);
  std::cout << '\n';
  /*
  print(Tree<int>::minimum(tree->root)->data);
  print(Tree<int>::maximum(tree->root)->data);
  print(Tree<int>::predecessor(Tree<int>::minimum(tree->root)));
  */
  
  Node<int>* s = Tree<int>::search(tree->root, 0);
  if (s != nullptr){
    print(s->data);
  }else{
    print(s);
  }

  return 0;
}
