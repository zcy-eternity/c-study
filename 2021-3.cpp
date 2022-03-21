// Created by zhangchaoyan on 2022/3/18.

#include <iostream>
#define MaxSize 100
using namespace std;
typedef struct BSTNode{
    char data;
    BSTNode *lchild,*rchild;
}BSTNode,*BSTree;

typedef struct {
    BSTree data[MaxSize];
    int front,rear;
}SqQueue;
void init(SqQueue &q){
    q.front = q.rear = 0;
}
int EnQueue(SqQueue &q, BSTNode *p){
    if((q.rear+1)%MaxSize == q.front)
        return 0;
    q.data[q.rear] = p;
    q.rear = (q.rear+1)%MaxSize;
    return 1;
}
int DeQueue(SqQueue &q, BSTNode *&p){
    if(q.rear==q.front)
        return 0;
    p = q.data[q.front];
    q.front = (q.front+1)%MaxSize;
    return 1;
}
bool QueueEmpty(SqQueue q){
    if(q.front == q.rear)
        return true;
    else
        return false;
}
//�ڶ����������в���Ԫ��
int insert(BSTree &T,char x){
    if(T == nullptr){
        T = new BSTNode;
        T->data = x;
        T->lchild = nullptr;
        T->rchild = nullptr;
        return 1;
    } else{
        if(T->data == x)
            return 0;
        else if(T->data < x)
            return insert(T->rchild,x);
        else
            return insert(T->lchild,x);
    }
}
//��������������
void create(BSTree &T){
    char n;
    cin>>n;
    while (n!='#'){
        insert(T,n);
        cin>>n;
    }
}
//�������
void inorder(BSTree T){
    if(T){
        inorder(T->lchild);
        cout<<T->data<<" ";
        inorder(T->rchild);
    }
}
//�����ĸ߶�
int depth(BSTree T){
    if(T == nullptr)
        return 0;
    else{
        int m = depth(T->lchild);
        int n = depth(T->rchild);
        return m>n?m+1:n+1;
    }
}
/*
��ȫ�������ҵ����һ����֧��㣬����ÿһ������ΪҶ�ӽ�㣬ֻ�����һ����֧���Ķȿ���Ϊ1��ֻ��������
�ж϶������Ƿ�Ϊһ����ȫ�������Ĺؼ������ҵ���һ�������ͽڵ�(�ҵ���һ�������͵Ľڵ�֮�󣬺�������нڵ㲻���к��ӽڵ������ȫ������)
*/

//�ж����Ƿ�����ȫ������
bool judge(BSTree T){
    if(T== nullptr)
        return false;
    SqQueue q;
    init(q);
    EnQueue(q,T);
    bool find = false;
    BSTNode *p;
    while (!QueueEmpty(q)){
        DeQueue(q,p);
        if(!find){
            if(p->lchild && p->rchild){
                EnQueue(q,p->lchild);
                EnQueue(q,p->rchild);
            } else if(p->lchild && !p->rchild){
                find = true;
                EnQueue(q,p->lchild);
            } else if(!p->lchild && p->rchild)
                return false;
            else{
                find = true;
            }
        } else{
            if(p->lchild || p->rchild)
                return false;
        }
    }
    return true;
}
//��Ƕ�����ŵ���ʽ���������
void print(BSTree T){
    if(T){
       cout<<T->data;
       if(T->lchild || T->rchild)
           cout<<'(';
       print(T->lchild);
       if(T->rchild)
           cout<<',';
       print(T->rchild);
       if(T->lchild || T->rchild)
           cout<<')';
    }
}
//����������Ҷ�ӽ������һ��˫��������ͷ����⣬�����ٴ��������ռ�
void LinkLeafNode(BSTree T, BSTNode *&r) {
    if(T){
        if(!T->lchild && !T->rchild){
            r->rchild = T;
            T->lchild = r;
            r = T;
        } else{   //ע��������ҽ�㣬Ҫ����else��֧�ڣ�������Ҷ�ӽ�㣬����Ҫ������������ݹ飬���ŵ����棬�޸���Ҷ�ӽ��ָ�룬���������
            LinkLeafNode(T->lchild,r);
            LinkLeafNode(T->rchild,r);
        }
    }
}
//ͷ�巨����
void LinkLeafNode1(BSTree T, BSTNode *&L) {
    if(T){
        if(!T->lchild && !T->rchild){
            T->rchild = L->rchild;
            if(L->rchild)
                L->rchild->lchild = T;
            T->lchild = L;
            L->rchild = T;
        } else{   //ע��������ҽ�㣬Ҫ����else��֧�ڣ�������Ҷ�ӽ�㣬����Ҫ������������ݹ飬���ŵ����棬�޸���Ҷ�ӽ��ָ�룬���������
            LinkLeafNode(T->lchild,L);
            LinkLeafNode(T->rchild,L);
        }
    }
}

void printLeaf(BSTNode *r){
    BSTNode *p = r,*L;
    while (p->lchild){
        L = p;       //�ҵ�˫���������Ԫ���
        p = p->lchild;
    }
    while (L){
        cout<<L->data<<" ";
        L = L->rchild;
    }
}
//ͷ�巨���
void printLeaf1(BSTNode *L){
    BSTNode *p = L->rchild;
    while (p){
        cout<<p->data<<" ";
        p = p->rchild;
    }
}
int main(){
    BSTree T;
//    B A D C E #
    create(T);
    inorder(T);
    cout<<endl;
    cout<<depth(T)<<" ";
    if(judge(T))
        cout<<"��"<<endl;
    else
        cout<<"��"<<endl;
    print(T);
    cout<<endl;
    BSTNode *r = new BSTNode;
    r->lchild = nullptr;
    r->rchild = nullptr;
    LinkLeafNode(T,r); //��βָ�봫�룬������L��¼��ʼβָ��r��λ�� why?
    printLeaf(r);
}