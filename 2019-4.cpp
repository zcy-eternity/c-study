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
    cin>>ch; //递归进入会多次读取
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
/*
情况1：节点有parent节点
这种情况就直接找到节点1和节点2的根节点，然后求得2个链表的长度，再求得长度差。如果说2条链的长度差为n，那么
就长的节点先移动n步，然后和短的节点一起移动，并且判断父节点是否相等。
情况2，节点没有parent节点
这个其实也简单，就是从根节点开始遍历这棵树，然后判断当前节点是否包含2个节点，如果包含就继续遍历当前节点的
左右节点是否包含这2个节点，如果包含就继续深入。如果左右都不包含，那么当前节点就是最小公共父节点。
*/
//求二叉树2个节点的最小公共父节点
bool find(BiTree T, char u){
    if(T== nullptr)
        return false;
    else if(T->data == u)
        return true;
    else{
        bool flag = find(T->lchild,u);
        if(!flag) //左树没找到，再去右树找
            flag = find(T->rchild,u);
        return flag;
    }
}
BiTNode* fatherNode(BiTree T, char u, char v){
   if(T== nullptr || !find(T,u) || !find(T,v))
        return nullptr; //树为空或找一个当前树中不存在的结点
   else{
        if(find(T->lchild,u)&&find(T->lchild,v)) //两结点均在左子树，最小公共父节点一定在左子树
            return fatherNode(T->lchild,u,v);
        else if(find(T->rchild,u)&&find(T->rchild,v)) //两结点均在右子树
            return fatherNode(T->rchild,u,v);
        else
            return T; //两结点在左右子树或有一个结点在左子树或右子树，另一个结点位于当前结点，此时递归到最深层次，函数参数T即为最小公共父节点
   }
}
int main(){
    BiTree T;
//    ABC##D#E##F##
    create(T);
    Inorder(T);
    cout<<endl;
    cout<<fatherNode(T,'B','E')->data;
}

