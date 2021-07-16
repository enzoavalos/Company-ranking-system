#include "BST.h"
#include<assert.h>

template <typename T> BST<T>::BST(){
}

template <typename T> BST<T>::BST(Company *new_company,unsigned int ranking_position){
    node = new Node;
    node->company = new_company;
    node->ranking_position = ranking_position;
}

template <typename T> void BST<T>::addElement(Company *companies,unsigned int ranking_position){
    Add(node,companies,ranking_position);
}

template <> void BST<int>::_add(Node *&tree,Company *companies,int ranking_position){
    if (tree == NULL){
        tree = new Node;
        tree->ranking_position = ranking_position;
        tree->company = &companies[ranking_position-1];
    }else{
        if (ranking_position < tree->ranking_position){
            Add(tree->left,companies,ranking_position);
        }else{
            Add(tree->right,companies,ranking_position);
        }
    }
}

template <> void BST<string>::_add(Node *&tree,Company *companies,int ranking_position){
    if (tree == NULL){
        tree = new Node;
        tree->ranking_position = ranking_position;
        tree->company = &companies[ranking_position-1];
    }else{
        Company current_company = companies[ranking_position-1];
        if (current_company.getLegalName() < tree->company->getLegalName()){
            Add(tree->left,companies,ranking_position);
        }else{
            Add(tree->right,companies,ranking_position);
        }
    }
}

template <typename T> void BST<T>::_delete(Node *&tree){
   if (tree != NULL){
        delete(tree->left);
        delete(tree->right);
        delete tree;
        tree = NULL;
   }
}

template <typename T> BST<T>::~BST(){
    delete(node);
}

template <> Company* BST<int>::_search(Node *tree,int position) const{
    if (tree != NULL){
        if (position == tree->ranking_position){
            return tree->company;
        }else if (position < tree->ranking_position){
            if (tree->left != NULL){
                return Search(tree->left,position);
            }
        }else{
            if (tree->right != NULL){
                return Search(tree->right,position);
            }
        }
    }
    return NULL;
}

template <> int BST<string>::_search(Node *tree,string legal_name) const{
    if (tree != NULL){
        if (legal_name == tree->company->getLegalName()){
            return tree->ranking_position;
        }else if (legal_name < tree->company->getLegalName()){
            if (tree->left != NULL){
                return Search(tree->left,legal_name);
            }
        }else{
            if (tree->right!= NULL){
                return Search(tree->right,legal_name);
            }
        }
    }
    return -1;
}

template <> int BST<string>::searchCompany(string legal_name){
    return Search(node,legal_name);
}

template <> Company* BST<int>::searchCompany(unsigned int position){
    return Search(node,position);
}

template class BST<int>;
template class BST<string>;
