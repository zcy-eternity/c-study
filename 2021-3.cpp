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
//在二叉排序树中插入元素
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
//建立二叉排序树
void create(BSTree &T){
    char n;
    cin>>n;
    while (n!='#'){
        insert(T,n);
        cin>>n;
    }
}
//中序遍历
void inorder(BSTree T){
    if(T){
        inorder(T->lchild);
        cout<<T->data<<" ";
        inorder(T->rchild);
    }
}
//求树的高度
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
完全二叉树找到最后一个分支结点，其后的每一个结点均为叶子结点，只有最后一个分支结点的度可能为1且只能右左孩子
判断二叉树是否为一棵完全二叉树的关键就是找到第一个不饱和节点(找到第一个不饱和的节点之后，后序的所有节点不能有孩子节点才是完全二叉树)
*/

//判断树是否是完全二叉树
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
//以嵌套括号的形式输出二叉树
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
//将二叉树的叶子结点连成一个双向链表，除头结点外，不能再创建其他空间
void LinkLeafNode(BSTree T, BSTNode *&r) {
    if(T){
        if(!T->lchild && !T->rchild){
            r->rchild = T;
            T->lchild = r;
            r = T;
        } else{   //注意遍历左右结点，要置于else分支内，处理完叶子结点，不需要继续进行深入递归，若放到外面，修改了叶子结点指针，会深入遍历
            LinkLeafNode(T->lchild,r);
            LinkLeafNode(T->rchild,r);
        }
    }
}
//头插法建立
void LinkLeafNode1(BSTree T, BSTNode *&L) {
    if(T){
        if(!T->lchild && !T->rchild){
            T->rchild = L->rchild;
            if(L->rchild)
                L->rchild->lchild = T;
            T->lchild = L;
            L->rchild = T;
        } else{   //注意遍历左右结点，要置于else分支内，处理完叶子结点，不需要继续进行深入递归，若放到外面，修改了叶子结点指针，会深入遍历
            LinkLeafNode(T->lchild,L);
            LinkLeafNode(T->rchild,L);
        }
    }
}

void printLeaf(BSTNode *r){
    BSTNode *p = r,*L;
    while (p->lchild){
        L = p;       //找到双向链表的首元结点
        p = p->lchild;
    }
    while (L){
        cout<<L->data<<" ";
        L = L->rchild;
    }
}
//头插法输出
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
        cout<<"是"<<endl;
    else
        cout<<"否"<<endl;
    print(T);
    cout<<endl;
    BSTNode *r = new BSTNode;
    r->lchild = nullptr;
    r->rchild = nullptr;
    LinkLeafNode(T,r); //将尾指针传入，不能用L记录初始尾指针r的位置 why?
    printLeaf(r);
}