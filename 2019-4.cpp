// Created by zhangchaoyan1 on 2022/3/17.
#include <iostream>
#include <queue>
using namespace std;
typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void create(BiTree &T){
    char ch;
    cin>>ch;
    if(ch == '#'){
        T = nullptr;
    } else{
        T = new BiTNode;
        T->data = ch;
        create(T->lchild);
        create(T->rchild);
    }
}
void Inorder(BiTree T){
    if(T){
        Inorder(T->lchild);
        cout<<T->data;
        Inorder(T->rchild);
    }
}
void preorder(BiTree T){
    if(T){
        cout<<T->data;
        preorder(T->lchild);
        preorder(T->rchild);
    }
}
BiTNode* loc(BiTree T, char ch){
    BiTNode *p = T;
    queue<BiTree> q;
    q.push(p);
    while (!q.empty()){
        p = q.front();
        q.pop();
        if(p->data == ch)
            return p;
        if(p->lchild)
            q.push(p->lchild);
        if(p->rchild)
            q.push(p->rchild);
    }
    return nullptr;
}
void fatherNode(BiTree T, char u, char v){
    BiTNode *p = loc(T,u);
    BiTNode *q = loc(T,v);
    cout<<p->data;
    cout<<q->data;
}
int main(){
    BiTree T;
//    ABC##D#E##F##
    create(T);
    Inorder(T);
    cout<<endl;
    fatherNode(T,'B','E');

}

