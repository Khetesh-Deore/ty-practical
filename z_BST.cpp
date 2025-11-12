#include<bits/stdc++.h>
using namespace std;

class node 
{
    public:
        int data;
        node *left;
        node *right;
        
        node(int d,node*l=NULL,node *r=NULL){
            data=d;
            left=l;
            right=r;
        }
};

class bst
{
    public:
    node *root;
    
    bst(){
        root=NULL;
    }
    node *insert(node* root ,int dta);
    void inorder(node* root);
    void search(node *,int);
    int height(node * root);
    int leaf(node *root);
    node *deletee(node *root,int key );
    int minn(node *root);
    void inordernonrec(node *);
    void preordernonrec(node *);
    void postordernonrec(node *);
};

node* bst::insert(node *root,int dta){
    if(!root)return new node(dta);
    if(root->data>dta){
        root->left=insert(root->left,dta);
    }
    else if(root->data<dta){
        root->right=insert(root->right,dta);
    }
    else {
        cout<<"data can not be inserted"<<endl;
        return root;
    }
    return root;
}

void bst::postordernonrec(node *root){
   stack<node*>st1,st2;
   st1.push(root);
   while(!st1.empty()){
       node *temp=st1.top();
        st1.pop();
        st2.push(temp);
        if(temp->left){
            st1.push(temp->left);
        }
        if(temp->right){
            st1.push(temp->right);
        }
   }
   while(!st2.empty()){
       node *temp=st2.top();
        st2.pop();
       cout<<temp->data<<" ";
   }
   
}


void bst::preordernonrec(node *root){
   stack<node*>st;
   st.push(root);
   while(!st.empty()){
      root= st.top();
       cout<<root->data<<" ";
       st.pop();
       if(root->right){
           st.push(root->right);
       }
       if(root->left){
           st.push(root->left);
       }
       
   }
}


void bst::inordernonrec(node *root){
    node *temp=root;
    if(!temp)return;
    stack<node *>st;
   //st.push(temp);
    while( temp ||!st.empty() ){
        while(temp){
            st.push(temp);
            temp=temp->left;
        }
        temp=st.top();st.pop();
        cout<<temp->data<<" ";
        temp=temp->right;
    }
}

void bst::inorder(node* root){
    if(!root)return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
    
}

void bst::search(node * root,int dta){
   
    if(!root){
        cout<<"element not found"<<endl;
        return;
    }
    if(root->data==dta){
        cout<<"element found"<<endl;
    }
    else if(root->data>dta)
     search(root->left,dta);
    else
    search(root->right,dta);
}

int bst ::height(node * root){
    if(!root)return 0;
    return 1+max(height(root->left),height(root->right));
}

int bst ::leaf(node *root){
    if(!root)return 0;
    if(!root->left && !root->right)return 1;
    return leaf(root->left)+leaf(root->right);
}

int bst:: minn(node *root){
    while(root &&root->left){
        root=root->left;
    }
    return root->data;
}

node *bst::deletee(node *root,int key){
    if(!root)return root;
    
    if(root->data>key){
        root->left=deletee(root->left,key);
    }
    else if(root->data<key){
        root->right=deletee(root->right,key);
    }
    else{
        if(!root->left && !root->right){
            delete root;
            return NULL;
        }
        else if (!root->right){
            node *temp=root->left;
            delete root;
            return temp;
        }
        else if(!root->left){
            node *temp=root->right;
            delete root;
            return temp;
        }
        else{
            root->data=minn(root->right);
            root->right=deletee(root->right,root->data);
        }
    }
    return root;
}

int main(){
    bst b;
    node *root= b.insert(nullptr,5);
    b.inorder(root);
    cout<<endl;
    root=b.insert(root,4);
    b.inorder(root);
    cout<<endl;
    root= b.insert(root,8);
    b.inorder(root); cout<<endl;
    root=b.insert(root,1);
    b.inorder(root); cout<<endl;
    root= b.insert(root,6);
    b.inorder(root); cout<<endl;
    root= b.insert(root,9);
    b.inorder(root); cout<<endl;
    b.search(root,1);
   root= b.insert(root,3);
    root= b.insert(root,0);
    b.inorder(root);
    cout<<endl;
      b.inordernonrec(root);cout<<endl;
       b.preordernonrec(root);cout<<endl;
       b.postordernonrec(root);cout<<endl;
       
       
    b.search(root,2);
    cout<<"\nH:"<<b.height(root);
    cout<<"\nleaf:"<<b.leaf(root)<<endl;
    
    root=b.deletee(root,4);
    b.inorder(root);
    cout<<endl;
    root=b.deletee(root,5);
    b.inorder(root);
    cout<<endl;
    //cout<<root->data;
    b.inordernonrec(root);
}