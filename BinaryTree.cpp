#include <iostream>

using namespace std;

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct TStackNode{
    BiTNode* data;
    struct TStackNode *next;
}TStackNode,*LinkStack;

typedef struct BiThrNode{
    char data;
    struct BiThrNode *lchild,*rchild;
    int lTag,rTag;
}BiThrNode,*BiThrTree;

BiThrNode *pre = nullptr;

typedef struct CSNode{
    char data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

void initStack(LinkStack &s){
    s = nullptr;
}
void push(LinkStack &s, BiTNode* x){
    TStackNode *p = new TStackNode;
    p->data = x;
    p->next = s;
    s = p;
}
void pop(LinkStack &s, BiTNode* &x){
    TStackNode *p = s;
    x = p->data;
    s = p->next;
    delete p;
}
bool StackEmpty(LinkStack s){
    if(!s)
        return true;
    else
       return false;
}
void initBiTree(BiTree &T){
    T = nullptr;
}
//ABC##DE#G##F###
//���������˳������������
void createBiTree(BiTree &T){
    char ch;
    cin>>ch;
    if(ch=='#')
        T = nullptr;
    else{
        T = new BiTNode;
        T->data = ch;
        createBiTree(T->lchild);
        createBiTree(T->rchild);
    }
}
//���������˳��������������
//ABC##DE#G##F###
void createBiThrTree(BiThrTree &T){
    char ch;
    cin>>ch;
    if(ch=='#'){
        T = nullptr;
    } else{
        T = new BiThrNode;
        T->data = ch;
        createBiThrTree(T->lchild);
        createBiThrTree(T->rchild);
    }

}
void inOrder(BiTree T){
    if(T){
        inOrder(T->lchild);
        cout<<T->data<<" ";
        inOrder(T->rchild);
    }
}
void inOrder(BiThrTree T){
    while (T){
        while (T->lTag==0)
            T = T->lchild;
        cout<<T->data<<" ";   //�ҵ���������ĵ�һ��������
        while (T->rTag==1&&T->rchild!= nullptr){
            T = T->rchild;
            cout<<T->data<<" ";
        }    //���������������ѭ�����
        T = T->rchild; //���������������ʼת����������ѭ��δ�˳����ҵ�����������������ĵ�һ��������
    }
}
void inOrderTraverse(BiTree T){
    LinkStack s;
    initStack(s);
    BiTNode *p = T,*q;
    while (p || !StackEmpty(s)){
        if(p){            //ջ�ǿյ����
            push(s,p);
            p = p->lchild;
        } else{
            pop(s,q);
            cout<<q->data<<" ";
            p = q->rchild;
        }
    }
}
int Depth(BiTree T){
    if(T == nullptr)
        return 0;
    else{
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        return m>n ? m+1 : n+1;
    }
}
void Copy(BiTree T, BiTree &newT){
    if(T == nullptr){
        newT = nullptr;
    } else{
        newT = new BiTNode; //���Ƹ����
        newT->data = T->data;
        Copy(T->lchild, newT->lchild);
        Copy(T->rchild, newT->rchild);
    }

}
int NodeCount(BiTree T){
    if(T== nullptr){
        return 0;
    } else{
        int m = NodeCount(T->lchild);
        int n = NodeCount(T->rchild);
        return m+n+1;
    }
}
void InThreading(BiThrTree &T){
    if(T){
        InThreading(T->lchild);
        if(!T->lchild){
            T->lchild = pre; //��ʼpreΪ�� ���������һ�����ǰ��Ϊ��
            T->lTag = 1;
        }
        if(pre&&!pre->rchild){ //��pre��Ϊ��ʱִ�� ��ʼpreΪ�ղ�ִ�� ��ִ�н���ǰ��
            pre->rchild = T;
            pre->rTag = 1;
        }  //��ʼpreΪ��ָ�� ��rTag rTag=0 Ĭ������
        pre = T;
        InThreading(T->rchild);
    }
}
void PreThreading(BiThrTree &T){
    if(T){
        if(!T->lchild){
            T->lchild = pre;
            T->lTag = 1;
        }
        if(pre&&!pre->rchild){
            pre->rchild = T;
            pre->rTag = 1;
        }
        pre = T;
        if(T->lTag == 0)
            PreThreading(T->lchild); //���������������תȦ����
            // ��ǰ������ָ��Ϊ��ʱ���������������ʱ����ָ���ָ��pre
            // ������Ҫ�Ե�ǰ�������ӽ���������Ҳ����pre���������� ����ѭ��
        PreThreading(T->rchild);
    }
}
void InOrderThreading(BiThrTree &T){
    pre = nullptr;
    if(T){
        InThreading(T);
        pre->rTag = 1; //preָ������������һ����� ���һ�����һ��û���Һ���
    }
}
int main(){
    BiTree T;
    initBiTree(T);
    cout<<"���������� �����룺"<<endl;
    createBiTree(T);
    cout<<"�ѽ����������������������(�ݹ�)Ϊ��"<<endl;
    inOrder(T);
    cout<<endl;
    cout<<"�ѽ����������������������(�ǵݹ�)Ϊ��"<<endl;
    inOrderTraverse(T);
    cout<<endl;
    cout<<"�ѽ���������������Ϊ��"<<endl;
    cout<<Depth(T)<<endl;
    cout<<"�ѽ����������Ľ����Ϊ��"<<endl;
    cout<<NodeCount(T)<<endl;
    BiTree newT;
    initBiTree(newT);
    Copy(T,newT);
    cout<<"�����������������������Ϊ��"<<endl;
    inOrder(newT);
    cout<<endl;
    BiThrTree Thr;
    Thr = nullptr;
    cout<<"�������������� �����룺"<<endl;
    createBiThrTree(Thr);
    InOrderThreading(Thr);
    cout<<"�����������������������Ϊ��"<<endl;
    inOrder(Thr);
}
