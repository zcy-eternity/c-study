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
    cin>>ch; //�ݹ������ζ�ȡ
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
���1���ڵ���parent�ڵ�
���������ֱ���ҵ��ڵ�1�ͽڵ�2�ĸ��ڵ㣬Ȼ�����2������ĳ��ȣ�����ó��Ȳ���˵2�����ĳ��Ȳ�Ϊn����ô
�ͳ��Ľڵ����ƶ�n����Ȼ��Ͷ̵Ľڵ�һ���ƶ��������жϸ��ڵ��Ƿ���ȡ�
���2���ڵ�û��parent�ڵ�
�����ʵҲ�򵥣����ǴӸ��ڵ㿪ʼ�����������Ȼ���жϵ�ǰ�ڵ��Ƿ����2���ڵ㣬��������ͼ���������ǰ�ڵ��
���ҽڵ��Ƿ������2���ڵ㣬��������ͼ������롣������Ҷ�����������ô��ǰ�ڵ������С�������ڵ㡣
*/
//�������2���ڵ����С�������ڵ�
bool find(BiTree T, char u){
    if(T== nullptr)
        return false;
    else if(T->data == u)
        return true;
    else{
        bool flag = find(T->lchild,u);
        if(!flag) //����û�ҵ�����ȥ������
            flag = find(T->rchild,u);
        return flag;
    }
}
BiTNode* fatherNode(BiTree T, char u, char v){
   if(T== nullptr || !find(T,u) || !find(T,v))
        return nullptr; //��Ϊ�ջ���һ����ǰ���в����ڵĽ��
   else{
        if(find(T->lchild,u)&&find(T->lchild,v)) //������������������С�������ڵ�һ����������
            return fatherNode(T->lchild,u,v);
        else if(find(T->rchild,u)&&find(T->rchild,v)) //��������������
            return fatherNode(T->rchild,u,v);
        else
            return T; //�������������������һ�������������������������һ�����λ�ڵ�ǰ��㣬��ʱ�ݹ鵽�����Σ���������T��Ϊ��С�������ڵ�
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

