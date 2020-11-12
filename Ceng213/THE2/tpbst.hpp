#ifndef TWOPHASEBST_H
#define TWOPHASEBST_H

#include <iostream>
#include <string>
#include <stack>
#include <list>
// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class TwoPhaseBST {
private: //do not change
    struct SecondaryNode {
        std::string key;
        T data;
        SecondaryNode *left;
        SecondaryNode *right;

        SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r);
    };

    struct PrimaryNode {
        std::string key;
        PrimaryNode *left;
        PrimaryNode *right;
        SecondaryNode *rootSecondaryNode;

        PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn);
    };

public: // do not change.
    TwoPhaseBST();
    ~TwoPhaseBST();

    TwoPhaseBST &insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data);
    TwoPhaseBST &remove(const std::string &primaryKey, const std::string &secondaryKey);
    TwoPhaseBST &print(const std::string &primaryKey = "", const std::string &secondaryKey = "");
    T *find(const std::string &primaryKey, const std::string &secondaryKey);

private: // you may add your own utility member functions here.
    void destructNode(PrimaryNode * &root);
    void destructNode(SecondaryNode * &root);
    void printfunc1(PrimaryNode *p, int &i);
    void printfunc2(SecondaryNode *t,int &i);
    TwoPhaseBST<T>::SecondaryNode* findParent(TwoPhaseBST<T>::SecondaryNode *root,const std::string &secondaryKey){
      SecondaryNode *cursor = root;
      while (cursor != NULL){
        if(secondaryKey.compare(cursor->key) < 0){
          if((cursor->left->key).compare(secondaryKey) == 0 || (cursor->right->key).compare(secondaryKey) == 0){
            return cursor;
          }
          cursor = cursor->left;
        }
        else if(secondaryKey.compare(cursor->key) > 0){
          if((cursor->left->key).compare(secondaryKey) == 0 || (cursor->right->key).compare(secondaryKey) == 0){
            return cursor;
          }
          cursor = cursor->right;
        }
    }
    return NULL;
    };
    // void remove1(const std::string &k,SecondaryNode * &p);

private: // do not change.
    PrimaryNode *root; //designated root.

    // do not provide an implementation. TwoPhaseBST's are not copiable.
    TwoPhaseBST(const TwoPhaseBST &);
    const TwoPhaseBST &operator=(const TwoPhaseBST &);
};

template <class T>
TwoPhaseBST<T>::SecondaryNode::SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r)
        : key(k), data(d), left(l), right(r) {}

template <class T>
TwoPhaseBST<T>::PrimaryNode::PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn)
        : key(k), left(l), right(r), rootSecondaryNode(rsn) {}

template <class T>
TwoPhaseBST<T>::TwoPhaseBST() : root(NULL) {}

template <class T>
TwoPhaseBST<T>::~TwoPhaseBST() {
    destructNode(root);
}

template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data) {
    /* IMPLEMENT THIS */
  if(root == NULL){
    SecondaryNode* second = new SecondaryNode(secondaryKey,data,NULL,NULL);
    root = new PrimaryNode(primaryKey,NULL,NULL,second);
  }
  else{
    PrimaryNode* cursor = root;
    PrimaryNode* parent;
    PrimaryNode* birinci=NULL;
    while(cursor!=NULL){
      parent = cursor;
      if(primaryKey.compare(cursor->key)<0){
        cursor=cursor->left;
      }
      else if(primaryKey.compare(cursor->key)>0){
        cursor = cursor->right;
      }
      else if(primaryKey.compare(cursor->key)==0){
        birinci = cursor;
        break;
      }
    }
    if(birinci == NULL && primaryKey.compare(parent->key)<0){
      SecondaryNode* second = new SecondaryNode(secondaryKey,data,NULL,NULL);
      parent->left = new PrimaryNode(primaryKey,NULL,NULL,second);
    }
    else if(birinci==NULL && primaryKey.compare(parent->key)>0){
      SecondaryNode* second = new SecondaryNode(secondaryKey,data,NULL,NULL);
      parent->right = new PrimaryNode(primaryKey,NULL,NULL,second);
      }
    else if(birinci != NULL){
        if(birinci->rootSecondaryNode == NULL){
          birinci->rootSecondaryNode = new SecondaryNode(secondaryKey,data,NULL,NULL);
        }
        else if(birinci->rootSecondaryNode != NULL){
          SecondaryNode* cursor2 = birinci->rootSecondaryNode;
          SecondaryNode* parent2;
          while(cursor2 != NULL){
            parent2 = cursor2;
            if(secondaryKey.compare(cursor2->key)<0){
              cursor2=cursor2->left;
            }
            else if(secondaryKey.compare(cursor2->key)>0){
              cursor2 = cursor2->right;
            }
          }
          if(secondaryKey.compare(parent2->key)<0){
            parent2->left = new SecondaryNode(secondaryKey,data,NULL,NULL);
          }
          else if(secondaryKey.compare(parent2->key)>0){
            parent2->right = new SecondaryNode(secondaryKey,data,NULL,NULL);
          }
        }
      }
    }
    return *this;
  }  


