// Online C++ compiler to run C++ program online
#include<bits/stdc++.h>
using namespace std;

class node 
{
    public:
        string key;
        string value;
        int height;
        node *left;
        node* right;
        
        node(string k,string v){
            key=k;
            value=v;
            height=1;
            left=NULL;
            right=NULL;
        }
};

int getheight(node * n){
    if(n)return n->height;
    return 0;
}

int balance(node *n)
{
    if(n)return getheight(n->left)-getheight(n->right);
    return 0;
}

class avl
{
    public:
    node *root;
    node *insert(node *,string k,string v);
    node *deletee(node*,string k);
};

node* rotateright(node * root){
    node *x=root->left;
    node *t2=x->right;
    x->right=root;
    root->left=t2;
    x->height = max(getheight(x->left), getheight(x->right)) + 1;
        root->height = max(getheight(root->left), getheight(root->right)) + 1;
    return x;
}

node *rotateleft(node * root){
    node *x=root->right;
    node *t2=x->left;
    x->left=root;
    root->right=t2;
    x->height = max(getheight(x->left), getheight(x->right)) + 1;
        root->height = max(getheight(root->left), getheight(root->right)) + 1;
    return x;
}

  void inorder(node* root) {
        if (root) {
            inorder(root->left);
            cout << root->key << " : " << root->value << endl;
            inorder(root->right);
        }
    }

node * avl:: insert(node* root,string k,string v){
    if(!root)return new node(k,v);
    if(root->key>k)
    root->left=insert(root->left,k,v);
    else if(root->key<k)
    root->right=insert(root->right,k,v);
    else {
        cout<<"Duplicate Key"<<endl;
        return root;
    }
    
   
    
    root->height=1+max(getheight(root->left),getheight(root->right));
    
    int bal=balance(root);
    
    if(bal>1 && k<root->left->key){
        return rotateright(root);
    }
   
    if(bal<-1 && k>root->right->key){
        return rotateleft(root);
    }
     if(bal>1 && k>root->left->key)
    {   
        root->left=rotateleft(root->left);
        return rotateright(root);
    }
    if(bal<-1 && k<root->right->key){
        root->right=rotateright(root->right);
        return rotateleft(root);
    }
    return root;
}

 node* minnode(node* n) {
        node* current = n;
        while (current->left)
            current = current->left;
        return current;
    }

node * avl::deletee(node * root,string k){
    if(!root)return root;
    if(root->key>k){
         root->left=deletee(root->left,k);
    }
    else if(root->key<k){
        root->right=deletee(root->right,k);
    }
    else{
        if(!root->left && !root->right){
            delete root;
            return NULL;
        }
         else if(!root->left){
            node* temp=root->right;
            delete root;
            return temp;
        }
        else if(!root->right){
             node* temp=root->left;
            delete root;
            return temp;
        }
        else{
            node *temp=minnode(root->right);
            root->key=temp->key;
            root->value=temp->value;
            root->right=deletee(root->right,temp->key);
        }
    }
    
    if(!root)return root;
    
    root->height=1+max(getheight(root->left),getheight(root->right));
    
    int bal=balance(root);
    
    if(bal>1 && balance(root->left)>=0){
        return rotateright(root);
    }
    if(bal>1 && balance(root->left)<0){
        root->left=rotateleft(root->left);
         return rotateright(root);
    }
    if(bal>-1 && balance(root->left)<=0){
        return rotateleft(root);
        
    }
    if(bal>-1 && balance(root->left)>0){
        root->left=rotateright(root->left);
         return rotateleft(root);
    }
    
    return root;
}

int main()
{
    avl a;
    node *root=a.insert(NULL,"khetesh ","Deore");
    root=a.insert(root,"pramod ","Deore shet");
    root=a.insert(root,"om","Patil");
    root=a.insert(root,"deo","pagar");
    root=a.insert(root,"dhruvesh","patil");
    inorder(root);
    root=a.deletee(root,"om");
    inorder(root);
}