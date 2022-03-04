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
//先序遍历的顺序建立二叉链表
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
//先序遍历的顺序建立线索二叉树
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
        cout<<T->data<<" ";   //找到中序遍历的第一个结点输出
        while (T->rTag==1&&T->rchild!= nullptr){
            T = T->rchild;
            cout<<T->data<<" ";
        }    //若结点有右线索，循环输出
        T = T->rchild; //结点无右线索，开始转向右子树，循环未退出，找到右子树中中序遍历的第一个结点输出
    }
}
void inOrderTraverse(BiTree T){
    LinkStack s;
    initStack(s);
    BiTNode *p = T,*q;
    while (p || !StackEmpty(s)){
        if(p){            //栈非空的情况
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
        newT = new BiTNode; //复制根结点
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
            T->lchild = pre; //初始pre为空 中序遍历第一个结点前驱为空
            T->lTag = 1;
        }
        if(pre&&!pre->rchild){ //判pre不为空时执行 初始pre为空不执行 仅执行建立前驱
            pre->rchild = T;
            pre->rTag = 1;
        }  //初始pre为空指针 无rTag rTag=0 默认设置
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
            PreThreading(T->lchild); //先序线索化会出现转圈问题
            // 当前结点的左指针为空时会进行线索化，此时左孩子指针会指向pre
            // 接下来要对当前结点的左孩子进行线索化也就是pre进行线索化 出现循环
        PreThreading(T->rchild);
    }
}
void InOrderThreading(BiThrTree &T){
    pre = nullptr;
    if(T){
        InThreading(T);
        pre->rTag = 1; //pre指向中序遍历最后一个结点 最后一个结点一定没有右孩子
    }
}
int main(){
    BiTree T;
    initBiTree(T);
    cout<<"建立二叉树 请输入："<<endl;
    createBiTree(T);
    cout<<"已建立二叉树的中序遍历序列(递归)为："<<endl;
    inOrder(T);
    cout<<endl;
    cout<<"已建立二叉树的中序遍历序列(非递归)为："<<endl;
    inOrderTraverse(T);
    cout<<endl;
    cout<<"已建立二叉树的树高为："<<endl;
    cout<<Depth(T)<<endl;
    cout<<"已建立二叉树的结点数为："<<endl;
    cout<<NodeCount(T)<<endl;
    BiTree newT;
    initBiTree(newT);
    Copy(T,newT);
    cout<<"拷贝二叉树的中序遍历序列为："<<endl;
    inOrder(newT);
    cout<<endl;
    BiThrTree Thr;
    Thr = nullptr;
    cout<<"建立线索二叉树 请输入："<<endl;
    createBiThrTree(Thr);
    InOrderThreading(Thr);
    cout<<"线索二叉树的中序遍历序列为："<<endl;
    inOrder(Thr);
}