template <class T>
void TwoPhaseBST<T>::printfunc1(TwoPhaseBST::PrimaryNode* p,int &i){
  int j = 0;
  if(p==NULL){
    return;
  }
  printfunc1(p->left,i);
  if(i !=0){
  std::cout << "}, "; }
  std::cout << "\"" << p->key << "\" : {";
  printfunc2(p->rootSecondaryNode,j);
  i++;
  printfunc1(p->right,i);
}
template <class T>
void TwoPhaseBST<T>::printfunc2(TwoPhaseBST::SecondaryNode* t, int &i){
  if(t==NULL){
    return;
  }
  printfunc2(t->left,i);
  if(i!=0){
    std::cout << ", ";
  }
  std::cout << "\"" << t->key << "\" : " << "\"" << t->data << "\"";
  i++;
  printfunc2(t->right,i);
}

template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::remove(const std::string &primaryKey, const std::string &secondaryKey) {
    /* IMPLEMENT THIS */
    PrimaryNode *cursor = root;
  PrimaryNode *primary = NULL;
  SecondaryNode* secondRoot = NULL;
  SecondaryNode* secondary = NULL;
  SecondaryNode* cursor2 = NULL;
  while (cursor != NULL){
    if(primaryKey.compare(cursor->key) < 0){
      cursor = cursor->left;
    }
    else if(primaryKey.compare(cursor->key) > 0){
      cursor = cursor->right;
    }
    else if(primaryKey.compare(cursor->key) == 0){
      primary = cursor;
      break;
    }
}
if(primary != NULL){
  secondRoot = primary->rootSecondaryNode;
  cursor2 = secondRoot;
  while(cursor2 != NULL){
    if(secondaryKey.compare(cursor2->key) < 0){
      cursor2 = cursor2->left;
    }
    else if(secondaryKey.compare(cursor2->key) > 0){
      cursor2 = cursor2->right;
    }
    else if(secondaryKey.compare(cursor2->key) == 0){
      secondary = cursor2;
      break;
    }
  }
  if(secondary == secondRoot){
    if(secondary->left == NULL && secondary->right == NULL){
    primary->rootSecondaryNode = NULL;
    delete secondary;
    }
    else if(secondary->left == NULL && secondary->right != NULL){
      primary->rootSecondaryNode = secondary->right;
      delete secondary;
    }
    else if(secondary->left != NULL && secondary->right == NULL){
      primary->rootSecondaryNode = secondary->left;
      delete secondary;
    }
    else if(secondary->left != NULL && secondary->right != NULL){
      SecondaryNode* min=secondary->right;
      SecondaryNode* parentmin;
      SecondaryNode* left = primary->rootSecondaryNode->left;
      SecondaryNode* right = primary->rootSecondaryNode->right;
      while(min->left != NULL){
        min = min->left;
      }
      parentmin = findParent(secondary,min->key);
      if(parentmin == secondary){
        min->left = left;
        primary->rootSecondaryNode = min;
        delete secondary;
      }
      else{
        parentmin->left = min->right;
        min->left = left;
        min->right = right;
        primary->rootSecondaryNode = min;
        delete secondary;
      }
      }
    }
    else if(secondary->left == NULL && secondary->right == NULL){
      SecondaryNode* parent = findParent(primary->rootSecondaryNode,secondary->key);
      if(parent->left == secondary){
        parent->left = NULL;
        delete secondary;
      }
      else if(parent->right == secondary){
        parent->right = NULL;
        delete secondary;
      }
    }
    else if(secondary->left != NULL && secondary->right == NULL){
      SecondaryNode* parent = findParent(primary->rootSecondaryNode,secondary->key);
      if(parent->left == secondary){
        parent->left = secondary->left;
        delete secondary;
      }
      else if(parent->right == secondary){
        parent->right = secondary->left;
        delete secondary;
      }
    }
    else if(secondary->left == NULL && secondary->right != NULL){
      SecondaryNode* parent = findParent(primary->rootSecondaryNode,secondary->key);
      if(parent->left == secondary){
        parent->left = secondary->right;
        delete secondary;
      }
      else if(parent->right == secondary){
        parent->right = secondary->right;
        delete secondary;
      }
    }
    else if(secondary->left != NULL && secondary->right != NULL){
      SecondaryNode* parent = findParent(primary->rootSecondaryNode,secondary->key);
      SecondaryNode* min=secondary->right;
      SecondaryNode* parentmin;
      SecondaryNode* newNode;
      while(min->left != NULL){
        min = min->left;
      }
      parentmin = findParent(primary->rootSecondaryNode,min->key);
      newNode = new SecondaryNode(min->key,min->data,NULL,NULL);
      if(parent->right == secondary){
        parent->right = newNode;
        newNode->right = secondary->right;
        newNode->left = secondary->left;
        parentmin->left = NULL;
        if(newNode->right == min){
          newNode->right = NULL;
        }
      }
      else if(parent->left == secondary){
        parent->left = newNode;
        newNode->right = secondary->right;
        newNode->left = secondary->left;
        parentmin->left = NULL;
        if(newNode->right == min){
          newNode->right = NULL;
        }
      }
        delete secondary;
        delete min;
      }
    }
    return *this;
  }


template <class T>
TwoPhaseBST<T> &TwoPhaseBST<T>::print(const std::string &primaryKey, const std::string &secondaryKey) {
    /* IMPLEMENT THIS */
    PrimaryNode *cursor = root;
    PrimaryNode *primary = NULL;
    SecondaryNode* secondary = NULL;
    SecondaryNode* cursor2 = NULL;
    while (cursor != NULL){
      if(primaryKey.compare(cursor->key) < 0){
        cursor = cursor->left;
      }
      else if(primaryKey.compare(cursor->key) > 0){
        cursor = cursor->right;
      }
      else if(primaryKey.compare(cursor->key) == 0){
        primary = cursor;
        break;
      }
  }
    if(primary != NULL){
      SecondaryNode* secondRoot = primary->rootSecondaryNode;
      cursor2 = secondRoot;
      while(cursor2 != NULL){
        if(secondaryKey.compare(cursor2->key) < 0){
          cursor2 = cursor2->left;
        }
        else if(secondaryKey.compare(cursor2->key) > 0){
          cursor2 = cursor2->right;
        }
        else if(secondaryKey.compare(cursor2->key) == 0){
          secondary = cursor2;
          break;
        }
      } }
    if(primaryKey == "" && secondaryKey == ""){
      if(root == NULL){
        std::cout << "{}" << std::endl;
      }
      else{
        int i=0;
        std::cout << "{";
        printfunc1(root,i);
        std::cout << "}}" << std::endl;
      }
    }
    else if(primaryKey ==  "" && secondaryKey != ""){
      ;
    }
    else if(primaryKey != "" && secondaryKey == ""){
      if(primary == NULL){
        std::cout << "{}" << std::endl;
      }
      else{
        int i=0;
        std::cout << "{\"" << primary->key << "\" : {";
        printfunc2(primary->rootSecondaryNode,i);
        std::cout << "}}" << std::endl;
      }
    }
    else if(primaryKey != "" && secondaryKey != ""){
      if(secondary == NULL || primary == NULL){
        std::cout << "{}" << std::endl;
      }
      else{
      std::cout << "{\"" << primary->key << "\" : {";
      std::cout << "\"" << secondary->key << "\" : \"" << secondary->data << "\"}}"<<std::endl;
     }
}
 return *this;}

template <class T>
T *TwoPhaseBST<T>::find(const std::string &primaryKey, const std::string &secondaryKey) {
    /* IMPLEMENT THIS */
    PrimaryNode *cursor = root;
   PrimaryNode *primary = NULL;
   SecondaryNode* secondRoot = NULL;
   SecondaryNode* secondary = NULL;
   SecondaryNode* cursor2 = NULL;
   while (cursor != NULL){
     if(primaryKey.compare(cursor->key) < 0){
       cursor = cursor->left;
     }
     else if(primaryKey.compare(cursor->key) > 0){
       cursor = cursor->right;
     }
     else if(primaryKey.compare(cursor->key) == 0){
       primary = cursor;
       break;
     }
 }
   if(primary != NULL){
    secondRoot = primary->rootSecondaryNode;
     cursor2 = secondRoot;
     while(cursor2 != NULL){
       if(secondaryKey.compare(cursor2->key) < 0){
         cursor2 = cursor2->left;
       }
       else if(secondaryKey.compare(cursor2->key) > 0){
         cursor2 = cursor2->right;
       }
       else if(secondaryKey.compare(cursor2->key) == 0){
         secondary = cursor2;
         break;
       }
     }
       if(secondary == NULL){
           return NULL;
       }
   }
   else{
       return NULL;
           }
     return &(secondary->data);
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::PrimaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    destructNode(root->rootSecondaryNode);

    delete root;

    root = NULL;
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::SecondaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    delete root;

    root = NULL;
}

#endif //TWOPHASEBST_H
